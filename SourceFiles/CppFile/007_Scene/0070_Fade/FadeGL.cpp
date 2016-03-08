/**************************************************************************************************

 @File   : [ FadeGL.cpp ] ��ʑS�̂̏Ɠx��ω�������t�F�[�h�N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"
#include "002_Constant/Constant.h"

//-----Object-----//
#include "007_Scene/0070_Fade/FadeGL.h"
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0041_RenderGL/Render2DGL.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_OPENGL

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//
const std::string FadeGL::className = "FadeGL";

/*=================================================================================================
  @Summary: �R���X�g���N�^
  @Details: None
=================================================================================================*/
FadeGL::FadeGL(GameObject* pObject) : Fade(pObject, className)
{
    fadeTime  = 20;
    fadeCount = 0;

    fadeState = FADE::NONE;
}

/*===============================================================================================* 
  @Summary: �f�X�g���N�^
  @Details: None
 *===============================================================================================*/
FadeGL::~FadeGL()
{

}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
void FadeGL::Init()
{
    fadeState = FADE::IDOL;

    // ��ʑJ�ڒ��̏����Ȃ̂ŉ�ʑJ�ڂ��Ă������Ȃ�
    gameObject->transform->SetPosition(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f);
    gameObject->DontDestroyOnLoad(true);

    // FadeGL�p 2D�|���S���ǉ�
    pRender2D = gameObject->AddComponent<Render2DGL>();
    pRender2D->SetSize(Vector2(Constant::SCREEN_WIDTH, Constant::SCREEN_HEIGHT));
    pRender2D->SetLayer(GameObject::LAYER::OBJECT2D_TRANSLUCENT_TWO);
    pRender2D->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void FadeGL::Uninit()
{

}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void FadeGL::Update()
{
    UpdateFadeIn();
    UpdateFadeOut();
}

/*===============================================================================================* 
  @Summary: FadeIn���̏���
  @Details: None
 *===============================================================================================*/
void FadeGL::UpdateFadeIn()
{
    if (fadeState != FADE::FADEIN) return;

    // ���v�Z
    Color color = pRender2D->GetColor();
    color.a = 1.0f * (1 - ((float)fadeCount / fadeTime));

    // ���_���̍X�V
    pRender2D->SetColor(color);

    // �t�F�[�h���I���΁A�t�F�[�h���s��Ԃ�����
    if (fadeTime < ++fadeCount)
    {
        fadeCount = fadeTime;
        fadeState = FADE::IDOL;
    }
}

/*===============================================================================================* 
  @Summary: FadeOut���̏���
  @Details: None
 *===============================================================================================*/
void FadeGL::UpdateFadeOut()
{
    if (fadeState != FADE::FADEOUT) return;

    // ���v�Z
    Color color = pRender2D->GetColor();
    color.a     = 1.0f * ((float)fadeCount / fadeTime);

    // ���_���̍X�V
    pRender2D->SetColor(color);

    // �t�F�[�h���I���΁A�t�F�[�h���s��Ԃ�����
    if (fadeTime < ++fadeCount)
    {
        fadeCount = fadeTime;
        fadeState = FADE::IDOL;
    }
}

/*===============================================================================================* 
  @Summary: FadeGL����F��ݒ肷��
  @Details: �������t�F�[�h���ɑ��삷��̂ō��͐ݒ�ł��Ȃ��悤�ɂ��Ă���
 *===============================================================================================*/
void FadeGL::SetColor(Color value)
{
    pRender2D->material.color.r = value.r;
    pRender2D->material.color.g = value.g;
    pRender2D->material.color.b = value.b;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
