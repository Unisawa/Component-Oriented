/**************************************************************************************************

 @File   : [ RenderDX.cpp ] DirectXで全てのレンダラーのための一般的な機能を管理するクラス (抽象クラス)
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderDX.h"
#include "004_Component/0040_RenderDX/RenderDXManager.h"

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

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
RenderDX::RenderDX(GameObject* pObject, std::string ComponentName, GameObject::LAYER Layer) : Component(pObject, RENDERER, ComponentName)
{
    enabled   = true;
    zDepth    = 1.0f;
    layer     = Layer;
    transform = pObject->transform;

    blendType   = BLENDTYPE::BLENDTYPE_NORMAL;
    cullingType = CULLTYPE::CULLTYPE_CCW;

    RenderDXManager::LinkList(this, Layer);
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
RenderDX::~RenderDX()
{

}

/*===============================================================================================* 
  @Summary: ZDepthの値を参考にソートする Bに対してAの方が小さいか
  @Details: None
 *===============================================================================================*/
bool RenderDX::ZSortCompareLess(RenderDX* RenderA, RenderDX* RenderB)
{
    return RenderA->GetZDepth() < RenderB->GetZDepth();
}

/*===============================================================================================* 
  @Summary: ZDepthの値を参考にソートする Bに対してAの方が大きいか
  @Details: None
 *===============================================================================================*/
bool RenderDX::ZSortCompareGreater(RenderDX* RenderA, RenderDX* RenderB)
{
    return RenderA->GetZDepth() > RenderB->GetZDepth();
}

/*===============================================================================================* 
  @Summary: Renderが持つブレンド設定を行う
  @Details: None
 *===============================================================================================*/
void RenderDX::SetBlending()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // ブレンドモードのリセット (アルファブレンドを基本とする)
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    // ブレンド設定
    switch (blendType)
    {
        // ブレンドしない
        case BLENDTYPE_NOTBLEND:
            pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            break;

        // アルファブレンド
        case BLENDTYPE_NORMAL:
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
            break;

        // 加算合成 (α無)
        case BLENDTYPE_ADD:
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
            break;

        // 加算合成 (α有)
        case BLENDTYPE_ADD_SOFT:
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
            break;

        // 減算合成
        case BLENDTYPE_SUBTRACT:
            pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
            break;

        default:
            break;
    }
}

/*===============================================================================================* 
  @Summary: Renderが持つカリング設定を行う
  @Details: None
 *===============================================================================================*/
void RenderDX::SetCulling()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // カリングのリセット (裏カリングを基本とする)
    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    // カリング設定
    switch (cullingType)
    {
        // カリングしない
        case CULLTYPE_NONE:
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
            break;

        // 表カリング
        case CULLTYPE_CW:
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
            break;

        // 裏カリング
        case CULLTYPE_CCW:
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
            break;

        default:
            break;
    }
}

/*===============================================================================================* 
  @Summary: Layer (描画順) を変更する
  @Details: None
 *===============================================================================================*/
void RenderDX::SetLayer(GameObject::LAYER value)
{
    if (layer == value) return;

    RenderDXManager::UnLinkList(this);
    layer = value;
    RenderDXManager::LinkList(this, value);
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//