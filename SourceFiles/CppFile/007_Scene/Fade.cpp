/**************************************************************************************************

 @File   : [ Fade.cpp ] 画面全体の照度を変化させるフェードクラス
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
#include "007_Scene/Fade.h"
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0040_RenderDX/Render2DDX.h"

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
const std::string Fade::className = "Fade";

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
Fade::Fade(GameObject* pObject) : MonoBehaviour(pObject, className)
{
    fadeTime  = 40;
    fadeCount = 0;

    fadeState = FADE::NONE;
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
Fade::~Fade()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void Fade::Init()
{
    fadeState = FADE::IDOL;

    gameObject->DontDestroyOnLoad(true);
    gameObject->transform->SetScale(Constant::SCREEN_WIDTH, Constant::SCREEN_HEIGHT, 0.0f);

    // Fade用 2Dポリゴン追加
    pRender2D = gameObject->AddComponent<Render2DDX>();
    pRender2D->SetLayer(GameObject::LAYER::OBJECT2D_TRANSLUCENT_TWO);
    pRender2D->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void Fade::Uninit()
{

}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void Fade::Update()
{
    UpdateFadeIn();
    UpdateFadeOut();
}

/*===============================================================================================* 
  @Summary: FadeIn中の処理
  @Details: None
 *===============================================================================================*/
void Fade::UpdateFadeIn()
{
    if (fadeState != FADE::FADEIN) return;

    // α計算
    D3DXCOLOR Color = pRender2D->GetColor();
    Color.a = 1.0f * (1 - ((float) fadeCount / fadeTime));

    // 頂点情報の更新
    pRender2D->SetColor(Color);

    // フェードが終われば、フェード実行状態を解除
    if (fadeTime < ++fadeCount)
    {
        fadeCount = fadeTime;
        fadeState = FADE::IDOL;
    }
}

/*===============================================================================================* 
  @Summary: FadeOut中の処理
  @Details: None
 *===============================================================================================*/
void Fade::UpdateFadeOut()
{
    if (fadeState != FADE::FADEOUT) return;

    // α計算
    D3DXCOLOR Color = pRender2D->GetColor();
    Color.a = 1.0f * ((float) fadeCount / fadeTime);

    // 頂点情報の更新
    pRender2D->SetColor(Color);

    // フェードが終われば、フェード実行状態を解除
    if (fadeTime < ++fadeCount)
    {
        fadeCount = fadeTime;
        fadeState = FADE::IDOL;
    }
}

/*===============================================================================================* 
  @Summary: FadeInを開始する
  @Details: None
 *===============================================================================================*/
void Fade::FadeIn()
{
    if (fadeState == FADE::IDOL)
    {
        fadeState = FADE::FADEIN;
        fadeCount = 0;
    }
}

/*===============================================================================================* 
  @Summary: FadeOutを開始する
  @Details: None
 *===============================================================================================*/
void Fade::FadeOut()
{
    if (fadeState == FADE::IDOL)
    {
        fadeState = FADE::FADEOUT;
        fadeCount = 0;
    }
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