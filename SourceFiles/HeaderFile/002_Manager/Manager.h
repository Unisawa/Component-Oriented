/**************************************************************************************************

 @File   : [ Manager.h ] ゲーム全般に必要な各種Managerを管理するクラス
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
#define _DIRECTX    // DirectXの使用宣言
//#define _OPENGL     // OpenGL の使用宣言

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class RenderManagerDX;
class RenderManagerGL;
class GameObjectManager;

class Manager
{
public:
     Manager() {}
    ~Manager() {}

    HRESULT Init();
    void    Uninit();
    void    Update();
    void    Draw();

    static RenderManagerDX* GetRenderManagerDX() { return pRenderManagerDX; }
    static RenderManagerGL* GetRenderManagerGL() { return pRenderManagerGL; }

    static GameObjectManager* GetGameObjectManager() { return pGameObjectManager; }

private:
    static RenderManagerDX* pRenderManagerDX;
    static RenderManagerGL* pRenderManagerGL;

    static GameObjectManager* pGameObjectManager;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//