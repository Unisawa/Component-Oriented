/**************************************************************************************************

 @File   : [ Transform.h ] オブジェクトの位置、回転、スケールを扱うクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "004_Component/Component.h"

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
class Transform : public Component
{
public:
             Transform();
    virtual ~Transform();

    void SetParent(Transform& value);

private:
    Transform*  parent;        // Transform の親

    D3DXVECTOR3 position;      // ワールド空間の Transform の位置
    D3DXVECTOR3 rotation;      // ワールド空間の Transform の回転
    D3DXVECTOR3 lossyScale;    // オブジェクトのグローバルスケール
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//