/**************************************************************************************************

 @File   : [ RenderManagerDX.cpp ] DirectX�̕`����Ǘ�����N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"
#include "001_Constant/Constant.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderManagerDX.h"

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
LPDIRECT3D9       RenderManagerDX::pD3DObject = NULL;
LPDIRECT3DDEVICE9 RenderManagerDX::pD3DDevice = NULL;

D3DXCOLOR         RenderManagerDX::clearColor = D3DCOLOR_RGBA(55, 55, 170, 255);

/*=================================================================================================
  @Summary: �R���X�g���N�^
  @Details: None
=================================================================================================*/
RenderManagerDX::RenderManagerDX()
{

}

/*===============================================================================================* 
  @Summary: �f�X�g���N�^
  @Details: None
 *===============================================================================================*/
RenderManagerDX::~RenderManagerDX()
{

}

/*===============================================================================================* 
  @Summary: ��������
  @Details: None
 *===============================================================================================*/
RenderManagerDX *RenderManagerDX::Create()
{
    RenderManagerDX* pRenderManagerDX;
    pRenderManagerDX = new RenderManagerDX();
    if (FAILED(pRenderManagerDX->Init()))
    {
        MessageBox(NULL, "DirectX�ɂ��`��ݒ�Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

        return NULL;
    }

    return pRenderManagerDX;
}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
HRESULT RenderManagerDX::Init()
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
    //if (IDYES == MessageBox(Main::windowHandle, "�E�B���h�E���[�h�Ŏ��s���܂����H", "��ʃ��[�h", MB_YESNO))
        Main::isWindow = true;

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
    pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);              // ���J�����O

    pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);             // �����̃u�����h�ݒ� �ȉ� 2�s�܂�
    pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

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

    return S_OK;
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::Uninit()
{
    SafeRelease(pD3DDevice);
    SafeRelease(pD3DObject);
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::Update()
{

}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::Draw()
{
    // ��ʂ̃N���A
    pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), clearColor, 1.0f, 0);

    // �`��J�n
    pD3DDevice->BeginScene();

    pD3DDevice->EndScene();

    // �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̓���ւ�
    pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//