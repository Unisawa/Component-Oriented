/**************************************************************************************************

 @File   : [ RenderDX.h ] �S�Ẵ����_���[�̂��߂̈�ʓI�ȋ@�\���Ǘ�����N���X
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
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "004_Component/0042_GameObject/GameObject.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//-----2DPolygon VertexInformation-----//
typedef struct
{
    D3DXVECTOR3 pos;    // ���_�̈ʒu���W
    float       rhw;    // 3D�ɂ�����2D�e�N�X�`���̂䂪�ݕ␳�̃f�[�^ �p�[�X�y�N�e�B�u�R���N�g
    D3DCOLOR    col;    // ���_�J���[
    D3DXVECTOR2 tex;    // �e�N�X�`�����W

}VERTEX_2D;

//-----3DPolygon VertexInformation-----//
typedef struct
{
    D3DXVECTOR3 pos;    // ���_�̈ʒu���W
    D3DXVECTOR3 nor;    // �@���x�N�g��
    D3DCOLOR    col;    // ���_�J���[
    D3DXVECTOR2 tex;    // �e�N�X�`�����W

}VERTEX_3D;

//-----VertexFormat-----//
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class RenderDX : public Component
{
public:
             RenderDX(GameObject::LAYER Layer = GameObject::LAYER_ZERO);
    virtual ~RenderDX();

    virtual void Init()   = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;
    virtual void Draw()   = 0;

    static bool ZSortCompareLess(RenderDX* RenderA, RenderDX* RenderB);
    static bool ZSortCompareGreater(RenderDX* RenderA, RenderDX* RenderB);

    //-----Setter, Getter-----//
    void              SetLayer(GameObject::LAYER value) { layer = value; }
    GameObject::LAYER GetLayer() const { return layer; }

    float GetZDepth() const { return zDepth; }

    bool enabled;    // True���̂ݕ`����s��

private:
    GameObject::LAYER layer;    // �`�揇

    float zDepth;    // �J��������I�u�W�F�N�g�܂ł̋��� (Z�\�[�g���ɗ��p)
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//