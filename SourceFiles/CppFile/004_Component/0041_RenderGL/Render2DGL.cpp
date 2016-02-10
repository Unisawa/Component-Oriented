/**************************************************************************************************

 @File   : [ Render2DGL.cpp ] OpenGL��2D�l�p�`�|���S����`�悷��Render�N���X
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
#include "004_Component/0041_RenderGL/RenderGL.h"
#include "004_Component/0041_RenderGL/Render2DGL.h"
#include "004_Component/0042_GameObject/Transform.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
const std::string Render2DGL::className = "Render2DGL";

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*=================================================================================================
  @Summary: �R���X�g���N�^
  @Details: None
=================================================================================================*/
Render2DGL::Render2DGL(GameObject* pObject, GameObject::LAYER Layer) : RenderGL(pObject, className, Layer)
{

}

/*===============================================================================================* 
  @Summary: �f�X�g���N�^
  @Details: None
 *===============================================================================================*/
Render2DGL::~Render2DGL()
{

}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
void Render2DGL::Init()
{
    textureID = -1;
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void Render2DGL::Uninit()
{

}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void Render2DGL::Update()
{

}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void Render2DGL::Draw()
{
    Transform* pTransform = this->gameObject->GetTransform();

    float x = pTransform->GetPosition().x;
    float y = pTransform->GetPosition().y;

    float SizeX = pTransform->GetScale().x;
    float SizeY = pTransform->GetScale().y;

    // �`��ݒ�
    SetBlending();
    SetCulling();

    // �e�N�X�`���Z�b�g
    //glBindTexture(GL_TEXTURE_2D,textureID);

    // �`��J�n
    glBegin(GL_TRIANGLE_STRIP);

    // ����
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x - SizeX * 0.5f,
               y - SizeY * 0.5f,
                           0.0f);

    // �E��
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + SizeX * 0.5f,
               y - SizeY * 0.5f,
                           0.0f);

    // ����O
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x - SizeX * 0.5f,
               y + SizeY * 0.5f,
                           0.0f);

    // �E��O
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x + SizeX * 0.5f,
               y + SizeY * 0.5f,
                           0.0f);

    // �`��I��
    glEnd();
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