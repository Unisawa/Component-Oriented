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
#include "001_Constant/Constant.h"

//-----Object-----//
#include "004_Component/0041_RenderGL/RenderGL.h"
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

std::list<RenderGL*> RenderManagerGL::renderGLList[GameObject::LAYER_MAX];

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

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        renderGLList[Layer].clear();
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
    // ����GameObjectManager::ReleaseAll()��Render�R���|�[�l���g�͍폜����Ă���̂Ń����N����������
    UnLinkListAll();

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
    UpdateAll();
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

    // �`��
    DrawAll();

    // �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̓���ւ�
    SwapBuffers(hDC);
}

/*===============================================================================================*
  @Summary: �o�^���ꂽ�S�Ă�Render���X�V����
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::UpdateAll()
{
    for (int Cnt = 0; Cnt < GameObject::LAYER_MAX; ++Cnt)
    {
        for (auto Iterator = renderGLList[Cnt].begin(); Iterator != renderGLList[Cnt].end(); ++Iterator)
        {
            if ((*Iterator)->enabled)
            {
                (*Iterator)->Update();
            }
        }
    }
}

/*===============================================================================================*
  @Summary: �o�^���ꂽ�S�Ă�Render�̕`�������
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::DrawAll()
{
    // �`��̍�����
    CalculateZSortAll();
    ZSort();

    for (int Cnt = 0; Cnt < GameObject::LAYER_MAX; ++Cnt)
    {
        // 2D�J�����ݒ�
        if (Cnt == GameObject::LAYER::OBJECT2D_OPACITY_ONE)
        {
            // 2D�`��ݒ�
            glDisable(GL_LIGHTING);
            glDisable(GL_DEPTH_TEST);

            // ���ˉe�s��
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0f, Constant::SCREEN_WIDTH, Constant::SCREEN_HEIGHT, 0.0f, 0.0f, 10000.0f);
            glPushMatrix();

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }

        for (auto Iterator = renderGLList[Cnt].begin(); Iterator != renderGLList[Cnt].end(); ++Iterator)
        {
            if ((*Iterator)->enabled)
            {
                (*Iterator)->Draw();
            }
        }
    }

    // 2D�J�����ݒ����
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // 2D�`��ݒ胊�Z�b�g
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

/*===============================================================================================*
  @Summary: �o�^���ꂽ�S�Ă�Render�����X�g�����������
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::UnLinkListAll()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        renderGLList[Layer].clear();
    }
}

/*===============================================================================================*
  @Summary: �o�^���ꂽ�S�Ă�Render���폜����
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::ReleaseAll()
{
    RenderGL* pRender;

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = renderGLList[Layer].begin(); Iterator != renderGLList[Layer].end();)
        {
            pRender = (*Iterator);

            // ���X�g����؂藣��
            Iterator = renderGLList[Layer].erase(Iterator);

            // GameObject�̍폜
            SafeDeleteUninit(pRender);
        }

        renderGLList[Layer].clear();
    }
}

/*===============================================================================================* 
  @Summary: �e���C���[��Render���J��������̋����ɂ���ă\�[�g����
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::ZSort()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        // �s������ZDepth�l�̓J��������߂����Ƀ\�[�g���A�������͉������Ƀ\�[�g
        if (Layer < GameObject::LAYER::OBJECT3D_TRANSLUCENT_ONE)
        {
            renderGLList[Layer].sort(RenderGL::ZSortCompareLess);
        }
        else
        {
            renderGLList[Layer].sort(RenderGL::ZSortCompareGreater);
        }
    }
}

/*===============================================================================================* 
  @Summary: �e���C���[��Render��ZDepth�̒l���v�Z����
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::CalculateZSortAll()
{
    for (int Cnt = 0; Cnt < GameObject::LAYER_MAX; ++Cnt)
    {
        for (auto Iterator = renderGLList[Cnt].begin(); Iterator != renderGLList[Cnt].end(); ++Iterator)
        {
            
        }
    }
}

/*===============================================================================================*
  @Summary: Render�����X�g�ɒǉ�����
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::LinkList(RenderGL* pRender, GameObject::LAYER Layer)
{
    renderGLList[Layer].push_back(pRender);
}

/*===============================================================================================*
  @Summary: Render�����X�g�����������
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::UnLinkList(RenderGL* pRender)
{
    GameObject::LAYER Layer = pRender->GetLayer();

    for (auto Iterator = renderGLList[Layer].begin(); Iterator != renderGLList[Layer].end(); ++Iterator)
    {
        if (*Iterator == pRender)
        {
            // ���X�g����؂藣��
            renderGLList[Layer].erase(Iterator);

            break;
        }
    }
}

/*===============================================================================================*
  @Summary: �Ώۂ�Render���폜���� (���X�g�������菜��)
  @Details: �Ώۂ�Render��Uninit()���Ă΂��
 *===============================================================================================*/
void RenderManagerGL::Release(RenderGL* pRender)
{
    GameObject::LAYER Layer = pRender->GetLayer();

    for (auto Iterator = renderGLList[Layer].begin(); Iterator != renderGLList[Layer].end();)
    {
        if (*Iterator == pRender)
        {
            // ���X�g����؂藣��
            Iterator = renderGLList[Layer].erase(Iterator);

            // GameObject�̍폜
            SafeDeleteUninit(pRender);

            return;
        }

        ++Iterator;
    }
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//