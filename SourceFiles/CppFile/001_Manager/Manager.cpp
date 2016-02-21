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
#include "001_Manager/Manager.h"

//-----Manager-----//
#include "006_Tool/0060_Input/InputManager.h"
#include "004_Component/0040_RenderDX/RenderDXManager.h"
#include "004_Component/0041_RenderGL/RenderGLManager.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"
#include "007_Scene/SceneManager.h"

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

RenderDXManager* Manager::pRenderDXManager = NULL;
RenderGLManager* Manager::pRenderGLManager = NULL;

GameObjectManager* Manager::pGameObjectManager = NULL;
SceneManager*      Manager::pSceneManager      = NULL;

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
HRESULT Manager::Init()
{
#ifdef _DIRECTX
    pRenderDXManager = RenderDXManager::Create();
    if (pRenderDXManager == NULL) return E_FAIL;    // DirectX �̏������Ɏ��s
#endif

#ifdef _OPENGL
    pRenderGLManager = RenderGLManager::Create();
    if (pRenderGLManager == NULL) return E_FAIL;    // OpenGL �̏������Ɏ��s
#endif

    pInputManager = InputManager::Create();

    pGameObjectManager = GameObjectManager::Create();

    pSceneManager = SceneManager::Create();

    return S_OK;
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void Manager::Uninit()
{
    SafeDeleteUninit(pSceneManager);

    SafeDeleteUninit(pGameObjectManager);

    SafeDeleteUninit(pInputManager);

#ifdef _DIRECTX
    SafeDeleteUninit(pRenderDXManager);
#endif

#ifdef _OPENGL
    SafeDeleteUninit(pRenderGLManager);
#endif
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void Manager::Update()
{
    pInputManager->Update();

#ifdef _DIRECTX
    pRenderDXManager->Update();
#endif

#ifdef _OPENGL
    pRenderGLManager->Update();
#endif

    pSceneManager->Update();

    pGameObjectManager->Update();
}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void Manager::Draw()
{
#ifdef _DIRECTX
    pRenderDXManager->Draw();
#endif

#ifdef _OPENGL
    pRenderGLManager->Draw();
#endif
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//