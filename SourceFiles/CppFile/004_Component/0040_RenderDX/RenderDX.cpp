/**************************************************************************************************

 @File   : [ RenderDX.cpp ] DirectX�őS�Ẵ����_���[�̂��߂̈�ʓI�ȋ@�\���Ǘ�����N���X (���ۃN���X)
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderDX.h"
#include "004_Component/0040_RenderDX/RenderDXManager.h"
#include "004_Component/0040_RenderDX/00403_Texture/TextureDXManager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*=================================================================================================
  @Summary: �R���X�g���N�^
  @Details: None
=================================================================================================*/
RenderDX::RenderDX(GameObject* pObject, std::string ComponentName, GameObject::LAYER Layer) : Component(pObject, RENDERER, ComponentName)
{
    enabled      = true;
    zDepth       = 1.0f;
    sortingOrder = 0.0f;
    layer        = Layer;
    transform    = pObject->transform;
    isLighiting  = true;

    blendType    = BLENDTYPE::BLENDTYPE_NORMAL;
    cullingType  = CULLTYPE::CULLTYPE_CCW;

    RenderDXManager::LinkList(this, Layer);
}

/*===============================================================================================* 
  @Summary: �f�X�g���N�^
  @Details: None
 *===============================================================================================*/
RenderDX::~RenderDX()
{

}

/*===============================================================================================* 
  @Summary: ZDepth�̒l���Q�l�Ƀ\�[�g���� B�ɑ΂���A�̕�����������
  @Details: None
 *===============================================================================================*/
bool RenderDX::ZSortCompareLess(RenderDX* RenderA, RenderDX* RenderB)
{
    return RenderA->GetZDepth() < RenderB->GetZDepth();
}

/*===============================================================================================* 
  @Summary: ZDepth�̒l���Q�l�Ƀ\�[�g���� B�ɑ΂���A�̕����傫����
  @Details: None
 *===============================================================================================*/
bool RenderDX::ZSortCompareGreater(RenderDX* RenderA, RenderDX* RenderB)
{
    return RenderA->GetZDepth() > RenderB->GetZDepth();
}

/*===============================================================================================* 
  @Summary: sortingOrder�̒l���Q�l�Ƀ\�[�g���� B�ɑ΂���A�̕�����������
  @Details: None
 *===============================================================================================*/
bool RenderDX::SortingOrderCompareLess(RenderDX* RenderA, RenderDX* RenderB)
{
    return RenderA->GetSortingOrder() < RenderB->GetSortingOrder();
}

/*===============================================================================================* 
  @Summary: sortingOrder�̒l���Q�l�Ƀ\�[�g���� B�ɑ΂���A�̕����傫����
  @Details: None
 *===============================================================================================*/
bool RenderDX::SortingOrderCompareGreater(RenderDX* RenderA, RenderDX* RenderB)
{
    return RenderA->GetSortingOrder() > RenderB->GetSortingOrder();
}

/*===============================================================================================* 
  @Summary: Rendering�̐ݒ���s��
  @Details: �`�悷��O�ɕK���ĂԊ֐�
 *===============================================================================================*/
void RenderDX::SetUpRendering()
{
    // �`��ݒ�
    SetUpBlending();
    SetUpCulling();
    SetUpMaterial();

    // ���C�g�ݒ�
    if (isLighiting)
    {
        RenderDXManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
    }
    else
    {
        RenderDXManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
    }
}

/*===============================================================================================* 
  @Summary: Rendering�̐ݒ����������
  @Details: �`�悵�I�������K���ĂԊ֐�
 *===============================================================================================*/
void RenderDX::ResetRendering()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // �e�N�X�`���̃��Z�b�g
    pDevice->SetTexture(0, TextureDXManager::GetTexture(NULL));
}

/*===============================================================================================* 
  @Summary: Render�����u�����h�ݒ���s��
  @Details: None
 *===============================================================================================*/
void RenderDX::SetUpBlending()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // �u�����h���[�h�̃��Z�b�g (�A���t�@�u�����h����{�Ƃ���)
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    // �u�����h�ݒ�
    switch (blendType)
    {
        // �u�����h���Ȃ�
        case BLENDTYPE_NOTBLEND:
            pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            break;

        // �A���t�@�u�����h
        case BLENDTYPE_NORMAL:
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
            break;

        // ���Z���� (����)
        case BLENDTYPE_ADD:
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
            break;

        // ���Z���� (���L)
        case BLENDTYPE_ADD_SOFT:
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
            break;

        // ���Z����
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
  @Summary: Render�����J�����O�ݒ���s��
  @Details: None
 *===============================================================================================*/
void RenderDX::SetUpCulling()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // �J�����O�̃��Z�b�g (���J�����O����{�Ƃ���)
    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    // �J�����O�ݒ�
    switch (cullingType)
    {
        // �J�����O���Ȃ�
        case CULLTYPE_NONE:
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
            break;

        // �\�J�����O
        case CULLTYPE_CW:
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
            break;

        // ���J�����O
        case CULLTYPE_CCW:
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
            break;

        default:
            break;
    }
}

/*===============================================================================================* 
  @Summary: Render�����}�e���A���̐ݒ���s��
  @Details: None
 *===============================================================================================*/
void RenderDX::SetUpMaterial()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // �e�N�X�`���̃Z�b�g
    pDevice->SetTexture(0, TextureDXManager::GetTexture(material.mainTextureID));
}

/*===============================================================================================* 
  @Summary: Layer (�`�揇) ��ύX����
  @Details: None
 *===============================================================================================*/
void RenderDX::SetLayer(GameObject::LAYER value)
{
    if (layer == value) return;

    RenderDXManager::UnLinkList(this);
    layer = value;
    RenderDXManager::LinkList(this, value);
}

/*===============================================================================================* 
  @Summary: �w�肵���e�N�X�`�����̃e�N�X�`����ݒ肷��
  @Details: ���ǂݍ��݂̏ꍇ�͓ǂݍ���
 *===============================================================================================*/
void RenderDX::SetTexture(std::string value)
{
    material.mainTexture = TextureDXManager::Load(value);

    if (material.mainTexture != NULL)
    {
        material.mainTextureID = material.mainTexture->textureID;
    }
}

/*===============================================================================================* 
  @Summary: �w�肵���e�N�X�`���N���X�𒼐ڐݒ肷��
  @Details: None
 *===============================================================================================*/
void RenderDX::SetTexture(Texture* value)
{
    material.mainTexture   = value;
    material.mainTextureID = value->textureID;

    value->repeatedNum++;    // ���̃e�N�X�`�����g�p���Ă��鐔�����������ߑ���������
}

/*===============================================================================================* 
  @Summary: �w�肵���e�N�X�`��ID(Hash�l)�𒼐ڐݒ肷��
  @Details: None
 *===============================================================================================*/
void RenderDX::SetTextureID(unsigned int value)
{
    material.mainTextureID = value;
}

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
