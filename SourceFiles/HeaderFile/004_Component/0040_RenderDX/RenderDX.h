/**************************************************************************************************

 @File   : [ RenderDX.h ] DirectX�őS�Ẵ����_���[�̂��߂̈�ʓI�ȋ@�\���Ǘ�����N���X (���ۃN���X)
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDERDX_H_
#define _RENDERDX_H_

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
#include "003_Object/Material.h"
#include "008_Utility/Color.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

//-----2DPolygon VertexInformation-----//
typedef struct
{
    Vector3     pos;    // ���_�̈ʒu���W
    COLOR       col;    // ���_�J���[
    D3DXVECTOR2 tex;    // �e�N�X�`�����W

}VERTEX_2D;

//-----3DPolygon VertexInformation-----//
typedef struct
{
    Vector3     pos;    // ���_�̈ʒu���W
    Vector3     nor;    // �@���x�N�g��
    COLOR       col;    // ���_�J���[
    D3DXVECTOR2 tex;    // �e�N�X�`�����W

}VERTEX_3D;

//-----VertexFormat-----//
#define FVF_VERTEX_2D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class RenderDX : public Component
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

             RenderDX(GameObject* pObject, std::string ComponentName, GameObject::LAYER Layer = GameObject::LAYER_ZERO);
    virtual ~RenderDX();

    virtual void Init()   = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;
    virtual void Draw()   = 0;

    virtual void SetVertex() = 0;

    static bool ZSortCompareLess(RenderDX* RenderA, RenderDX* RenderB);
    static bool ZSortCompareGreater(RenderDX* RenderA, RenderDX* RenderB);

    static bool SortingOrderCompareLess(RenderDX* RenderA, RenderDX* RenderB);
    static bool SortingOrderCompareGreater(RenderDX* RenderA, RenderDX* RenderB);

    void SetBlending();
    void SetCulling();

    //-----Setter, Getter-----//
    void              SetLayer(GameObject::LAYER value);
    GameObject::LAYER GetLayer() const { return layer; }

    void      SetBlendType(BLENDTYPE value) { blendType = value; }
    BLENDTYPE GetBlendType() const { return blendType; }
    
    void     SetCullType(CULLTYPE value) { cullingType = value; }
    CULLTYPE GetCullType() const { return cullingType; }

    void  SetZDepth(float value) { zDepth = value; }
    float GetZDepth() const { return zDepth; }

    void  SetSortingOrder(float value) { sortingOrder = value; }
    float GetSortingOrder() const { return sortingOrder; }

    void     SetTexture(std::string value);
    void     SetTexture(Texture* value);
    Texture* GetTexture() { return material.mainTexture; }

    void     SetTextureID(unsigned int value);
    int      GetTextureID() const { return material.mainTextureID; }

    bool enabled;    // True���̂ݕ`����s��

    Material          material;       // �}�e���A�����

private:
    GameObject::LAYER layer;          // �`�揇
    BLENDTYPE         blendType;      // �`�掞�̃u�����h�ݒ�
    CULLTYPE          cullingType;    // �`�掞�̃J�����O�ݒ�

    float zDepth;                     // �J��������I�u�W�F�N�g�܂ł̋��� (Z�\�[�g���ɗ��p)
    float sortingOrder;               // �������C���[���̕`�揇�Ԃ̐���Ɏg�p����
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//