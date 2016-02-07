/**************************************************************************************************

 @File   : [ GameObject.h ] �S�Ă̎��Ԃ̃x�[�X�N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----STL-----//
#include <list>

//-----Object-----//
#include "003_Object/Object.h"

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
class Component;
class Transform;

class GameObject : public Object
{
public:

    static const enum LAYER
    {
        LAYER_ZERO = 0,

        // 3D�I�u�W�F�N�g-�s����
        OBJECT3D_OPACITY_ONE,
        OBJECT3D_OPACITY_TWO,

        // �r���{�[�h-�s����
        BILLBOARD_OPACITY_ONE,

        // 3D�I�u�W�F�N�g-������
        OBJECT3D_TRANSLUCENT_ONE,
        OBJECT3D_TRANSLUCENT_TWO,

        // �r���{�[�h-������
        BILLBOARD_TRANSLUCENT_ONE,

        // 2D�I�u�W�F�N�g-�s����
        OBJECT2D_OPACITY_ONE,
        OBJECT2D_OPACITY_TWO,

        // 2D�I�u�W�F�N�g-������
        OBJECT2D_TRANSLUCENT_ONE,
        OBJECT2D_TRANSLUCENT_TWO,

        LAYER_MAX
    };

             GameObject(std::string name = "");
    virtual ~GameObject();

    virtual void Init();
    virtual void Uninit();
    virtual void Update();

    // �R���|�[�l���g�֘A
    void       AddComponent(Component* component);
    Component* GetComponent(std::string name);
    template <typename T> T* AddComponent();
    template <typename T> T* GetComponent();

    // GameObject->tag �ƃ^�O�t������Ă��邩�m�F
    bool CompareTag(std::string tag) { return ((this->tag == tag) ? true : false); }

    void  SetActive(bool value) { activeSelf = value; }
    bool  GetActive() const { return activeSelf; }

    void  SetLayer(LAYER value) { layer = value; }
    LAYER GetLayer() const { return layer; }

private:
    bool        activeSelf;    // GameObject �̃��[�J���̃A�N�e�B�u���
    LAYER       layer;         // ���C���[ (�K�w�ԍ� �����_�����O�����Ȃǂɉe������)
    std::string tag;           // �^�O��
    Transform*  transform;     // GameObject �ɃA�^�b�`����Ă��� Transform

    std::list<Component*> componentList;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//