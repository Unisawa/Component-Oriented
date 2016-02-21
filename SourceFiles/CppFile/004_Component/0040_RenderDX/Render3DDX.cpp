/**************************************************************************************************

 @File   : [ Render3DDX.cpp ] DirectX��3D�l�p�`�|���S����`�悷��Render�N���X
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
#include "004_Component/0040_RenderDX/Render3DDX.h"
#include "004_Component/0042_GameObject/Transform.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
const std::string Render3DDX::className = "Render3DDX";

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*=================================================================================================
  @Summary: �R���X�g���N�^
  @Details: None
=================================================================================================*/
Render3DDX::Render3DDX(GameObject* pObject, GameObject::LAYER Layer) : RenderDX(pObject, className, Layer)
{

}

/*===============================================================================================* 
  @Summary: �f�X�g���N�^
  @Details: None
 *===============================================================================================*/
Render3DDX::~Render3DDX()
{

}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
void Render3DDX::Init()
{
    size        = Vector3(10.0f, 0.0f, 10.0f);

    vertexColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    textureUV   = D3DXVECTOR2(0.0f, 0.0f);
    textureID   = -1;

    // ���_�o�b�t�@�[�̊m��
    RenderDXManager::GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &pVertexBuffer, NULL);

    SetVertex();
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void Render3DDX::Uninit()
{
    RenderDXManager::UnLinkList(this);

    SafeRelease(pVertexBuffer);
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void Render3DDX::Update()
{
    SetVertex();
}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void Render3DDX::Draw()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // �`��ݒ�
    SetBlending();
    SetCulling();

    // ���_�o�b�t�@�̕`��ݒ�
    pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));
    pDevice->SetFVF(FVF_VERTEX_3D);

    // �e�N�X�`���̓ǂݍ��� �|���S���̕`��
    pDevice->SetTexture(0, NULL);
    //pDevice->SetTexture(0, TextureManager::GetTexture(TextureID));
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    // �e�N�X�`�����Z�b�g
    pDevice->SetTexture(0, NULL);
}

/*===============================================================================================* 
  @Summary: ���_���̍X�V
  @Details: None
 *===============================================================================================*/
void Render3DDX::SetVertex()
{
    VERTEX_3D* pVtx;
    Vector3 Position = this->gameObject->transform->GetPosition();
    Vector3 Scale    = this->gameObject->transform->GetScale();

    // ���_�o�b�t�@�̈�̃��b�N
    pVertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

    // �|���S���̈ʒu���W
    pVtx[0].pos.x = -size.x;
    pVtx[0].pos.y =  0.0f;
    pVtx[0].pos.z =  size.z;

    pVtx[1].pos.x =  size.x;
    pVtx[1].pos.y =  0.0f;
    pVtx[1].pos.z =  size.z;

    pVtx[2].pos.x = -size.x;
    pVtx[2].pos.y =  0.0f;
    pVtx[2].pos.z = -size.z;

    pVtx[3].pos.x =  size.x;
    pVtx[3].pos.y =  0.0f;
    pVtx[3].pos.z = -size.z;

    // �|���S���̓������W--�Œ�--
    pVtx[0].nor = Vector3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = Vector3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = Vector3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = Vector3(0.0f, 1.0f, 0.0f);

    // �|���S���̃J���[���
    pVtx[0].col = vertexColor;
    pVtx[1].col = vertexColor;
    pVtx[2].col = vertexColor;
    pVtx[3].col = vertexColor;

    // �|���S���̃e�N�X�`�����W
    pVtx[0].tex = D3DXVECTOR2(textureUV.x + 0.0f, textureUV.y + 0.0f);
    pVtx[1].tex = D3DXVECTOR2(textureUV.x + 1.0f, textureUV.y + 0.0f);
    pVtx[2].tex = D3DXVECTOR2(textureUV.x + 0.0f, textureUV.y + 1.0f);
    pVtx[3].tex = D3DXVECTOR2(textureUV.x + 1.0f, textureUV.y + 1.0f);

    // ���_�o�b�t�@�̈�̃A�����b�N
    pVertexBuffer->Unlock();
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