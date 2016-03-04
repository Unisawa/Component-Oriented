/**************************************************************************************************

 @File   : [ RenderDXManager.cpp ] DirectX�̕`����Ǘ�����N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"
#include "002_Constant/Constant.h"

//-----Object-----//
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0040_RenderDX/RenderDX.h"
#include "004_Component/0040_RenderDX/RenderDXManager.h"
#include "004_Component/0040_RenderDX/00400_Light/LightDXManager.h"
#include "004_Component/0040_RenderDX/00401_Camera/CameraDX.h"
#include "004_Component/0040_RenderDX/00401_Camera/CameraDXManager.h"
#include "004_Component/0040_RenderDX/00402_ScreenState/ScreenStateDX.h"
#include "004_Component/0040_RenderDX/00402_ScreenState/ScreenStateNoneDX.h"
#include "004_Component/0040_RenderDX/00402_ScreenState/ScreenStateDebugDX.h"

#include "005_Debug/DebugManagerDX.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//
LPDIRECT3D9       RenderDXManager::pD3DObject = NULL;
LPDIRECT3DDEVICE9 RenderDXManager::pD3DDevice = NULL;

D3DVIEWPORT9      RenderDXManager::defaultViewport;
D3DXCOLOR         RenderDXManager::clearColor = D3DCOLOR_RGBA(55, 55, 170, 255);

DebugManagerDX*   RenderDXManager::pDebugManagerDX  = NULL;

LightDXManager*   RenderDXManager::pLightDXManager  = NULL;
CameraDXManager*  RenderDXManager::pCameraDXManager = NULL;

std::list<RenderDX*> RenderDXManager::pRenderDXList[GameObject::LAYER_MAX];

/*===============================================================================================* 
  @Summary: ��������
  @Details: None
 *===============================================================================================*/
RenderDXManager *RenderDXManager::Create()
{
    RenderDXManager* pRenderDXManager;
    pRenderDXManager = new RenderDXManager();
    if (FAILED(pRenderDXManager->Init()))
    {
        MessageBox(NULL, "DirectX�ɂ��`��ݒ�Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

        return NULL;
    }
    
    pDebugManagerDX  = DebugManagerDX::Create();

    pLightDXManager  = LightDXManager::Create();
    pCameraDXManager = CameraDXManager::Create();

    return pRenderDXManager;
}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
HRESULT RenderDXManager::Init()
{
    D3DDISPLAYMODE        d3ddm;
    D3DPRESENT_PARAMETERS d3dpp;

    // Direct3D �I�u�W�F�N�g�̐���
    pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);
    if (pD3DObject == NULL)
    {
        MessageBox(NULL, "[ pD3DObject ] �̐����Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

        return E_FAIL;
    }

    // ���݂̃f�B�X�v���C���[�h�̎擾
    if (FAILED(pD3DObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        MessageBox(NULL, "[ pD3DObject ] �f�B�X�v���C���[�h�擾�Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

        return E_FAIL;
    }

    // �X�N���[���T�C�Y�̐ݒ�m�F
#ifdef _DEBUG
    Main::isWindow = true;
#else
    if (IDYES == MessageBox(Main::windowHandle, "�E�B���h�E���[�h�Ŏ��s���܂����H", "��ʃ��[�h", MB_YESNO))
        Main::isWindow = true;
#endif

    // �f�B�X�v���C���[�h�̐ݒ�
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.BackBufferWidth        = (UINT)Constant::SCREEN_WIDTH;     // �Q�[����ʂ̕�
    d3dpp.BackBufferHeight       = (UINT)Constant::SCREEN_HEIGHT;    // �Q�[����ʂ̍���
    d3dpp.BackBufferCount        = 1;                                // �o�b�N�o�b�t�@�̐�
    d3dpp.BackBufferFormat       = d3ddm.Format;                     // �J���[���[�h
    d3dpp.Windowed               = Main::isWindow;                   // True: �E�B���h�E���[�h, False: �t���X�N���[��
    d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;            // �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̐؂�ւ����@
    d3dpp.EnableAutoDepthStencil = TRUE;                             // �f�v�X�o�b�t�@: �I�u�W�F�N�g�̉��s�� �X�e���V���o�b�t�@: �`��̈�̐���
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;                     // �X�e���V���o�b�t�@�̃t�H�[�}�b�g

    if (Main::isWindow)
    {
        // �E�B���h�E���[�h
        d3dpp.FullScreen_RefreshRateInHz = 0;
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    }
    else
    {
        // �t���X�N���[��
        d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    }

    // �f�o�C�X�I�u�W�F�N�g�̍쐬
    if (FAILED(pD3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Main::windowHandle,
        D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice)))
    {
        if (FAILED(pD3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Main::windowHandle,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice)))
        {
            if (FAILED(pD3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, Main::windowHandle,
                D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice)))
            {
                MessageBox(NULL, "[ pD3DDevice ] �̐����Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

                return E_FAIL;
            }
        }
    }

    // �����_�[�X�e�[�g�̐ݒ�
    pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);                     // ���C�g���g�p����
    pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);              // ���J�����O
    pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);             // �����̃u�����h�ݒ� �ȉ� 2�s�܂�
    pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    // �e�N�X�`���̃X�e�[�W�X�e�[�g�̐ݒ� �e�N�X�`���Ƀ�����K��������
    pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP  , D3DTOP_MODULATE);    // �e�N�X�`���ɂ����_�̃�����K��������
    pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);      // �e�N�X�`���̃A���t�@�u�����f�B���O����
    pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);      // Current -�|���S���̏��

    // �T���v���[�X�e�[�g�̐ݒ�
    pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);        // �e�N�X�`����UV�l�̌J��Ԃ���ݒ肷��
    pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);         // �e�N�X�`���̊g��k�����̕�Ԃ��s��
    pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

    // �t�H�O�̐ݒ�
    pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
    pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, clearColor);
    pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);
    float FogDensity = 0.001f;
    pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *((DWORD*)(&FogDensity)));

    // �w�i�N���A�F�̏����ݒ�
    SetClearColor(clearColor);

    // �����r���[�|�[�g�ݒ�
    pD3DDevice->GetViewport(&defaultViewport);

    pScreenStateDX = &ScreenStateDX::none;

    return S_OK;
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void RenderDXManager::Uninit()
{
    // ����GameObjectManager::ReleaseAll()��Render�R���|�[�l���g�͍폜����Ă���̂Ń����N����������
    UnLinkListAll();

    SafeDeleteUninit(pCameraDXManager);
    SafeDeleteUninit(pLightDXManager);

    SafeDeleteUninit(pDebugManagerDX);

    SafeRelease(pD3DDevice);
    SafeRelease(pD3DObject);
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void RenderDXManager::Update()
{
    pDebugManagerDX->Update();

    pLightDXManager->Update();
    pCameraDXManager->Update();

    //UpdateAll();    // GameObject->Update �ŌX��Render��Update�͌Ă΂�Ă���
}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void RenderDXManager::Draw()
{
    // ��ʑS�̂̃N���A
    pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

    // �`��J�n
    pD3DDevice->BeginScene();

        pScreenStateDX->BeginDraw(this);
        pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), clearColor, 1.0f, 0);
        DrawAll();
        pScreenStateDX->EndDraw(this);

        pDebugManagerDX->Draw();

    pD3DDevice->EndScene();

    // �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̓���ւ�
    pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*===============================================================================================*
  @Summary: �o�^���ꂽ�S�Ă�Render���X�V����
  @Details: None
 *===============================================================================================*/
