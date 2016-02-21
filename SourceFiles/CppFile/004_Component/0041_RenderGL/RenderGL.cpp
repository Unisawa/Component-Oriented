/**************************************************************************************************

 @File   : [ RenderGL.cpp ] OpenGL�őS�Ẵ����_���[�̂��߂̈�ʓI�ȋ@�\���Ǘ�����N���X (���ۃN���X)
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
#include "004_Component/0041_RenderGL/RenderGL.h"
#include "004_Component/0041_RenderGL/RenderGLManager.h"

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
  @Summary: �R���X�g���N�^
  @Details: None
=================================================================================================*/
RenderGL::RenderGL(GameObject* pObject, std::string ComponentName, GameObject::LAYER Layer) : Component(pObject, RENDERER, ComponentName)
{
    enabled = true;
    zDepth  = 1.0f;

    SetLayer(Layer);

    RenderGLManager::LinkList(this, Layer);
}

/*===============================================================================================* 
  @Summary: �f�X�g���N�^
  @Details: None
 *===============================================================================================*/
RenderGL::~RenderGL()
{

}

/*===============================================================================================* 
  @Summary: ZDepth�̒l���Q�l�Ƀ\�[�g���� B�ɑ΂���A�̕�����������
  @Details: None
 *===============================================================================================*/
bool RenderGL::ZSortCompareLess(RenderGL* RenderA, RenderGL* RenderB)
{
    return RenderA->GetZDepth() < RenderB->GetZDepth();
}

/*===============================================================================================* 
  @Summary: ZDepth�̒l���Q�l�Ƀ\�[�g���� B�ɑ΂���A�̕����傫����
  @Details: None
 *===============================================================================================*/
bool RenderGL::ZSortCompareGreater(RenderGL* RenderA, RenderGL* RenderB)
{
    return RenderA->GetZDepth() > RenderB->GetZDepth();
}

/*===============================================================================================* 
  @Summary: Render�����u�����h�ݒ���s��
  @Details: None
 *===============================================================================================*/
void RenderGL::SetBlending()
{
    // �u�����h Off
    glDisable(GL_BLEND);

    // �u�����h�ݒ�
    switch (blendType)
    {
        // �u�����h���Ȃ�
        case BLENDTYPE_NOTBLEND:
            glDisable(GL_BLEND);
            break;

        // �A���t�@�u�����h
        case BLENDTYPE_NORMAL:
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;

        // ���Z����
        case BLENDTYPE_ADD:
            break;

        // �����Z����
        case BLENDTYPE_ADD_SOFT:
            break;

        // ���Z����
        case BLENDTYPE_SUBTRACT:
            break;

        default:
            break;
    }
}

/*===============================================================================================* 
  @Summary: Render�����J�����O�ݒ���s��
  @Details: None
 *===============================================================================================*/
void RenderGL::SetCulling()
{
    //LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    //// �J�����O�̃��Z�b�g (���J�����O����{�Ƃ���)
    //pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    //// �J�����O�ݒ�
    //switch (cullingType)
    //{
    //    // �J�����O���Ȃ�
    //    case CULLTYPE_NONE:
    //        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    //        break;

    //    // �\�J�����O
    //    case CULLTYPE_CW:
    //        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    //        break;

    //    // ���J�����O
    //    case CULLTYPE_CCW:
    //        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    //        break;

    //    default:
    //        break;
    //}
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