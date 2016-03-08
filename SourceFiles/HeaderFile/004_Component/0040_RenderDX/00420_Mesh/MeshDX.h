﻿/**************************************************************************************************

 @File   : [ MeshDX.h ] スクリプトからメッシュを作成または変更できるようにするクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _MESHDX_H_
#define _MESHDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//-----Object-----//
#include "003_Object/Object.h"

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
class MeshDX : public Object
{
public:
             MeshDX();
    virtual ~MeshDX();

    void CreateVertexBuffer();
    void CreateIndexBuffer();

    void ResetBufer(int DivX, int DivY);

    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;    // 頂点バッファ
    LPDIRECT3DINDEXBUFFER9  pIndexBuffer;     // インテックスバッファ

    int vertexNum;         // 頂点数
    int vertexIndexNum;    // インデックス数

    int divisionX;         // ポリゴン分割数
    int divisionY;         // ポリゴン分割数
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
