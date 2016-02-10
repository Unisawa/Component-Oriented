/**************************************************************************************************

 @File   : [ RenderManagerDX.h ] DirectX�̕`����Ǘ�����N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDERMANAGERDX_H_
#define _RENDERMANAGERDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Link Library                                                                                //
//                                                                                               //
//***********************************************************************************************//
#pragma comment (lib, "d3d9.lib")      // DirectX �{��
#pragma comment (lib, "d3dx9.lib")     // DirectX �g�����C�u����
#pragma comment (lib, "dxguid.lib")    // DirectX �R���|�[�l���g�g�p�ɕK�v

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----DirectX-----//
#define  D3D_DEBUG_INFO
#include "d3dx9.h"

//-----Object-----//
#include "004_Component/0042_GameObject/GameObject.h"

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
class RenderDX;

class RenderManagerDX
{
public:
     RenderManagerDX() {}
    ~RenderManagerDX() {}

    static RenderManagerDX* Create();

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
    static void LinkList(RenderDX* pRender, GameObject::LAYER Layer);
    static void UnLinkList(RenderDX* pRender);
    static void Release(RenderDX* pRender);

    //-----Create Font-----//
    static LPD3DXFONT CreateFontText(int CharacterSize, int CharacterWidth, int FontSize, bool IsItalic, std::string FontName);

    //-----Setter, Getter-----//
    static LPDIRECT3DDEVICE9 GetDevice() { return pD3DDevice; }

    static void      SetClearColor(D3DXCOLOR Color) { clearColor = Color; }
    static D3DXCOLOR GetClearColor() { return clearColor; }

private:
    static LPDIRECT3D9       pD3DObject;    // Direct3D�I�u�W�F�N�g
    static LPDIRECT3DDEVICE9 pD3DDevice;    // �f�o�C�X�I�u�W�F�N�g

    static D3DXCOLOR clearColor;            // �w�i�N���A�F

    static std::list<RenderDX*> renderDXList[GameObject::LAYER_MAX];
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//