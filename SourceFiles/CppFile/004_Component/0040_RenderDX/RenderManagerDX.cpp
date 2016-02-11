/**************************************************************************************************

 @File   : [ RenderManagerDX.cpp ] DirectXの描画を管理するクラス
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
#include "004_Component/0040_RenderDX/RenderDX.h"
#include "004_Component/0040_RenderDX/RenderManagerDX.h"

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
LPDIRECT3D9       RenderManagerDX::pD3DObject = NULL;
LPDIRECT3DDEVICE9 RenderManagerDX::pD3DDevice = NULL;

D3DXCOLOR         RenderManagerDX::clearColor = D3DCOLOR_RGBA(55, 55, 170, 255);

std::list<RenderDX*> RenderManagerDX::renderDXList[GameObject::LAYER_MAX];

/*===============================================================================================* 
  @Summary: 生成処理
  @Details: None
 *===============================================================================================*/
RenderManagerDX *RenderManagerDX::Create()
{
    RenderManagerDX* pRenderManagerDX;
    pRenderManagerDX = new RenderManagerDX();
    if (FAILED(pRenderManagerDX->Init()))
    {
        MessageBox(NULL, "DirectXによる描画設定に失敗しました。", "エラー発生", MB_ICONERROR | MB_OK);

        return NULL;
    }

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        renderDXList[Layer].clear();
    }

    return pRenderManagerDX;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
HRESULT RenderManagerDX::Init()
{
    D3DDISPLAYMODE        d3ddm;
    D3DPRESENT_PARAMETERS d3dpp;

    // Direct3D オブジェクトの生成
    pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);
    if (pD3DObject == NULL)
    {
        MessageBox(NULL, "[ pD3DObject ] の生成に失敗しました。", "エラー発生", MB_ICONERROR | MB_OK);

        return E_FAIL;
    }

    // 現在のディスプレイモードの取得
    if (FAILED(pD3DObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
    {
        MessageBox(NULL, "[ pD3DObject ] ディスプレイモード取得に失敗しました。", "エラー発生", MB_ICONERROR | MB_OK);

        return E_FAIL;
    }

    // スクリーンサイズの設定確認
    //if (IDYES == MessageBox(Main::windowHandle, "ウィンドウモードで実行しますか？", "画面モード", MB_YESNO))
        Main::isWindow = true;

    // ディスプレイモードの設定
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.BackBufferWidth        = (UINT)Constant::SCREEN_WIDTH;     // ゲーム画面の幅
    d3dpp.BackBufferHeight       = (UINT)Constant::SCREEN_HEIGHT;    // ゲーム画面の高さ
    d3dpp.BackBufferCount        = 1;                                // バックバッファの数
    d3dpp.BackBufferFormat       = d3ddm.Format;                     // カラーモード
    d3dpp.Windowed               = Main::isWindow;                   // True: ウィンドウモード, False: フルスクリーン
    d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;            // フロントバッファとバックバッファの切り替え方法
    d3dpp.EnableAutoDepthStencil = TRUE;                             // デプスバッファ: オブジェクトの奥行き ステンシルバッファ: 描画領域の制限
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;                     // ステンシルバッファのフォーマット

    if (Main::isWindow)
    {
        // ウィンドウモード
        d3dpp.FullScreen_RefreshRateInHz = 0;
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    }
    else
    {
        // フルスクリーン
        d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
        d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    }

    // デバイスオブジェクトの作成
    if (FAILED(pD3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Main::windowHandle,
        D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice)))
    {
        if (FAILED(pD3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Main::windowHandle,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice)))
        {
            if (FAILED(pD3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, Main::windowHandle,
                D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice)))
            {
                MessageBox(NULL, "[ pD3DDevice ] の生成に失敗しました。", "エラー発生", MB_ICONERROR | MB_OK);

                return E_FAIL;
            }
        }
    }

    // レンダーステートの設定
    pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);                     // ライトを使用する
    pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);              // 裏カリング
    pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);             // α情報のブレンド設定 以下 2行含む
    pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    // テクスチャのステージステートの設定 テクスチャにα情報を適応させる
    pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP  , D3DTOP_MODULATE);    // テクスチャにも頂点のα情報を適応させる
    pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);      // テクスチャのアルファブレンディング処理
    pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);      // Current -ポリゴンの情報

    // サンプラーステートの設定
    pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);        // テクスチャのUV値の繰り返しを設定する
    pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
    pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);         // テクスチャの拡大縮小時の補間を行う
    pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

    // フォグの設定
    pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
    pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, clearColor);
    pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);
    float FogDensity = 0.001f;
    pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *((DWORD*)(&FogDensity)));

    // 背景クリア色の初期設定
    SetClearColor(clearColor);

    return S_OK;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::Uninit()
{
    // 既にGameObjectManager::ReleaseAll()でRenderコンポーネントは削除されているのでリンクを解除する
    UnLinkListAll();

    SafeRelease(pD3DDevice);
    SafeRelease(pD3DObject);
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::Update()
{
    //UpdateAll();    // GameObject->Update で個々のRenderのUpdateは呼ばれている
}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::Draw()
{
    // 画面のクリア
    pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), clearColor, 1.0f, 0);

    // 描画開始
    pD3DDevice->BeginScene();

        DrawAll();

    pD3DDevice->EndScene();

    // フロントバッファとバックバッファの入れ替え
    pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

