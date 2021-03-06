﻿/**************************************************************************************************

 @File   : [ DebugManagerDX.h ] DirectXのデバッグモードを制御するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _DEBUGMANAGERDX_H_
#define _DEBUGMANAGERDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class GameObject;
class DebugStateDX;

class DebugManagerDX
{
public:
     DebugManagerDX();
    ~DebugManagerDX();

    static DebugManagerDX* Create();

    void Init();
    void Uninit();
    void Update();
    void Draw();

    static void CheckFPS(DWORD NowTime);
    static void AddframeCount();

    static void Print(std::string String, ...);

    void ChangeState(DebugStateDX* pState);

    //-----Setter, Getter-----//
    void SetDebugMode(bool value) { isDebugMode = value; }
    bool IsDebugMode() const { return isDebugMode; }

    LPD3DXFONT GetDebugFont() const { return pDebugFont; }

    RECT GetRectBottom()   const { return freeRect; }
    RECT GetRectLeftUp()   const { return hierarchyRect; }
    RECT GetRectLeftDown() const { return inspectorRect; }

    std::string GetFreeMessege() const { return messegeFree; }

private:
    void SetFreeMessege();
    void SelectDebugState();
    void ChangeDebugMode();

    static DWORD currentTime;
    static DWORD lastTimeFPS;
    static DWORD frameCount;
    static int   countFPS;

    static std::string messegeFree;

    LPD3DXFONT pDebugFont;

    RECT       freeRect;
    RECT       hierarchyRect;
    RECT       inspectorRect;

    DebugStateDX* pDebugStateDX;

    bool isDebugMode;
    bool isWireFrame;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
