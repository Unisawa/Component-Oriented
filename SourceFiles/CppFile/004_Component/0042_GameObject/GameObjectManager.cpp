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
std::list<GameObject*> GameObjectManager::pGameObjectList[GameObject::LAYER_MAX];

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
        pGameObjectList[Layer].clear();
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
        for (auto Iterator = pGameObjectList[Layer].begin(); Iterator != pGameObjectList[Layer].end(); ++Iterator)
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
        for (auto Iterator = pGameObjectList[Layer].begin(); Iterator != pGameObjectList[Layer].end();)
        {
            pObject = (*Iterator);

            // ���X�g����؂藣��
            Iterator = pGameObjectList[Layer].erase(Iterator);

            // GameObject�̍폜
            SafeDeleteUninit(pObject);
        }

        pGameObjectList[Layer].clear();
    }
}

/*===============================================================================================*
  @Summary: �V�[���ǂݍ��ݎ��ɁA�o�^���ꂽ�S�Ă�GameObject���폜����
  @Details: �������A�폜���Ȃ��t���O���^�̂��͍̂폜���Ȃ�
 *===============================================================================================*/
void GameObjectManager::ReleaseAllScene()
{
    GameObject* pObject;

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = pGameObjectList[Layer].begin(); Iterator != pGameObjectList[Layer].end();)
        {
            if ((*Iterator)->IsDontDestroy())
            {
                Iterator++;
            }
            else
            {
                pObject = (*Iterator);

                // ���X�g����؂藣��
                Iterator = pGameObjectList[Layer].erase(Iterator);

                // GameObject�̍폜
                SafeDeleteUninit(pObject);
            }
        }
    }
}

/*===============================================================================================* 
  @Summary: �w�肵�����O������ GameObject ���������ăI�u�W�F�N�g��Ԃ�
  @Details: None
 *===============================================================================================*/
GameObject* GameObjectManager::FindGameObject(std::string Name)
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = pGameObjectList[Layer].begin(); Iterator != pGameObjectList[Layer].end();)
        {
            if (Name == (*Iterator)->GetName())
            {
                return (*Iterator);
            }

            Iterator++;
        }
    }

    return NULL;
}

/*===============================================================================================*
  @Summary: GameObject�����X�g�ɒǉ�����
  @Details: None
 *===============================================================================================*/
void GameObjectManager::LinkList(GameObject* pObject, GameObject::LAYER Layer)
{
    pGameObjectList[Layer].push_back(pObject);
}

/*===============================================================================================*
  @Summary: GameObject�����X�g�����������
  @Details: None
 *===============================================================================================*/
void GameObjectManager::UnLinkList(GameObject* pObject)
{
    GameObject::LAYER Layer = pObject->GetLayer();

    for (auto Iterator = pGameObjectList[Layer].begin(); Iterator != pGameObjectList[Layer].end(); ++Iterator)
    {
        if (*Iterator == pObject)
        {
            // ���X�g����؂藣��
            pGameObjectList[Layer].erase(Iterator);

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

    for (auto Iterator = pGameObjectList[Layer].begin(); Iterator != pGameObjectList[Layer].end();)
    {
        if ((*Iterator) == pObject)
        {
            // ���X�g����؂藣��
            Iterator = pGameObjectList[Layer].erase(Iterator);

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