void RenderDXManager::UpdateAll()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = pRenderDXList[Layer].begin(); Iterator != pRenderDXList[Layer].end(); ++Iterator)
        {
            if ((*Iterator)->enabled)
            {
                (*Iterator)->Update();
            }
        }
    }
}

/*===============================================================================================*
  @Summary: �o�^���ꂽ�S�Ă�Render�̕`�������
  @Details: None
 *===============================================================================================*/
void RenderDXManager::DrawAll()
{
    // �`��̍�����
    CalculateZSortAll();
    ZSort();

    // 3D�`��̊J�n
    pCameraDXManager->SetUpCamera3D();

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        // 2D�`��̊J�n
        if (Layer == GameObject::OBJECT2D_OPACITY_ONE)
        {
            pCameraDXManager->SetUpCamera2D();
        }

        for (auto Iterator = pRenderDXList[Layer].begin(); Iterator != pRenderDXList[Layer].end(); ++Iterator)
        {
            if ((*Iterator)->enabled)
            {
                (*Iterator)->Draw();
            }
        }
    }
}

/*===============================================================================================*
  @Summary: �o�^���ꂽ�S�Ă�Render�����X�g�����������
  @Details: None
 *===============================================================================================*/
void RenderDXManager::UnLinkListAll()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        pRenderDXList[Layer].clear();
    }
}

/*===============================================================================================*
  @Summary: �o�^���ꂽ�S�Ă�Render���폜����
  @Details: None
 *===============================================================================================*/
void RenderDXManager::ReleaseAll()
{
    RenderDX* pRender;

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = pRenderDXList[Layer].begin(); Iterator != pRenderDXList[Layer].end();)
        {
            pRender = (*Iterator);

            // ���X�g����؂藣��
            Iterator = pRenderDXList[Layer].erase(Iterator);

            // GameObject�̍폜
            SafeDeleteUninit(pRender);
        }

        pRenderDXList[Layer].clear();
    }
}

