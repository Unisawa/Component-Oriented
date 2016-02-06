/**************************************************************************************************

 @File   : [ RenderManagerGL.cpp ] OpneGL�̕`����Ǘ�����N���X
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
#include "004_Component/0041_RenderGL/RenderManagerGL.h"

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
HDC   RenderManagerGL::hDC   = NULL;
HGLRC RenderManagerGL::hGLRC = NULL;

/*===============================================================================================* 
  @Summary: ��������
  @Details: None
 *===============================================================================================*/
RenderManagerGL *RenderManagerGL::Create()
{
    RenderManagerGL* pRenderManagerGL;
    pRenderManagerGL = new RenderManagerGL();
    if (FAILED(pRenderManagerGL->Init()))
    {
        MessageBox(NULL, "OpenGL�ɂ��`��ݒ�Ɏ��s���܂����B", "�G���[����", MB_ICONERROR | MB_OK);

        return NULL;
    }

    return pRenderManagerGL;
}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
HRESULT RenderManagerGL::Init()
{
    // �f�o�C�X�R���e�L�X�g�̎擾 OpenGL ����������
    hDC = GetDC(Main::windowHandle);

    // OpenGL �s�N�Z���t�H�[�}�b�g�̍쐬
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Draw Flags
        PFD_TYPE_RGBA,                                                 // The kind of framebuffer. RGBA or palette.�`��
        24,                                                            // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,                                              // ��
        0,                                                             // ----
        0, 0, 0, 0, 0, 0,                                              // �� �A�L�������[�V���� �o�b�t�@
        32,                                                            // Number of bits for the depthbuffer
        1,                                                             // Number of bits for the stencilbuffer
        0,                                                             // Number of Aux buffers in the framebuffer. ���T�|�[�g
        PFD_MAIN_PLANE,
        0, 0, 0, 0
    };

    // �s�N�Z���t�H�[�}�b�g�̑I��
    int PixelFormat = ChoosePixelFormat(hDC, &pfd);

    // OpenGL�f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
    SetPixelFormat(hDC, PixelFormat, &pfd);

    // OpenGL �R���e�L�X�g���쐬
    hGLRC = wglCreateContext(hDC);

    // �쐬�����R���e�L�X�g���J�����g�ɐݒ�
    wglMakeCurrent(hDC, hGLRC);

    // �e�N�X�`���̗L����
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    return S_OK;
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::Uninit()
{
    // OpenGL �I������
    wglMakeCurrent(NULL, NULL);            // �J�����g�R���e�L�X�g�𖳌��ɂ���
    wglDeleteContext(hGLRC);               // �J�����g�R���e�L�X�g���폜
    ReleaseDC(Main::windowHandle, hDC);    // �f�o�C�X�R���e�L�X�g���

    hGLRC = NULL;
    hDC   = NULL;
}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::Update()
{

}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::Draw()
{
    // ��ʂ̃N���A
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̓���ւ�
    SwapBuffers(hDC);
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//