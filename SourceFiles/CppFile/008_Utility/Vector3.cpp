﻿/**************************************************************************************************

 @File   : [ Vector3.cpp ] 3Dベクトルと位置の表現
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"

//-----Object-----//
#include "008_Utility/Vector3.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//
Vector3 Vector3::one (1.0f,  1.0f,  1.0f);
Vector3 Vector3::zero(0.0f,  0.0f,  0.0f);

Vector3 Vector3::up     ( 0.0f,  1.0f,  0.0f);
Vector3 Vector3::down   ( 0.0f, -1.0f,  0.0f);
Vector3 Vector3::right  ( 1.0f,  0.0f,  0.0f);
Vector3 Vector3::left   (-1.0f,  0.0f,  0.0f);
Vector3 Vector3::forward( 0.0f,  0.0f,  1.0f);
Vector3 Vector3::back   ( 0.0f,  0.0f, -1.0f);

/*===============================================================================================* 
  @Summary: ベクトルの正規化を行う
  @Details: None
 *===============================================================================================*/
void Vector3::Normalize()
{
    float Magnitude = sqrtf((x * x) + (y * y) + (z * z));

    if (Magnitude != 0)
    {
        Magnitude = 1 / Magnitude;

        x = x * Magnitude;
        y = y * Magnitude;
        z = z * Magnitude;
    }
    else
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
}

/*===============================================================================================* 
  @Summary: D3DXVECTOR3型にVector3を変換する
  @Details: None
 *===============================================================================================*/
#ifdef USE_DIRECTX
D3DXVECTOR3 Vector3::GetDX()
{
    D3DXVECTOR3 Pos(x, y, z);

    return Pos;
}
#endif

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
