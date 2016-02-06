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

private:
    static HDC   hDC;       // デバイスコンテキスト
    static HGLRC hGLRC;     // カレントコンテキスト
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//