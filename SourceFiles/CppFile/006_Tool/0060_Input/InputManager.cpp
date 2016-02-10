/**************************************************************************************************

 @File   : [ InputManager.cpp ] �S�Ă̓��͏����Ǘ�����N���X
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
#include "006_Tool/0060_Input/InputManager.h"
#include "006_Tool/0060_Input/Keyboard.h"

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
LPDIRECTINPUT8   InputManager::pDInput     = NULL;
//Mouse*           InputManager::pMouse      = NULL;
Keyboard*        InputManager::pKeyboard   = NULL;
//Joystick*        InputManager::pJoystick   = NULL;
//InputVirtualKey* InputManager::pVirtualKey = NULL;

int InputManager::RepeatRate = 40;

/*===============================================================================================* 
  @Summary: ��������
  @Details: None
 *===============================================================================================*/
InputManager *InputManager::Create()
{
    InputManager* pInputManager;
    pInputManager = new InputManager();
    pInputManager->Init();

    return pInputManager;
}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
void InputManager::Init()
{
    if (FAILED(DirectInput8Create(Main::instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDInput, NULL)))
    {
        MessageBox(NULL, "[ pDInput ] �̐����Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

        return;
    }

    //pMouse      = Mouse::Create();
    pKeyboard   = Keyboard::Create();
    //pJoystick   = Joystick::Create();
    //pVirtualKey = InputVirtualKey::Create();
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void InputManager::Uninit()
{
    //SafeDeleteUninit(pMouse);
    SafeDeleteUninit(pKeyboard);
    //SafeDeleteUninit(pJoystick);
    //SafeDeleteUninit(pVirtualKey);

    SafeRelease(pDInput);
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void InputManager::Update()
{
    //pMouse->Update();
    pKeyboard->Update();
    //pJoystick->Update();
    //pVirtualKey->Update();
}

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//