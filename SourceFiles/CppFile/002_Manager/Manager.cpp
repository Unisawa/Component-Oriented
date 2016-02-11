/**************************************************************************************************

 @File   : [ Manager.cpp ] �Q�[���S�ʂɕK�v�Ȋe��Ǘ��N���X���Ǘ�����N���X
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
#include "002_Manager/Manager.h"

//-----Manager-----//
#include "006_Tool/0060_Input/InputManager.h"
#include "004_Component/0040_RenderDX/RenderManagerDX.h"
#include "004_Component/0041_RenderGL/RenderManagerGL.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0042_GameObject/GameObject.h"
#include "004_Component/0040_RenderDX/Render2DDX.h"
#include "004_Component/0041_RenderGL/Render2DGL.h"

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
InputManager* Manager::pInputManager = NULL;

RenderManagerDX* Manager::pRenderManagerDX = NULL;
RenderManagerGL* Manager::pRenderManagerGL = NULL;

GameObjectManager* Manager::pGameObjectManager = NULL;

GameObject* pTemp = NULL;

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
HRESULT Manager::Init()
{
    pInputManager = InputManager::Create();

#ifdef _DIRECTX
    pRenderManagerDX = RenderManagerDX::Create();
    if (pRenderManagerDX == NULL) return E_FAIL;    // DirectX �̏������Ɏ��s
#endif

#ifdef _OPENGL
    pRenderManagerGL = RenderManagerGL::Create();
    if (pRenderManagerGL == NULL) return E_FAIL;    // OpenGL �̏������Ɏ��s
#endif

    pGameObjectManager = GameObjectManager::Create();

    // GameObject�̐����A�R���|�[�l���g�̒ǉ��e�X�g
    GameObject* pGameObject0 = new GameObject;
    pGameObject0->SetName("AAAAA");
    pGameObject0->GetTransform()->SetPosition(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    pGameObject0->GetTransform()->SetScale(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D0 = pGameObject0->AddComponent<Render2DDX>();

    GameObject* pGameObject1 = new GameObject;
    pGameObject1->SetName("BBBBB");
    pGameObject1->GetTransform()->SetPosition(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF + Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    pGameObject1->GetTransform()->SetScale(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D1 = pGameObject1->AddComponent<Render2DDX>();
    pRender2D1->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

    GameObject* pGameObject2 = new GameObject;
    pGameObject2->SetName("CCCCC");
    pGameObject2->GetTransform()->SetPosition(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF - Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    pGameObject2->GetTransform()->SetScale(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D2 = pGameObject2->AddComponent<Render2DDX>();
    pRender2D2->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

    pTemp = pGameObject2;

    //GameObject* pGameObject9 = new GameObject;
    //pGameObject9->SetName("OpenGL");
    //pGameObject9->GetTransform()->SetPosition(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //pGameObject9->GetTransform()->SetScale(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
    //Render2DGL* pRender2D9 = pGameObject9->AddComponent<Render2DGL>();

    return S_OK;
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void Manager::Uninit()
{
    SafeDeleteUninit(pGameObjectManager);

#ifdef _DIRECTX
    SafeDeleteUninit(pRenderManagerDX);
#endif

#ifdef _OPENGL
    SafeDeleteUninit(pRenderManagerGL);
#endif

    SafeDeleteUninit(pInputManager);
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void Manager::Update()
{
    pInputManager->Update();

    // ���̓e�X�g
    Keyboard* pKey = InputManager::GetKeyboard();

    // �R���|�[�l���g�ǉ��e�X�g
    if (pKey->GetKeyboardTrigger(DIK_C))
    {
        Render2DDX* pRender = pTemp->GetComponent<Render2DDX>();

        if (pRender == NULL)
            pTemp->AddComponent<Render2DDX>()->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
    }

    // �R���|�[�l���g�擾�e�X�g
    if (pKey->GetKeyboardTrigger(DIK_V))
    {
        Render2DDX* pRender = pTemp->GetComponent<Render2DDX>();

        if (pRender != NULL)
            pRender->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
    }

    // �Q�[���I�u�W�F�N�g�̍폜�e�X�g
    if (pKey->GetKeyboardTrigger(DIK_K))
    {
        pTemp->Destroy();
    }

    // �R���|�[�l���g�̍폜�e�X�g
    if (pKey->GetKeyboardTrigger(DIK_L))
    {
        Render2DDX* pRender = pTemp->GetComponent<Render2DDX>();
        pRender->Destroy();
    }

    pGameObjectManager->Update();

#ifdef _DIRECTX
    pRenderManagerDX->Update();
#endif

#ifdef _OPENGL
    pRenderManagerGL->Update();
#endif
}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void Manager::Draw()
{
#ifdef _DIRECTX
    pRenderManagerDX->Draw();
#endif

#ifdef _OPENGL
    pRenderManagerGL->Draw();
#endif
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//