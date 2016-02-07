/**************************************************************************************************

 @File   : [ Render2DDX.h ] 
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDER2DDX_H_
#define _RENDER2DDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderDX.h"

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
class Render2DDX : public RenderDX
{
public:
             Render2DDX(GameObject* pObject, GameObject::LAYER Layer = GameObject::LAYER::OBJECT2D_OPACITY_ONE);
    virtual ~Render2DDX();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw()   override;

    //-----Setter, Getter-----//
    void SetTexture(std::string TextureName);
    int  GetTexture() const { return textureID; }

    void      SetColor(D3DXCOLOR value) { vertexColor = value; }
    D3DXCOLOR GetColor() const { return vertexColor; }

private:
    void SetVertex();

    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;    // ���_�o�b�t�@

    D3DXCOLOR   vertexColor;    // �J���[���
    D3DXVECTOR2 textureUV;      // �e�N�X�`����UV���W�̎��_
    int         textureID;      // �e�N�X�`�����ʔԍ�
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//