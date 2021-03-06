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
#include "008_Utility/Color.h"

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

             Fade(GameObject* pObject, std::string className);
    virtual ~Fade();

    virtual void Init()   = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;

    void FadeIn();
    void FadeOut();

    virtual void SetColor(Color value) {}

    FADE GetFadeState() const { return fadeState; }

protected:
    virtual void UpdateFadeIn()  {}
    virtual void UpdateFadeOut() {}

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