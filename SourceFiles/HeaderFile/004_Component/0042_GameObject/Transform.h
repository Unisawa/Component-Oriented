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

//-----Object-----//
#include "004_Component/Component.h"

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

    void SetParent(Transform& value);

    //-----Setter, Getter-----//
    void        SetPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; }
    void        SetPosition(const D3DXVECTOR3 &Pos)    { position = Pos; }
    D3DXVECTOR3 GetPosition() const { return position; }

    void        SetRotation(float x, float y, float z) { rotation.x = x; rotation.y = y; rotation.z = z; }
    void        SetRotation(const D3DXVECTOR3 &Rot)    { rotation = Rot; }
    D3DXVECTOR3 GetRotation() const { return rotation; }

    void        SetScale(float x, float y, float z) { lossyScale.x = x; lossyScale.y = y; lossyScale.z = z; }
    void        SetScale(const D3DXVECTOR3 &Sca)    { lossyScale = Sca; }
    D3DXVECTOR3 GetScale() const { return lossyScale; }

private:
    Transform*  parent;        // Transform �̐e

    D3DXVECTOR3 position;      // ���[���h��Ԃ� Transform �̈ʒu
    D3DXVECTOR3 rotation;      // ���[���h��Ԃ� Transform �̉�]
    D3DXVECTOR3 lossyScale;    // �I�u�W�F�N�g�̃O���[�o���X�P�[��
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//