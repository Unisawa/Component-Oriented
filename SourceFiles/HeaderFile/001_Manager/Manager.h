/**************************************************************************************************

 @File   : [ Manager.h ] �Q�[���S�ʂɕK�v�Ȋe��Manager���Ǘ�����N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _MANAGER_H_
#define _MANAGER_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//
#include "004_Component/0040_RenderDX/RenderDXManager.h"
#include "004_Component/0041_RenderGL/RenderGLManager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define USE_DIRECTX    // DirectX�̎g�p�錾
//#define USE_OPENGL     // OpenGL �̎g�p�錾

#ifdef USE_DIRECTX
    #include "008_Utility/MatrixDX.h"
#endif

#ifdef USE_OPENGL
    #include "008_Utility/MatrixGL.h"
#endif

#include "004_Component/0042_GameObject/Transform.h"

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class InputManager;

class RenderDXManager;
class RenderGLManager;
class GameObjectManager;
class SceneManager;

class Manager
{
public:
     Manager() {}
    ~Manager() {}

    HRESULT Init();
    void    Uninit();
    void    Update();
    void    Draw();

    static InputManager* GetInputManager() { return pInputManager; }

    static RenderDXManager* GetRenderDXManager() { return pRenderDXManager; }
    static RenderGLManager* GetRenderGLManager() { return pRenderGLManager; }

    static GameObjectManager* GetGameObjectManager() { return pGameObjectManager; }
    static SceneManager*      GetSceneManager() { return pSceneManager; }

private:
    static InputManager* pInputManager;

    static RenderDXManager* pRenderDXManager;
    static RenderGLManager* pRenderGLManager;

    static GameObjectManager* pGameObjectManager;
    static SceneManager*      pSceneManager;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//