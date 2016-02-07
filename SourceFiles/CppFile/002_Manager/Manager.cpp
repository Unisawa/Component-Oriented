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
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderManagerDX.h"
#include "004_Component/0041_RenderGL/RenderManagerGL.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"

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
RenderManagerDX* Manager::pRenderManagerDX = NULL;
RenderManagerGL* Manager::pRenderManagerGL = NULL;

GameObjectManager* Manager::pGameObjectManager = NULL;

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
HRESULT Manager::Init()
{
#ifdef _DIRECTX
    pRenderManagerDX = RenderManagerDX::Create();
    if (pRenderManagerDX == NULL) return E_FAIL;    // DirectX �̏������Ɏ��s
#endif

#ifdef _OPENGL
    pRenderManagerGL = RenderManagerGL::Create();
    if (pRenderManagerGL == NULL) return E_FAIL;    // OpenGL �̏������Ɏ��s
#endif

    pGameObjectManager = GameObjectManager::Create();

    GameObject* pTemp = new GameObject();
    pTemp->SetName("AAAAA");

    GameObject* apTemp = new GameObject();
    apTemp->SetName("BBBBB");

    return S_OK;
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void Manager::Uninit()
{
#ifdef _DIRECTX
    SafeDeleteUninit(pRenderManagerDX);
#endif

#ifdef _OPENGL
    SafeDeleteUninit(pRenderManagerGL);
#endif

    SafeDeleteUninit(pGameObjectManager);
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void Manager::Update()
{
#ifdef _DIRECTX
    pRenderManagerDX->Update();
#endif

#ifdef _OPENGL
    pRenderManagerGL->Update();
#endif

    pGameObjectManager->Update();
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