/*===============================================================================================*
  @Summary: 登録された全てのRenderを更新する
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::UpdateAll()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = renderDXList[Layer].begin(); Iterator != renderDXList[Layer].end(); ++Iterator)
        {
            if ((*Iterator)->enabled)
            {
                (*Iterator)->Update();
            }
        }
    }
}

/*===============================================================================================*
  @Summary: 登録された全てのRenderの描画をする
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::DrawAll()
{
    // 描画の高速化
    CalculateZSortAll();
    ZSort();

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = renderDXList[Layer].begin(); Iterator != renderDXList[Layer].end(); ++Iterator)
        {
            if ((*Iterator)->enabled)
            {
                (*Iterator)->Draw();
            }
        }
    }
}

/*===============================================================================================*
  @Summary: 登録された全てのRenderをリストから解除する
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::UnLinkListAll()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        renderDXList[Layer].clear();
    }
}

/*===============================================================================================*
  @Summary: 登録された全てのRenderを削除する
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::ReleaseAll()
{
    RenderDX* pRender;

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = renderDXList[Layer].begin(); Iterator != renderDXList[Layer].end();)
        {
            pRender = (*Iterator);

            // リストから切り離す
            Iterator = renderDXList[Layer].erase(Iterator);

            // GameObjectの削除
            SafeDeleteUninit(pRender);
        }

        renderDXList[Layer].clear();
    }
}

/*===============================================================================================* 
  @Summary: 各レイヤーのRenderをカメラからの距離によってソートする
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::ZSort()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        // 不透明はZDepth値はカメラから近い順にソートし、半透明は遠い順にソート
        if (Layer < GameObject::LAYER::OBJECT3D_TRANSLUCENT_ONE)
        {
            renderDXList[Layer].sort(RenderDX::ZSortCompareLess);
        }
        else
        {
            renderDXList[Layer].sort(RenderDX::ZSortCompareGreater);
        }
    }
}

/*===============================================================================================* 
  @Summary: 各レイヤーのRenderのZDepthの値を計算する
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::CalculateZSortAll()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = renderDXList[Layer].begin(); Iterator != renderDXList[Layer].end(); ++Iterator)
        {
            
        }
    }
}

/*===============================================================================================*
  @Summary: Renderをリストに追加する
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::LinkList(RenderDX* pRender, GameObject::LAYER Layer)
{
    renderDXList[Layer].push_back(pRender);
}

/*===============================================================================================*
  @Summary: Renderをリストから解除する
  @Details: None
 *===============================================================================================*/
void RenderManagerDX::UnLinkList(RenderDX* pRender)
{
    GameObject::LAYER Layer = pRender->GetLayer();

    for (auto Iterator = renderDXList[Layer].begin(); Iterator != renderDXList[Layer].end(); ++Iterator)
    {
        if (*Iterator == pRender)
        {
            // リストから切り離す
            renderDXList[Layer].erase(Iterator);

            break;
        }
    }
}

/*===============================================================================================*
  @Summary: 対象のRenderを削除する (リストからも取り除く)
  @Details: 対象のRenderのUninit()が呼ばれる
 *===============================================================================================*/
void RenderManagerDX::Release(RenderDX* pRender)
{
    GameObject::LAYER Layer = pRender->GetLayer();

    for (auto Iterator = renderDXList[Layer].begin(); Iterator != renderDXList[Layer].end();)
    {
        if (*Iterator == pRender)
        {
            // リストから切り離す
            Iterator = renderDXList[Layer].erase(Iterator);

            // GameObjectの削除
            SafeDeleteUninit(pRender);

            return;
        }

        ++Iterator;
    }
}

/*===============================================================================================* 
  @Summary: フォントテキストを生成する
  @Details: None
 *===============================================================================================*/
LPD3DXFONT RenderManagerDX::CreateFontText(int CharacterSize, int CharacterWidth, int FontSize, bool IsItalic, std::string FontName)
{
    LPD3DXFONT FontDevice;

    if (FAILED(D3DXCreateFont(pD3DDevice, CharacterSize, CharacterWidth, FontSize, 0, IsItalic, SHIFTJIS_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, FontName.c_str(), &FontDevice)))
    {
        MessageBox(NULL, "[ FontDevice ] の生成に失敗しました。", "エラー発生", MB_ICONERROR | MB_OK);

        return NULL;
    }

    return FontDevice;
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//