/**************************************************************************************************

 @File   : [ Fade.cpp ] 画面全体の照度を変化させるフェードクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "007_Scene/0070_Fade/Fade.h"

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
Fade::Fade(GameObject* pObject, std::string className) : MonoBehaviour(pObject, className)
{
    fadeTime  = 20;
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

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
