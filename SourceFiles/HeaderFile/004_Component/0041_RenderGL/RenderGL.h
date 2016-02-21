/**************************************************************************************************

 @File   : [ RenderGL.h ] OpenGL�őS�Ẵ����_���[�̂��߂̈�ʓI�ȋ@�\���Ǘ�����N���X (���ۃN���X)
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDERGL_H_
#define _RENDERGL_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "004_Component/0042_GameObject/GameObject.h"

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
class RenderGL : public Component
{
public:

    static const enum BLENDTYPE
    {
        BLENDTYPE_NOTBLEND = 0,    // �u�����h���Ȃ�

        BLENDTYPE_NORMAL,          // �A���t�@�u�����h
        BLENDTYPE_ADD,             // ���Z����
        BLENDTYPE_ADD_SOFT,        // �����Z����
        BLENDTYPE_SUBTRACT,        // ���Z����

        BLENDTYPE_MAX
    };

    static const enum CULLTYPE
    {
        CULLTYPE_NONE = 0,    // �J�����O���Ȃ�
        CULLTYPE_CW,          // �\�J�����O
        CULLTYPE_CCW,         // ���J�����O

        CULLTYPE_MAX
    };

             RenderGL(GameObject* pObject, std::string ComponentName, GameObject::LAYER Layer = GameObject::LAYER_ZERO);
    virtual ~RenderGL();

    virtual void Init()   = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;
    virtual void Draw()   = 0;
    
    static bool ZSortCompareLess(RenderGL* RenderA, RenderGL* RenderB);
    static bool ZSortCompareGreater(RenderGL* RenderA, RenderGL* RenderB);

    void SetBlending();
    void SetCulling();

    //-----Setter, Getter-----//
    void              SetLayer(GameObject::LAYER value) { layer = value; }
    GameObject::LAYER GetLayer() const { return layer; }

    void      SetBlendType(BLENDTYPE value) { blendType = value; }
    BLENDTYPE GetBlendType() const { return blendType; }
    
    void     SetCullType(CULLTYPE value) { cullingType = value; }
    CULLTYPE GetCullType() const { return cullingType; }

    float GetZDepth() const { return zDepth; }

    bool enabled;    // True���̂ݕ`����s��

private:
    GameObject::LAYER layer;          // �`�揇
    BLENDTYPE         blendType;      // �`�掞�̃u�����h�ݒ�
    CULLTYPE          cullingType;    // �`�掞�̃J�����O�ݒ�

    float zDepth;    // �J��������I�u�W�F�N�g�܂ł̋��� (Z�\�[�g���ɗ��p)
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//