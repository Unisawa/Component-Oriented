/**************************************************************************************************

 @File   : [ SceneManager.h ] 画面遷移を管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"

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
class Scene;
class Fade;

class SceneManager
{
public:
     SceneManager();
    ~SceneManager();

    static SceneManager* Create();

    void Init();
    void Uninit();
    void Update();

    void   StartChange();
    void   CheckChange();
    Scene* ChangeScene(Scene* pNextScene);

    static void LoadLevel(Scene* pNext, int IntervalFrame = 0.0f);
    static void LoadLevelQuick(Scene* pNext);

private:
    static Scene* pScene;                  // 現在のシーン
    static Scene* pSceneNext;              // 次に変更するシーン
    static bool   isShiftNow;              // Scene遷移中かどうか
    static int    intervalFrameByShift;    // Scene遷移するまでのインターバル

    static Fade* pFade;

    int shiftState;    // シーン遷移中の状態を管理する
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//