/**************************************************************************************************

 @File   : [ Main.cpp ] 
 @Auther : Nagasawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"
#include "001_Constant/Constant.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define CLASS_NAME "CoreClass"

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//
HWND         Main::WindowHandle = NULL;
HINSTANCE    Main::Instance = NULL;
unsigned int Main::FrameRate = 0;

/*===============================================================================================* 
  @Summary: �v���O�����N�����ɍŏ��ɌĂ΂�AWindow�𐶐��A�Ǘ��A�j������
  @Details: None
 *===============================================================================================*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    RECT  Rect;       // ��ʃT�C�Y
    MSG   Message;    // ���b�Z�[�W���
    Main* pMain;      // �Q�[���pFPS�Ǘ��Ȃ�

    // ���������[�N�̌��o�J�n
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

    // ����\�̐ݒ�
    timeBeginPeriod(1);

    // �E�C���h�E�N���X�̐ݒ�
    WNDCLASSEX wcex =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, Main::WindowProcedure, 0, 0, hInstance, NULL,
        LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), NULL, CLASS_NAME, NULL
    };

    // �N���C�A���g�̈�T�C�Y�̕␳
    SetRect(&Rect, 0, 0, (int)Constant::SCREEN_WIDTH, (int)Constant::SCREEN_HEIGHT);
    AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, FALSE);

    // �E�C���h�E�N���X�̓o�^
    RegisterClassEx(&wcex);

    // �E�B���h�E�����ʒu�𒆉��ɒ�������
    RECT rcRect;
    Main::WindowHandle = GetDesktopWindow();
    GetWindowRect(Main::WindowHandle, &rcRect);

    // �E�B���h�E�̐���
#ifdef _DEBUG
    Main::WindowHandle = CreateWindowEx(0, CLASS_NAME, Constant::WINDOW_NAME.c_str(), WS_OVERLAPPEDWINDOW, (rcRect.right - (int)Constant::SCREEN_WIDTH) / 2 , (Rect.bottom - (int)Constant::SCREEN_HEIGHT) / 2,
                                        (Rect.right - Rect.left), (Rect.bottom - Rect.top), NULL, NULL, hInstance, NULL);
#else if _RELEASE
    Main::WindowHandle = CreateWindowEx(0, CLASS_NAME, Constant::WINDOW_NAME.c_str(), WS_OVERLAPPEDWINDOW, (rcRect.right - (int)Constant::SCREEN_WIDTH) / 2 , (Rect.bottom - (int)Constant::SCREEN_HEIGHT) / 2,
                                        (Rect.right - Rect.left), (Rect.bottom - Rect.top), NULL, NULL, hInstance, NULL);

    // �E�B���h�E�T�C�Y�̌Œ艻
    LONG Style = GetWindowLong(Main::WindowHandle, GWL_STYLE);
    Style &= ~WS_THICKFRAME;
    Style  = SetWindowLong(Main::WindowHandle, GWL_STYLE, Style);
#endif

    // �E�B���h�E�̕\��
    ShowWindow(Main::WindowHandle, nCmdShow);
    UpdateWindow(Main::WindowHandle);

    // ����������
    Main::Instance = hInstance;
    pMain = new Main();
    pMain->Init();

    // Message Loop
    Message = pMain->MessageLoop();

    // �E�B���h�E�N���X�̓o�^����
    UnregisterClass(CLASS_NAME, wcex.hInstance);

    //-----�I������-----//
    SafeDeleteUninit(pMain);

    // ����\�ݒ�̉���
    timeEndPeriod(1);

    return (int)Message.wParam;
}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
void Main::Init()
{
    Main::FrameRate = 60;

    //pManager = new Manager();
    //pManager->Init();
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void Main::Uninit()
{
    //SafeDeleteUninit(pManager);
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void Main::Update()
{
    //pManager->Update();

    // FPS�\���p�J�E���^�̍X�V
    //DebugManager::AddFrameCount();
}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void Main::Draw()
{
    //pManager->Draw();
}

/*===============================================================================================* 
  @Summary: FPS�𒲐����čX�V�A�`��A�v���O�����I���̔�����Ǘ�����
  @Details: None
 *===============================================================================================*/
MSG Main::MessageLoop()
{
    MSG   Message;           // ���b�Z�[�W���
    DWORD dwExecLastTime;    // �ŏI���s����
    DWORD dwCurrentTime;     // ���ݎ���

    // FPS�̏����ݒ�
    dwExecLastTime = timeGetTime();
    dwCurrentTime = 0;

    while (true)
    {
        if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE) != 0)
        {
            if (Message.message == WM_QUIT)
            {
                break;    // �v���O�����I��
            }
            else
            {
                // ���b�Z�[�W�̉�͂Ƒ��o
                TranslateMessage(&Message);
                DispatchMessage(&Message);
            }
        }
        else
        {
            // ���ݎ����擾
            dwCurrentTime = timeGetTime();

            // FPS �v�Z
            //DebugManager::CheckFPS(dwCurrentTime);

            if ((dwCurrentTime - dwExecLastTime) >= (1000 / Main::FrameRate))
            {
                dwExecLastTime = dwCurrentTime;

                //-----�X�V����-----//
                Update();

                //-----�`�揈��-----//
                Draw();
            }
        }
    }

    return Message;
}

/*===============================================================================================* 
  @Summary: Window����̃R�[���o�b�N�֐�
  @Details: None
 *===============================================================================================*/
LRESULT CALLBACK Main::WindowProcedure(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    switch(uMessage)
    {
        // �E�B���h�E�������̏���
        case WM_CREATE:
            break;

        // ���b�Z�[�W���[�v�̏I��
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        // �E�B���h�E�I���{�^���������̊m�F
        case WM_CLOSE:

            // �t���X�N���[�����Ȃ�m�F�����ɏI������
            if( IDYES == MessageBox(hWnd, "�I�����܂����H" , "�I��", MB_YESNO | MB_ICONQUESTION) )
            {
                DestroyWindow(hWnd);
                break;
            }

            return 0;
            break;
        
        // �}�E�X���쎞
        case WM_MOUSEMOVE:
            break;

        // �e��L�[���͎�
        case WM_KEYDOWN:
            switch(wParam)
            {
                // �I������
                case VK_ESCAPE:

                if( IDYES == MessageBox(hWnd, "�I�����܂����H" , "�I��", MB_YESNO | MB_ICONQUESTION) )
                {
                    DestroyWindow(hWnd);
                }
                break;
            }
            break;

        // ���j���[�o�[����̐ݒ菈��
        case WM_COMMAND:
            break;

        default:
            break;
    }

    return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//