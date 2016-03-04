/**************************************************************************************************

 @File   : [ Fade.h ] 画面全体の照度を変化させるフェードクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _FADE_H_
#define _FADE_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0043_Behaviour/MonoBehaviour.h"
#include "007_Scene/Fade.h"

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
class Render2DDX;
class Color;

class Fade : public MonoBehaviour
{
public:

    static const enum FADE
    {
        NONE = -1,

        IDOL,
        FADEIN,
        FADEOUT,

        MAX
    };

             Fade(GameObject* pObject);
    virtual ~Fade();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;

    void FadeIn();
    void FadeOut();

    void SetColor(Color value);

    static const std::string className;

    FADE GetFadeState() const { return fadeState; }

private:
    void UpdateFadeIn();
    void UpdateFadeOut();

    Render2DDX* pRender2D;

    FADE fadeState;
    int  fadeTime;
    int  fadeCount;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//