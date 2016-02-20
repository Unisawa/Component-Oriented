/**************************************************************************************************

 @File   : [ Render2DDX.cpp ] DirectX��2D�l�p�`�|���S����`�悷��Render�N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderDX.h"
#include "004_Component/0040_RenderDX/Render2DDX.h"
#include "004_Component/0042_GameObject/Transform.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
const std::string Render2DDX::className = "Render2DDX";

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*=================================================================================================
  @Summary: �R���X�g���N�^
  @Details: None
=================================================================================================*/
Render2DDX::Render2DDX(GameObject* pObject, GameObject::LAYER Layer) : RenderDX(pObject, className, Layer)
{

}

/*===============================================================================================* 
  @Summary: �f�X�g���N�^
  @Details: None
 *===============================================================================================*/
Render2DDX::~Render2DDX()
{

}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
void Render2DDX::Init()
{
    vertexColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    textureUV   = D3DXVECTOR2(0.0f, 0.0f);
    textureID   = -1;

    // ���_�o�b�t�@�[�̊m��
    RenderManagerDX::GetDevice()->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &pVertexBuffer, NULL);

    SetVertex();
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void Render2DDX::Uninit()
{
    RenderManagerDX::UnLinkList(this);

    SafeRelease(pVertexBuffer);
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void Render2DDX::Update()
{
    SetVertex();
}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void Render2DDX::Draw()
{
    LPDIRECT3DDEVICE9 pDevice = RenderManagerDX::GetDevice();

    // �`��ݒ�
    SetBlending();
    SetCulling();

    // ���_�o�b�t�@�̕`��ݒ�
    pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_2D));
    pDevice->SetFVF(FVF_VERTEX_2D);

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
void Render2DDX::SetVertex()
{
    VERTEX_2D* pVtx;
    Vector3 Position = this->gameObject->transform->GetPosition();
    Vector3 Scale    = this->gameObject->transform->GetScale();

    // ���_�o�b�t�@�̈�̃��b�N
    pVertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

    // �|���S���̈ʒu���W
    pVtx[0].pos.x = Position.x - Scale.x * 0.5f;
    pVtx[0].pos.y = Position.y - Scale.y * 0.5f;
    pVtx[0].pos.z = 0.0f;

    pVtx[1].pos.x = Position.x + Scale.x * 0.5f;
    pVtx[1].pos.y = Position.y - Scale.y * 0.5f;
    pVtx[1].pos.z = 0.0f;

    pVtx[2].pos.x = Position.x - Scale.x * 0.5f;
    pVtx[2].pos.y = Position.y + Scale.y * 0.5f;
    pVtx[2].pos.z = 0.0f;

    pVtx[3].pos.x = Position.x + Scale.x * 0.5f;
    pVtx[3].pos.y = Position.y + Scale.y * 0.5f;
    pVtx[3].pos.z = 0.0f;

    // �|���S���̓������W--�Œ�--
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

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