/**************************************************************************************************

 @File   : [ RenderManagerGL.h ] OpneGLの描画を管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDERMANAGERGL_H_
#define _RENDERMANAGERGL_H_

//***********************************************************************************************//
//                                                                                               //
//  @Link Library                                                                                //
//                                                                                               //
//***********************************************************************************************//
#pragma comment (lib, "OpenGL32.lib")    // OpenGL  関連
#pragma comment (lib, "GLu32.lib")       // OpenGL  関連

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----OpenGL-----//
#include <gl/GL.h>
#include <gl/GLU.h>

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderManagerDX.h"

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
class RenderGL;

class RenderManagerGL
{
public:
     RenderManagerGL() {}
    ~RenderManagerGL() {}

    static RenderManagerGL* Create();

    HRESULT Init();
    void    Uninit();
    void    Update();
    void    Draw();

    static void UpdateAll();
    static void DrawAll();
    static void UnLinkListAll();
    static void ReleaseAll();

    static void ZSort();
    static void CalculateZSortAll();

    //-----Operation List-----//
    static void LinkList(RenderGL* pRender, GameObject::LAYER Layer);
    static void UnLinkList(RenderGL* pRender);
    static void Release(RenderGL* pRender);

private:
    static HDC   hDC;       // デバイスコンテキスト
    static HGLRC hGLRC;     // カレントコンテキスト

    static std::list<RenderGL*> renderGLList[GameObject::LAYER_MAX];
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//