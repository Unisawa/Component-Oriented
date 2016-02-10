/**************************************************************************************************

 @File   : [ Main.cpp ] �y UniverseEngine �z�̃V�X�e����S�ĊǗ����郁�C���N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"
#include "001_Constant/Constant.h"
#include "002_Manager/Manager.h"

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
HWND         Main::windowHandle = NULL;
HINSTANCE    Main::instance     = NULL;
bool         Main::isWindow     = false;

unsigned int Main::frameRate    = 0;

/*===============================================================================================* 
  @Summary: �v���O�����N�����ɍŏ��ɌĂ΂�AWindow�𐶐��A�Ǘ��A�j������
  @Details: None
 *===============================================================================================*/
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
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
        sizeof(WNDCLASSEX), CS_CLASSDC, Main::WindowProcedure, 0, 0, hinstance, NULL,
        LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), NULL, CLASS_NAME, NULL
    };

    // �N���C�A���g�̈�T�C�Y�̕␳
    SetRect(&Rect, 0, 0, (int)Constant::SCREEN_WIDTH, (int)Constant::SCREEN_HEIGHT);
    AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, FALSE);

    // �E�C���h�E�N���X�̓o�^
    RegisterClassEx(&wcex);

    // �E�B���h�E�����ʒu�𒆉��ɒ�������
    RECT rcRect;
    Main::windowHandle = GetDesktopWindow();
    GetWindowRect(Main::windowHandle, &rcRect);

    // �E�B���h�E�̐���
#ifdef _DEBUG
    Main::windowHandle = CreateWindowEx(0, CLASS_NAME, Constant::WINDOW_NAME.c_str(), WS_OVERLAPPEDWINDOW,
                                        (rcRect.right - (int)Constant::SCREEN_WIDTH) / 2 , (Rect.bottom - (int)Constant::SCREEN_HEIGHT) / 2,
                                        (Rect.right - Rect.left), (Rect.bottom - Rect.top), NULL, NULL, hinstance, NULL);
#else if _RELEASE
    Main::windowHandle = CreateWindowEx(0, CLASS_NAME, Constant::WINDOW_NAME.c_str(), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                                        (rcRect.right - (int)Constant::SCREEN_WIDTH) / 2 , (Rect.bottom - (int)Constant::SCREEN_HEIGHT) / 2,
                                        (Rect.right - Rect.left), (Rect.bottom - Rect.top), NULL, NULL, hinstance, NULL);
#endif

    // �E�B���h�E�̕\��
    ShowWindow(Main::windowHandle, nCmdShow);
    UpdateWindow(Main::windowHandle);

    // ����������
    Main::instance = hinstance;
    pMain = new Main();
    if (pMain->Init() == E_FAIL)    // ���������s �v���O�����I��
    {
        //-----�I������-----//
        SafeDeleteUninit(pMain);

        // ����\�ݒ�̉���
        timeEndPeriod(1);

        return NULL;
    }

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
HRESULT Main::Init()
{
    Main::frameRate = 60;

    Debug::Log("Start Manager Init");

    pManager = new Manager();
    if (pManager->Init() == E_FAIL) return E_FAIL;

    return S_OK;
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void Main::Uninit()
{
    Debug::Log("Start Manager Uninit");

    SafeDeleteUninit(pManager);
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void Main::Update()
{
    pManager->Update();

    // FPS�\���p�J�E���^�̍X�V
    //DebugManager::AddFrameCount();
}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void Main::Draw()
{
    pManager->Draw();
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

            if ((dwCurrentTime - dwExecLastTime) >= (1000 / Main::frameRate))
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