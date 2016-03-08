/**************************************************************************************************

 @File   : [ Transform.cpp ] �I�u�W�F�N�g�̈ʒu�A��]�A�X�P�[���������N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "004_Component/0042_GameObject/Transform.h"
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
const std::string Transform::className = "Transform";

/*=================================================================================================
  @Summary: �R���X�g���N�^
  @Details: None
=================================================================================================*/
Transform::Transform(GameObject* pObject) : Component(pObject, TRANSFORM, className)
{
    parent = NULL;

    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;

    rotation.x = 0.0f;
    rotation.y = 0.0f;
    rotation.z = 0.0f;

    lossyScale.x = 1.0f;
    lossyScale.y = 1.0f;
    lossyScale.z = 1.0f;

    gameObject = pObject;
    transform  = this;
}

/*===============================================================================================* 
  @Summary: �f�X�g���N�^
  @Details: None
 *===============================================================================================*/
Transform::~Transform()
{

}

/*===============================================================================================* 
  @Summary: ���[���h�s��̐���
  @Details: None
 *===============================================================================================*/
void Transform::CreateWorldMatrix()
{
    // ���[���h�}�g���b�N�X�̏�����
    worldMatrix.Identity();

    // Rot
    worldMatrix.SetRotateYawPitchRoll(rotation);

    // Scale
    worldMatrix.SetScaling(lossyScale);

    // position
    worldMatrix.SetTranslate(position);

    // �e�����݂���΁A�e�̃��[���h�s����|����
    if (this->parent != NULL)
    {
        worldMatrix *= this->parent->transform->worldMatrix;
    }
}

/*===============================================================================================* 
  @Summary: �Ώۂ̐e�I�u�W�F�N�g�̎q���ǂ������肷��B
  @Details: True �Ȃ� value�̎q�Ɏ��g�����݂���B
 *===============================================================================================*/
bool Transform::IsChildOf(Transform* value)
{
    for (auto Iterator = value->childrentList.begin(); Iterator != value->childrentList.end();)
    {
        if ((*Iterator) == this)
        {
            return true;
        }

        Iterator++;
    }

    return false;
}

/*===============================================================================================* 
  @Summary: �e�I�u�W�F�N�g���玩�g��؂藣��
  @Details: pGameObject ���e�̃I�u�W�F�N�g
 *===============================================================================================*/
void Transform::DetachParent()
{
    if (this->parent == NULL) return;

    GameObject* pGameObject;

    for (auto Iterator = this->parent->childrentList.begin(); Iterator != this->parent->childrentList.end();)
    {
        pGameObject = (*Iterator)->gameObject;

        if (pGameObject == this->gameObject)
        {
            // ���X�g����؂藣��
            this->parent->childrentList.erase(Iterator);

            // ���X�g�o�^
            GameObjectManager::LinkList(this->gameObject, this->gameObject->GetLayer());

            // �e��Transform�������ɔ��f������
            Matrix TransMatrix;
            TransMatrix.SetTranslate(this->transform->GetPosition());
            TransMatrix *= this->parent->GetWorldMatrix();
            this->SetPosition(TransMatrix._41, TransMatrix._42, TransMatrix._43);
            this->rotation += this->transform->parent->rotation;
            //for (Transform *pParent = pGameObject->transform->parent; pParent != NULL;)
            //{
            //    this->rotation += pParent->rotation;
            //    pParent = pParent->parent;
            //}

            this->transform->parent = NULL;

            return;
        }

        Iterator++;
    }
}

/*===============================================================================================* 
  @Summary: �Ώۂ̎q�I�u�W�F�N�g��e�I�u�W�F�N�g(���g)����؂藣��
  @Details: None
 *===============================================================================================*/
