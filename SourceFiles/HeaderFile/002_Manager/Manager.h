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
#include "004_Component/0040_RenderDX/RenderManagerDX.h"
#include "004_Component/0041_RenderGL/RenderManagerGL.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define _DIRECTX    // DirectX�̎g�p�錾
//#define _OPENGL     // OpenGL �̎g�p�錾

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class InputManager;

class RenderManagerDX;
class RenderManagerGL;
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

    static RenderManagerDX* GetRenderManagerDX() { return pRenderManagerDX; }
    static RenderManagerGL* GetRenderManagerGL() { return pRenderManagerGL; }

    static GameObjectManager* GetGameObjectManager() { return pGameObjectManager; }
    static SceneManager*      GetSceneManager() { return pSceneManager; }

private:
    static InputManager* pInputManager;

    static RenderManagerDX* pRenderManagerDX;
    static RenderManagerGL* pRenderManagerGL;

    static GameObjectManager* pGameObjectManager;
    static SceneManager*      pSceneManager;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//