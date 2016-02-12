/**************************************************************************************************

 @File   : [ Render2DGL.cpp ] OpenGLで2D四角形ポリゴンを描画するRenderクラス
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
#include "004_Component/0041_RenderGL/RenderGL.h"
#include "004_Component/0041_RenderGL/Render2DGL.h"
#include "004_Component/0042_GameObject/Transform.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
const std::string Render2DGL::className = "Render2DGL";

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
Render2DGL::Render2DGL(GameObject* pObject, GameObject::LAYER Layer) : RenderGL(pObject, className, Layer)
{

}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
Render2DGL::~Render2DGL()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void Render2DGL::Init()
{
    textureID = -1;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void Render2DGL::Uninit()
{

}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void Render2DGL::Update()
{

}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void Render2DGL::Draw()
{
    Transform* pTransform = this->gameObject->transform;

    float x = pTransform->GetPosition().x;
    float y = pTransform->GetPosition().y;

    float SizeX = pTransform->GetScale().x;
    float SizeY = pTransform->GetScale().y;

    // 描画設定
    SetBlending();
    SetCulling();

    // テクスチャセット
    //glBindTexture(GL_TEXTURE_2D,textureID);

    // 描画開始
    glBegin(GL_TRIANGLE_STRIP);

    // 左奥
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x - SizeX * 0.5f,
               y - SizeY * 0.5f,
                           0.0f);

    // 右奥
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + SizeX * 0.5f,
               y - SizeY * 0.5f,
                           0.0f);

    // 左手前
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x - SizeX * 0.5f,
               y + SizeY * 0.5f,
                           0.0f);

    // 右手前
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x + SizeX * 0.5f,
               y + SizeY * 0.5f,
                           0.0f);

    // 描画終了
    glEnd();
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