/*===============================================================================================* 
  @Summary: �e���C���[��Render���J��������̋����ɂ���ă\�[�g����
  @Details: None
 *===============================================================================================*/
void RenderDXManager::ZSort()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        // �s������ZDepth�l�̓J��������߂����Ƀ\�[�g���A�������͉������Ƀ\�[�g
        if (Layer < GameObject::LAYER::OBJECT3D_TRANSLUCENT_ONE)
        {
            pRenderDXList[Layer].sort(RenderDX::ZSortCompareLess);
        }
        else if (Layer < GameObject::LAYER::OBJECT2D_OPACITY_ONE)
        {
            pRenderDXList[Layer].sort(RenderDX::ZSortCompareGreater);
        }
        else    // 2D�|���S����Z���W���̌���(+)���傫����Α傫���قǍŏ��ɕ`�悳���
        {
            std::stable_sort(pRenderDXList[Layer].begin(), pRenderDXList[Layer].end(), &RenderDX::SortingOrderCompareGreater);
        }
    }
}

/*===============================================================================================* 
  @Summary: �e���C���[��Render��ZDepth�̒l���v�Z����
  @Details: None
 *===============================================================================================*/
void RenderDXManager::CalculateZSortAll()
{
    std::list<CameraDX*> pCamera = CameraDXManager::GetCameraDXList();

    // �J�����̌����A�e�I�u�W�F�N�g�Ƃ̋������v�Z����B
    // ���݃J�������Ƃ�Z�l��ۑ����Ă���킯�ł͂Ȃ��̂ŏ㏑�������Ă���B
    // ���C���[�ɂ���ĉe�����󂯂�悤�ɕύX�������
    for (auto CameraIterator = pCamera.begin(); CameraIterator != pCamera.end(); ++CameraIterator)
    {
        for (int Layer = 0; Layer < GameObject::OBJECT2D_OPACITY_ONE; ++Layer)
        {
            for (auto Iterator = pRenderDXList[Layer].begin(); Iterator != pRenderDXList[Layer].end(); ++Iterator)
            {
                if ((*Iterator)->enabled)
                {
                    (*Iterator)->SetZDepth( (*CameraIterator)->GetZLengthCamera( ((*Iterator)->transform->GetPosition())) );
                }
            }
        }
    }
}

/*===============================================================================================*
  @Summary: Render�����X�g�ɒǉ�����
  @Details: None
 *===============================================================================================*/
void RenderDXManager::LinkList(RenderDX* pRender, GameObject::LAYER Layer)
{
    pRenderDXList[Layer].push_back(pRender);
}

/*===============================================================================================*
  @Summary: Render�����X�g�����������
  @Details: None
 *===============================================================================================*/
void RenderDXManager::UnLinkList(RenderDX* pRender)
{
    GameObject::LAYER Layer = pRender->GetLayer();

    for (auto Iterator = pRenderDXList[Layer].begin(); Iterator != pRenderDXList[Layer].end(); ++Iterator)
    {
        if ((*Iterator) == pRender)
        {
            // ���X�g����؂藣��
            pRenderDXList[Layer].erase(Iterator);

            break;
        }
    }
}

/*===============================================================================================*
  @Summary: �Ώۂ�Render���폜���� (���X�g�������菜��)
  @Details: �Ώۂ�Render��Uninit()���Ă΂��
 *===============================================================================================*/
void RenderDXManager::Release(RenderDX* pRender)
{
    GameObject::LAYER Layer = pRender->GetLayer();

    for (auto Iterator = pRenderDXList[Layer].begin(); Iterator != pRenderDXList[Layer].end();)
    {
        if ((*Iterator) == pRender)
        {
            // ���X�g����؂藣��
            Iterator = pRenderDXList[Layer].erase(Iterator);

            // GameObject�̍폜
            SafeDeleteUninit(pRender);

            return;
        }

        ++Iterator;
    }
}

/*===============================================================================================* 
  @Summary: �t�H���g�e�L�X�g�𐶐�����
  @Details: None
 *===============================================================================================*/
LPD3DXFONT RenderDXManager::CreateFontText(int CharacterSize, int CharacterWidth, int FontSize, bool IsItalic, std::string FontName)
{
    LPD3DXFONT FontDevice;

    if (FAILED(D3DXCreateFont(pD3DDevice, CharacterSize, CharacterWidth, FontSize, 0, IsItalic, SHIFTJIS_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, FontName.c_str(), &FontDevice)))
    {
        MessageBox(NULL, "[ FontDevice ] �̐����Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

        return NULL;
    }

    return FontDevice;
}

/*===============================================================================================* 
  @Summary: �`�悷��̈��Ԃ�ύX����
  @Details: None
 *===============================================================================================*/
void RenderDXManager::ChangeState(ScreenStateDX* pState)
{
    pScreenStateDX = pState;
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//