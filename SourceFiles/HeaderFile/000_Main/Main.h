/**************************************************************************************************

 @File   : [ Main.h ] 
 @Auther : Nagasawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

//***********************************************************************************************//
//                                                                                               //
//  @Link Library                                                                                //
//                                                                                               //
//***********************************************************************************************//
#pragma comment (lib, "d3d9.lib")      // DirectX �{��
#pragma comment (lib, "d3dx9.lib")     // DirectX �g�����C�u����
#pragma comment (lib, "dxguid.lib")    // DirectX �R���|�[�l���g�g�p�ɕK�v
#pragma comment (lib, "winmm.lib")     // Windows �V�X�e���֘A

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Find Memory Leak-----//
#define  _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//-----DirectX-----//
#define  D3D_DEBUG_INFO
#include "d3dx9.h"

//-----Default Include-----//
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <time.h>

//-----STL-----//
#include <String>
#include <list>

//-----Manager-----//


//-----GameObject-----//


//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//-----Memory Leak Report-----//
#ifdef _DEBUG
    #ifndef DBG_NEW
        #define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
        #define new DBG_NEW
    #endif
#endif

//-----Safe Memory Delete-----//
template <typename T>
inline void SafeDelete(T*& pPointer)    // NULL�łȂ��Ȃ�|�C���^�폜
{
    if (pPointer != NULL)
    {
        delete (pPointer);
        (pPointer) = NULL;
    }
}

template <typename T>
inline void SafeDeleteArray(T*& pPointer)    // NULL�łȂ��Ȃ�z��|�C���^�폜
{
    if (pPointer != NULL)
    {
        delete[] (pPointer);
        (pPointer) = NULL;
    }
}

template <typename T>
inline void SafeUninit(T*& pPointer)    // NULL�łȂ��Ȃ炻�̃|�C���^��Uninit()�����s
{
    if (pPointer != NULL)
    {
        (pPointer)->Uninit();
        (pPointer) = NULL;
    }
}

template <typename T>
inline void SafeDeleteUninit(T*& pPointer)    // NULL�łȂ��Ȃ炻�̃|�C���^��Uninit()�����s��A�폜
{
    if (pPointer != NULL)
    {
        (pPointer)->Uninit();
        delete (pPointer);
        (pPointer) = NULL;
    }
}

//-----Safe Memory Release-----//
template <typename T>
inline void SafeRelease(T*& pPointer)    // NULL�łȂ��Ȃ炻�̃|�C���^��Release()�����s
{
    if (pPointer != NULL)
    {
        (pPointer)->Release();
        (pPointer) = NULL;
    }
}

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class Manager;

class Main
{
public:
     Main() {};
    ~Main() {};

    void Init();
    void Uninit();
    void Update();
    void Draw();
    MSG  MessageLoop();

    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // WinAPI�̃E�B���h�E���
    static HWND      WindowHandle;
    static HINSTANCE Instance;

    static unsigned int FrameRate;

private:
    Manager* pManager;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//