void Transform::DetachChildren(Transform* value)
{
    GameObject* pGameObject;

    for (auto Iterator = this->childrentList.begin(); Iterator != this->childrentList.end();)
    {
        pGameObject = (*Iterator)->gameObject;

        if (pGameObject == value->gameObject)
        {
            // ���X�g�o�^
            GameObjectManager::LinkList(pGameObject, pGameObject->GetLayer());

            // ���X�g����؂藣��
            this->childrentList.erase(Iterator);

            // �e��Transform�������ɔ��f������
            Matrix TransMatrix;
            TransMatrix.SetTranslate(pGameObject->transform->GetPosition());
            TransMatrix *= pGameObject->transform->parent->GetWorldMatrix();
            pGameObject->transform->SetPosition(TransMatrix._41, TransMatrix._42, TransMatrix._43);
            pGameObject->transform->rotation += this->rotation;
            //for (Transform *pParent = this->parent; pParent != NULL;)
            //{
            //    pGameObject->transform->rotation -= pParent->rotation;
            //    pParent = pParent->parent;
            //}

            pGameObject->transform->parent = NULL;

            return;
        }

        Iterator++;
    }
}

/*===============================================================================================* 
  @Summary: �S�Ă̎q�I�u�W�F�N�g��e�I�u�W�F�N�g(���g)����؂藣��
  @Details: None
 *===============================================================================================*/
void Transform::DetachChildrenAll()
{
    GameObject* pGameObject;

    for (auto Iterator = this->childrentList.begin(); Iterator != this->childrentList.end();)
    {
        pGameObject = (*Iterator)->gameObject;

        // ���X�g�o�^
        GameObjectManager::LinkList(pGameObject, pGameObject->GetLayer());

        // �e��Transform�������ɔ��f������
        Matrix TransMatrix;
        TransMatrix.SetTranslate(pGameObject->transform->GetPosition());
        TransMatrix *= pGameObject->transform->parent->GetWorldMatrix();
        pGameObject->transform->SetPosition(TransMatrix._41, TransMatrix._42, TransMatrix._43);
        pGameObject->transform->rotation += this->rotation;
        //for (Transform *pParent = this->parent; pParent != NULL;)
        //{
        //    pGameObject->transform->rotation -= pParent->rotation;
        //    pParent = pParent->parent;
        //}

        pGameObject->transform->parent = NULL;

        Iterator++;
    }

    childrentList.clear();
}

/*===============================================================================================* 
  @Summary: �w�肵���I�u�W�F�N�g��e�Ƃ��Ă���GameObject�ɐݒ肷��
  @Details: None
 *===============================================================================================*/
void Transform::SetParent(Transform* value)
{
    // ���ɐe�̎q�ɂȂ��Ă���ꍇ�A�I��
    if (this->IsChildOf(value)) return;

    value->childrentList.push_back(this);
    GameObjectManager::UnLinkList(this->gameObject);    // �e��Update()���Ŏq��Update���ĂԂ��ߎ��g�����X�g����O��
    this->parent = value;

    // �e��Transform�������ɔ��f������
    Matrix TransMatrix, InverseMatrix;
    TransMatrix.SetTranslate(this->position);
    InverseMatrix = value->worldMatrix.Inverse();
    if (InverseMatrix != Matrix::zero)
    {
        Matrix ReturnMatrix = TransMatrix * InverseMatrix;
        this->SetPosition(ReturnMatrix._41, ReturnMatrix._42, ReturnMatrix._43);
        this->rotation -= value->rotation;
    }
}

/*===============================================================================================* 
  @Summary: �w�肵���I�u�W�F�N�g���q�Ƃ��Ă���GameObject�ɐݒ肷��
  @Details: None
 *===============================================================================================*/
void Transform::SetChild(Transform* value)
{
    // ���ɐe�̎q�ɂȂ��Ă���ꍇ�A�I��
    if (value->IsChildOf(this)) return;

    this->childrentList.push_back(value);
    GameObjectManager::UnLinkList(value->gameObject);    // �e��Update()���Ŏq��Update���ĂԂ��ߎ��g�����X�g����O��
    value->parent = this;

    // �e��Transform�������ɔ��f������
    Matrix TransMatrix, InverseMatrix;
    TransMatrix.SetTranslate(value->position);
    InverseMatrix = this->worldMatrix.Inverse();
    if (InverseMatrix != Matrix::zero)
    {
        Matrix ReturnMatrix = TransMatrix * InverseMatrix;
        value->SetPosition(ReturnMatrix._41, ReturnMatrix._42, ReturnMatrix._43);
        value->rotation -= this->rotation;
        //for (Transform *pParent = this->parent; pParent != NULL;)
        //{
        //    value->rotation += pParent->rotation;
        //    pParent = pParent->parent;
        //}
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
