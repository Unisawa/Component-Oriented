/**************************************************************************************************

 @File   : [ Constant.cpp ] 
 @Auther : Nagasawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"

//-----GameObject-----//
#include "001_Constant/Constant.h"

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

//-----Application Setting-----//
const std::string Constant::WINDOW_NAME = "UniverseEngine";

//-----Screen Size-----//
const float Constant::SCREEN_WIDTH  = 1280.0f;    // HD (720p)
const float Constant::SCREEN_HEIGHT = 720.0f;

//const float Constant::SCREEN_WIDTH  = 1366.0f;    // PC��ʍő�
//const float Constant::SCREEN_HEIGHT = 768.0f;

const float Constant::SCREEN_WIDTH_HALF  = SCREEN_WIDTH  * 0.5f;
const float Constant::SCREEN_HEIGHT_HALF = SCREEN_HEIGHT * 0.5f;

//-----FilePath-----//
const std::string Constant::PATH_RESOURCE = "Resource/";

const std::string Constant::PATH_DATABASE = "Database/";
const std::string Constant::PATH_TEXTURE  = "Texture/";
const std::string Constant::PATH_SHADER   = "Shader/";

const std::string Constant::PATH_NETWORK  = "Network/";

const std::string Constant::PATH_MAP      = "Map/";

const std::string Constant::PATH_MODEL    = "Model/";
const std::string Constant::PATH_MOTION   = "Motion/";

const std::string Constant::PATH_AUDIO    = "Audio/";
const std::string Constant::PATH_VOICE    = "VOICE";
const std::string Constant::PATH_BGM      = "BGM/";
const std::string Constant::PATH_SE       = "SE/";

//-----Message-----//
const int Constant::MESSAGE_ERROR   = -1;
const int Constant::MESSAGE_SUCCESS = 1;

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//