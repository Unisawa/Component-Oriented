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

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define _DIRECTX    // DirectX�̎g�p�錾
//#define _OPENGL     // OpenGL �̎g�p�錾

#ifdef _DIRECTX
#include "004_Component/0040_RenderDX/RenderManagerDX.h"
#endif

#ifdef _OPENGL
#include "004_Component/0041_RenderGL/RenderManagerGL.h"
#endif

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class RenderManagerDX;
class RenderManagerGL;

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

private:
    static RenderManagerDX* pRenderManagerDX;
    static RenderManagerGL* pRenderManagerGL;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//