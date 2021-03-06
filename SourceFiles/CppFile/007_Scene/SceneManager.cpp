/**************************************************************************************************

 @File   : [ SceneManager.cpp ] 画面遷移を管理するクラス
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
#include "007_Scene/SceneManager.h"
#include "007_Scene/SceneTitle.h"
#include "007_Scene/SceneGame.h"
#include "007_Scene/SceneResult.h"
#include "007_Scene/SceneOpenGL.h"

#include "007_Scene/0070_Fade/FadeDX.h"
#include "007_Scene/0070_Fade/FadeGL.h"

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
Scene* SceneManager::pScene;
Scene* SceneManager::pSceneNext;
bool   SceneManager::isShiftNow = 0;
int    SceneManager::intervalFrameByShift = -1;

Fade*  SceneManager::pFade = NULL;

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
SceneManager::SceneManager()
{
    pScene = &Scene::TITLE;

#ifdef USE_OPENGL
    pScene = &Scene::OPENGL;
#endif
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
SceneManager::~SceneManager()
{

}

/*===============================================================================================* 
  @Summary: 生成処理
  @Details: None
 *===============================================================================================*/
SceneManager *SceneManager::Create()
{
    SceneManager* pSceneManager;
    pSceneManager = new SceneManager();
    pSceneManager->Init();

    return pSceneManager;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void SceneManager::Init()
{
    shiftState = 0;

    // フェードフィルターの作成
    GameObject* pFadeGameObject = new GameObject("Fade Filter");

#ifdef USE_DIRECTX
    pFade = pFadeGameObject->AddComponent<FadeDX>();
#endif
#ifdef USE_OPENGL
    pFade = pFadeGameObject->AddComponent<FadeGL>();
#endif
    pFade->SetColor(Color::white);

    // 初回起動時のシーンの初期化
    pScene->Init();
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void SceneManager::Uninit()
{
    pScene->Uninit();

    pFade->Uninit();
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void SceneManager::Update()
{
    pScene->Update();

    // 画面遷移の状態管理
    CheckChange();
}

/*===============================================================================================* 
  @Summary: 画面遷移を開始する
  @Details: None
 *===============================================================================================*/
void SceneManager::StartChange()
{
    shiftState = 1;

    pFade->FadeOut();
}

/*===============================================================================================* 
  @Summary: 画面遷移に関する処理
  @Details: None
 *===============================================================================================*/
void SceneManager::CheckChange()
{
    // 画面遷移を開始する時
    if (intervalFrameByShift >= 0)
    {
        --intervalFrameByShift;
        if (intervalFrameByShift < 0)
        {
            StartChange();
        }
    }

    // 以下、画面遷移中の処理
    if (shiftState == 0) return;

    // FadeOut終了
    if ((shiftState == 1) && pFade->GetFadeState() == Fade::FADE::IDOL)
    {
        shiftState = 2;

        // 画面遷移
        ChangeScene(pSceneNext);

        pFade->FadeIn();
    }

    // FadeIn終了 (画面遷移完了)
    if ((shiftState == 2) && pFade->GetFadeState() == Fade::FADE::IDOL)
    {
        shiftState = 0;
        isShiftNow = false;
    }
}

/*===============================================================================================* 
  @Summary: 指定したSceneに切り替え、前回のSceneを返す
  @Details: None
 *===============================================================================================*/
Scene* SceneManager::ChangeScene(Scene* pNextScene)
{
    Scene* pBeforeScene = pScene;

    pBeforeScene->Uninit();
    pScene = pNextScene;
    pNextScene->Init();

    return pBeforeScene;
}

/*===============================================================================================* 
  @Summary: インターバルのフレーム数が経過してから画面遷移を開始するように設定をする
  @Details: IntervalFrameは 0 以上の数 (0 <= x)
 *===============================================================================================*/
void SceneManager::LoadLevel(Scene* pNext, int IntervalFrame)
{
    if (!isShiftNow)
    {
        isShiftNow = true;

        pSceneNext = pNext;
        intervalFrameByShift = IntervalFrame;
    }
}

/*===============================================================================================* 
  @Summary: すぐに画面遷移を行う FadeDX無し
  @Details: None
 *===============================================================================================*/
void SceneManager::LoadLevelQuick(Scene* pNext)
{
    Scene* pBeforeScene = pScene;

    pBeforeScene->Uninit();
    pScene = pNext;
    pNext->Init();
}

/*===============================================================================================* 
  @Summary: 現在のシーン名を返す
  @Details: None
 *===============================================================================================*/
std::string SceneManager::GetNowSceneName()
{
    return pScene->GetSceneName();
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
