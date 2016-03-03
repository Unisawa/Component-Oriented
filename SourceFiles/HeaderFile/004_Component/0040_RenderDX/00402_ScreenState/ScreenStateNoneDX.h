﻿/**************************************************************************************************

 @File   : [ ScreenStateNoneDX.h ] 描画する領域を制御するステートクラス (空のステート)
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _SCREENSTATENONEDX_H_
#define _SCREENSTATENONEDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"
#include "004_Component/0040_RenderDX/00402_ScreenState/ScreenStateDX.h"

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
class RenderDXManager;

class ScreenStateNoneDX : public ScreenStateDX
{
public:
             ScreenStateNoneDX() : ScreenStateDX() {}
    virtual ~ScreenStateNoneDX() {}

    virtual void BeginDraw(RenderDXManager* pRender) override {}
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//