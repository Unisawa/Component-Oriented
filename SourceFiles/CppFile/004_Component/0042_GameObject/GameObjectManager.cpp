/**************************************************************************************************

 @File   : [ GameObjectManager.cpp ] �S�Ă̎��̂��Ǘ��N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"

//-----Object-----//
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
std::list<GameObject*> GameObjectManager::gameObjectList[GameObject::LAYER_MAX];

/*===============================================================================================* 
  @Summary: ��������
  @Details: None
 *===============================================================================================*/
GameObjectManager *GameObjectManager::Create()
{
    GameObjectManager* pGameObjectManager;
    pGameObjectManager = new GameObjectManager();
    pGameObjectManager->Init();

    return pGameObjectManager;
}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
void GameObjectManager::Init()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        gameObjectList[Layer].clear();
    }
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void GameObjectManager::Uninit()
{
    ReleaseAll();
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void GameObjectManager::Update()
{
    UpdateAll();
}

/*===============================================================================================*
  @Summary: �o�^���ꂽ�S�Ă�GameObject���X�V����
  @Details: None
 *===============================================================================================*/
void GameObjectManager::UpdateAll()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = gameObjectList[Layer].begin(); Iterator != gameObjectList[Layer].end(); ++Iterator)
        {
            if ((*Iterator)->GetActive())
            {
                (*Iterator)->Update();
            }
        }
    }
}

/*===============================================================================================*
  @Summary: �o�^���ꂽ�S�Ă�GameObject���폜����
  @Details: None
 *===============================================================================================*/
void GameObjectManager::ReleaseAll()
{
    GameObject* pObject;

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = gameObjectList[Layer].begin(); Iterator != gameObjectList[Layer].end();)
        {
            pObject = (*Iterator);

            // ���X�g����؂藣��
            Iterator = gameObjectList[Layer].erase(Iterator);

            // GameObject�̍폜
            SafeDeleteUninit(pObject);
        }

        gameObjectList[Layer].clear();
    }
}

/*===============================================================================================*
  @Summary: GameObject�����X�g�ɒǉ�����
  @Details: None
 *===============================================================================================*/
void GameObjectManager::LinkList(GameObject* pObject, GameObject::LAYER Layer)
{
    gameObjectList[Layer].push_back(pObject);
}

/*===============================================================================================*
  @Summary: GameObject�����X�g�����������
  @Details: None
 *===============================================================================================*/
void GameObjectManager::UnLinkList(GameObject* pObject)
{
    GameObject::LAYER Layer = pObject->GetLayer();

    for (auto Iterator = gameObjectList[Layer].begin(); Iterator != gameObjectList[Layer].end(); ++Iterator)
    {
        if (*Iterator == pObject)
        {
            // ���X�g����؂藣��
            gameObjectList[Layer].erase(Iterator);

            break;
        }
    }
}

/*===============================================================================================*
  @Summary: �Ώۂ�GameObject���폜���� (���X�g�������菜��)
  @Details: �Ώۂ�GameObject��Uninit()���Ă΂��
 *===============================================================================================*/
void GameObjectManager::Release(GameObject* pObject)
{
    GameObject::LAYER Layer = pObject->GetLayer();

    for (auto Iterator = gameObjectList[Layer].begin(); Iterator != gameObjectList[Layer].end();)
    {
        if (*Iterator == pObject)
        {
            // ���X�g����؂藣��
            Iterator = gameObjectList[Layer].erase(Iterator);

            // GameObject�̍폜
            SafeDeleteUninit(pObject);

            return;
        }

        ++Iterator;
    }
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