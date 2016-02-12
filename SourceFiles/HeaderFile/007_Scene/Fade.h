/**************************************************************************************************

 @File   : [ Fade.h ] ��ʑS�̂̏Ɠx��ω�������t�F�[�h�N���X
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
#include "002_Manager/Manager.h"

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

    virtual void Init();
    virtual void Uninit();
    virtual void Update();

    void FadeIn();
    void FadeOut();

    static const std::string className;

    FADE GetFadeState() { return fadeState; }

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