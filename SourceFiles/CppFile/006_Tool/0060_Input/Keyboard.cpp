/**************************************************************************************************

 @File   : [ Keyboard.cpp ] �L�[�{�[�h����̓��͂��Ǘ�����N���X
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

/*===============================================================================================* 
  @Summary: ��������
  @Details: None
 *===============================================================================================*/
Keyboard *Keyboard::Create()
{
    Keyboard* pKeyboard;
    pKeyboard = new Keyboard();
    pKeyboard->Init();

    return pKeyboard;
}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
void Keyboard::Init()
{
    HRESULT Result;
    LPDIRECTINPUT8 pInput = InputManager::GetInputDevice();

    // �z��̏�����
    for (int KeyID = 0; KeyID < MAX_KEY_NUM; KeyID++)
    {
        keyStatePress[KeyID]       = 0x00;
        keyStateTrigger[KeyID]     = 0x00;
        keyStateRelease[KeyID]     = 0x00;
        keyStateRepeat[KeyID]      = 0x00;
        keyStateRepeatCount[KeyID] = 1;
    }

    // �L�[�{�[�h�f�o�C�X�I�u�W�F�N�g�̍쐬
    Result = pInput->CreateDevice(GUID_SysKeyboard, &pDeviceKeyboard, NULL);
    if (FAILED(Result))
    {
        MessageBox(NULL, "[ pDeviceKeyboard ] �̍쐬�Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

        return;
    }

    // �L�[�{�[�h�f�o�C�X�̃f�[�^�`����ݒ�
    Result = pDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(Result))
    {
        MessageBox(NULL, "[ pDeviceKeyboard ] �̃f�[�^�`���̐ݒ�Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

        return;
    }

    // �f�o�C�X�̃C���X�^���X�ɑ΂��鋦�����x���̐ݒ�
    Result = pDeviceKeyboard->SetCooperativeLevel(Main::windowHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
    if (FAILED(Result))
    {
        MessageBox(NULL, "[ pDeviceKeyboard ] �̋������[�h�̐ݒ�Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

        return;
    }

    // �L�[�{�[�h�ւ̃A�N�Z�X�����l��
    pDeviceKeyboard->Acquire();
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void Keyboard::Uninit()
{
    if (pDeviceKeyboard != NULL)
    {
        pDeviceKeyboard->Unacquire();
    }

    SafeRelease(pDeviceKeyboard);
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void Keyboard::Update()
{
    BYTE keyState[MAX_KEY_NUM];    // �L�[���̒���
    int  RepeatRate = InputManager::RepeatRate;

    // ���݂̃L�[�{�[�h���͏�Ԃ��擾���āA�e����͏����X�V����
    if (SUCCEEDED(pDeviceKeyboard->GetDeviceState(sizeof(keyState), keyState)))
    {
        for (int KeyID = 0; KeyID < MAX_KEY_NUM; KeyID++)
        {
            // Trigger ���͏��
            keyStateTrigger[KeyID] = (keyStatePress[KeyID] ^ keyState[KeyID]) & (keyState[KeyID]);

            // Release ���͏��
            keyStateRelease[KeyID] = (keyStatePress[KeyID] ^ keyState[KeyID]) & (keyStatePress[KeyID]);

            // Repeat ���͏��
            if (keyState[KeyID] == 0x80)
            {
                if (keyStateRepeatCount[KeyID] == 1)    // ����̓��͂�^�ɂ���
                {
                    keyStateRepeat[KeyID] = 0x80;
                    keyStateRepeatCount[KeyID]++;

                }
                else if (keyStateRepeatCount[KeyID] <= RepeatRate)    // ���̃t���[���Ԃ͖����ɂ���
                {
                    keyStateRepeat[KeyID] = 0x00;
                    keyStateRepeatCount[KeyID]++;

                }
                else if (keyStateRepeatCount[KeyID] > RepeatRate)     // �Ȍ�S�Đ^�ɂ���
                {
                    keyStateRepeat[KeyID] = keyState[KeyID];
                }

            }
            else    // Repeat ��Ԃ̉���
            {
                keyStateRepeatCount[KeyID] = 1;
                keyStateRepeat[KeyID] = keyState[KeyID];
            }

            // �L�[�{�[�h���̍X�V (Press ���͏��)
            keyStatePress[KeyID] = keyState[KeyID];
        }
    }
    else
    {
        // �L�[�{�[�h�ւ̃A�N�Z�X�����Ċl��
        pDeviceKeyboard->Acquire();
    }
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//