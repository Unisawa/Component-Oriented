/**************************************************************************************************

 @File   : [ MonoBehaviour.cpp ] 全てのスクリプトから派生するベースクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0043_Behaviour/MonoBehaviour.h"

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

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
MonoBehaviour::MonoBehaviour(GameObject* pObject, std::string ComponentName) : Behaviour(pObject, ComponentName)
{

}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
MonoBehaviour::~MonoBehaviour()
{

}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//