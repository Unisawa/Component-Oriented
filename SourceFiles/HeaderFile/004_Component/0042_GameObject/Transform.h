/**************************************************************************************************

 @File   : [ Transform.h ] �I�u�W�F�N�g�̈ʒu�A��]�A�X�P�[���������N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "008_Utility/Vector3.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class GameObject;

class Transform : public Component
{
public:
             Transform(GameObject* pObject = NULL);
    virtual ~Transform();

    void       SetParent(Transform& value);
    Transform* GetParent() { return parent; }

    //-----Setter, Getter-----//
    void    SetPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; }
    void    SetPosition(const Vector3 &Vec)        { position = Vec; }
    Vector3 GetPosition() const { return position; }

    void    SetRotation(float x, float y, float z) { rotation.x = x; rotation.y = y; rotation.z = z; }
    void    SetRotation(const Vector3 &Vec)        { rotation = Vec; }
    Vector3 GetRotation() const { return rotation; }

    void    SetScale(float x, float y, float z) { lossyScale.x = x; lossyScale.y = y; lossyScale.z = z; }
    void    SetScale(const Vector3 &Vec)        { lossyScale = Vec; }
    Vector3 GetScale() const { return lossyScale; }

    static const std::string Transform::className;

private:
    Transform* parent;     // Transform �̐e

    Vector3 position;      // ���[���h��Ԃ� Transform �̈ʒu
    Vector3 rotation;      // ���[���h��Ԃ� Transform �̉�]
    Vector3 lossyScale;    // �I�u�W�F�N�g�̃O���[�o���X�P�[��
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//