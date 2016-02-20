﻿/**************************************************************************************************

 @File   : [ Vector2.cpp ] 2Dベクトルと位置の表現
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "008_Utility/Vector2.h"

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
Vector2 Vector2::one  ( 1,  1);
Vector2 Vector2::zero ( 0,  0);

Vector2 Vector2::up   ( 0,  1);
Vector2 Vector2::down ( 0, -1);
Vector2 Vector2::right( 1,  0);
Vector2 Vector2::left (-1,  0);

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
