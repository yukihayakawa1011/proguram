//============================
//
//メイン関数(main.cpp)
//Author:早川 友貴
//
//============================ 

#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include"fade.h"
#include"sound.h"
#include "key.h"
#include "gameover.h"
#include "enemy.h"
#include "ranking.h"
#include "tutorial.h"

//マクロ定義
#define CLASS_NAME    "WindowClass"        //ウインドウクラスの名前
#define WINDOW_NAME   "ESCAPE" //ウインドウの名前（キャプションに表示）

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void); 
void DrawEnemyCnt(void);

//グローバル変数宣言
LPDIRECT3D9				g_pD3D = NULL;				//Direct3Dのオブジェクトへのポインタ
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		//Direct3Dデバイスのポインタ
LPD3DXFONT				g_pFont = NULL;             //フォントへのポインタ
int						g_nCountFPS = 0;            //FPSカウンタ
int						g_nCntKey = 0;              //鍵カウンタ
bool					g_bDispDebug = false;		//デバッグ表示のON/OFF
MODE					g_mode = MODE_TITLE;			//現在のモード

//============================
//メイン関数
//============================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//ウインドウクラスの構造体を宣言
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),           //WNDCLASSEXのメモリサイズ
		CS_CLASSDC,                   //ウインドウのスタイル
		WindowProc,                  //ウインドウプロシージャ
		0,                           //０にする（通常は通用しない)
		0,							//0にする（通常は通用しない）
		hInstance,					//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),  //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),  //クライアント領域の背景色
		NULL,						//メニューバー
		CLASS_NAME,                 //ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),
	};

	HWND hWnd;				//ウインドウハンドル(識別子)

	MSG msg;				//メッセージを格納する変数

	RECT rect = { 0, 0, SCREEN_WINDTH, SCREEN_HEIGHT };

	RegisterClassEx(&wcex);			//ウインドウクラスの登録

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドを作成
	hWnd = CreateWindowEx(0,	//拡張ウインドウスタイル
		CLASS_NAME,			//ウインドウクラスの名前
		WINDOW_NAME,			//ウインドウの名前
		WS_OVERLAPPEDWINDOW,  //ウインドウスタイル
		CW_USEDEFAULT,      //ウインドウの左上X座標
		CW_USEDEFAULT,      //ウインドウの左上Y座標
		(rect.right - rect.left),     //ウインドウの幅
		(rect.bottom - rect.top),     //ウインドウの高さ
		NULL,                 //親ウインドウのハンドル
		NULL,					//メニューハンドルまたは子ウインドウID
		hInstance,			//インスタンスハンドル
		NULL);				    //ウインドウ作成データ

	DWORD dwCurrentTime;		//現在時刻
	DWORD dwExecLastTime;       //最後に処理した時刻
	DWORD dwFrameCount;			//フレームカウント
	DWORD dwFPSLASTTIME;        //最後にFPSを計測した時刻

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合

		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;  //初期化する
	dwExecLastTime = timeGetTime();		//現在時刻を取得(保存)
	dwFrameCount = 0;  //初期化する
	dwFPSLASTTIME = timeGetTime();      //FPS現在数値を取得(保存)

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);       //ウインドウの表示状態を設定
	UpdateWindow(hWnd);				  //クライアント領域を更新

//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける

				break;

			}

			else
			{
				//メッセージの設定
				TranslateMessage(&msg); //仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);  //ウインドウプロージャへメッセージを送出
			}
		}

		else
		{//DirectXの処理

			dwCurrentTime = timeGetTime();   //現在時刻を取得

			if ((dwCurrentTime - dwFPSLASTTIME) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLASTTIME);

				dwFPSLASTTIME = dwCurrentTime;   //FPSを測定した時刻を保存

				dwFrameCount = 0;   //フレームカウントをクリア

			}

			if (dwCurrentTime - dwExecLastTime >= (1000 / 60))
			{//60分の1秒経過

			dwExecLastTime = dwCurrentTime;  //処理開始の時刻[現在時刻]を保存

			 //更新処理						 
			Update();  

			//描画処理
			Draw();

			dwFrameCount++;         //フレームカウントを加算

			}

		}

	}

	//終了処理
	Uninit();

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;

}

//======================
//ウインドウプロージャ
//======================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;  //帰り

	switch (uMsg)
	{
	case WM_DESTROY:   //ウインドウ破棄のメッセージ

					   //WM_QUITにメッセージを送る
		PostQuitMessage(0);

		break;

	case WM_KEYDOWN:  //キー押したのメッセージ

		switch (wParam)
		{
		case VK_ESCAPE:  //[ESC]キーが押された

			nID = MessageBox(hWnd, "終了しますか", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{

				//ウインドウを破棄する
				DestroyWindow(hWnd);

			}

			else
			{
				return 0;   //0を返さないと終了してしまう
			}

			break;
		}
		break;

	case WM_CLOSE:  //閉じるボタン押したのメッセージ

		nID = MessageBox(hWnd, "終了しますか", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{

			//ウインドウを破棄する
			DestroyWindow(hWnd);

		}

		else
		{
			return 0;   //0を返さないと終了してしまう
		}

		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);  //既定の処理を返す
}

//=============
//初期化処理
//=============
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;            //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	 //プレゼンテーションパラメータ

	 //Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));    //パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WINDTH;  //ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;  //ゲーム画面サイズ(高さ
	d3dpp.BackBufferFormat = d3ddm.Format;  //バックばふぁの形式
	d3dpp.BackBufferCount = 1;				//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   //ダブルバッファの切り替え(映像信号の同期)
	d3dpp.EnableAutoDepthStencil = TRUE;    //デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;			//デプスバッファに16bitを使う
	d3dpp.Windowed = bWindow;							//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;  //リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;  //インターバル

															   //Direct3Dデバイスの作成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{

			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);


	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	//サウンドの初期化処理
	InitSound(hWnd);

	////モードの設定
	//SetMode(g_mode);

	//デバッグ表示用フォントの作成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ゲームパッドの初期化処理
	InitGamepad();

	//フェードの設定
	InitFade(g_mode);

	return S_OK;
}

//======================
//終了処理
//======================
void Uninit(void)
{
	//キーボードの終了処理
	UninitKeyboard();

	//ゲームパッドの終了処理
	UninitGamepad();

	//タイトルの終了処理
	UninitTitle();

	//チュートリアルの終了処理
	UninitTutorial();

	//ゲームの終了処理
	UninitGame();

	//リザルトの終了処理
	UninitResult();

	//ゲームオーバーの終了処理
	UninitGameover();

	//ランキングの終了処理
	UninitRanking();

	//フェードの終了処理
	UninitFade();

	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();

		g_pFont = NULL;
	}

	//サウンドの停止
	StopSound();

	//サウンドの終了処理
	UninitSound();

	//各種オブジェクトの終了処理
	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;

	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
//==========================
//更新処理
//==========================
void Update(void)
{
	//キーボードの更新
	UpdateKeyboard();

	//ゲームパッドの更新
	UpdateGamepad();

	switch (g_mode)
	{
	case MODE_TITLE:
			UpdateTitle();
		break;

	case MODE_TUTORIAL:
		UpdateTutorial();
		break;

	case MODE_GAME:
		UpdateGame();
		break;

	case MODE_RESULT:
		UpdateResult();
		break;

	case MODE_GAMEOVER:
		UpdateGameover();
		break;

	case MODE_RANKING:
		UpdateRanking();
		break;
	}

	//フェードの更新
	UpdateFade();
}

//======================
//描画処理
//======================
void Draw(void)
{//画面クリア(バックバッファとZバッファのクリア)

	g_pD3DDevice->Clear(0,NULL,(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

//描画開始
   if (SUCCEEDED(g_pD3DDevice->BeginScene()))
   {//描画処理が成功した場合
	//各種オブジェクトの描画処理

	   switch (g_mode)
	   {
	   case MODE_TITLE:
		   DrawTitle();
		   break;

	   case MODE_TUTORIAL:
			   DrawTutorial();
			   break;

	   case MODE_GAME:
		   DrawGame();
		   break;

	   case MODE_RESULT:
		   DrawResult();
		   break;

	   case MODE_GAMEOVER:
		   DrawGameover();
		   break;

	   case MODE_RANKING:
		   DrawRanking();
		   break;
	   }

	   //フェードの描画処理
	   DrawFade();

	//描画終了
	g_pD3DDevice->EndScene();

   }

   //バックバッファとフロントバッファの入れ替え
   g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//======================
//デバイスの取得
//======================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//======================
//FPSの表示
//======================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WINDTH,SCREEN_HEIGHT };

	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//======================
//数を表示
//======================
void DrawEnemyCnt(void)
{
	RECT rect = { 0,20,SCREEN_WINDTH,SCREEN_HEIGHT };

	char aStr[256];
	int Enemy = ENEMY();
	int g_nCntKey = GetKey();

	//文字列に代入
	wsprintf(&aStr[0], "\n\n[鍵の数] : %d\n\n[敵の数] : %d \n\n[キーボード]\n\n左移動 : A\n右移動 : D\nジャンプ : J\n\n攻撃 : SPACE\n\n[ゲームパッド]\n\n移動 : スティック\nジャンプ : B\n\n攻撃 : A",g_nCntKey, Enemy);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255 , 255, 255, 255));

}

//====================
//モードの設定処理
//====================
void SetMode(MODE mode)
{
	//終了処理
	switch (mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_TUTORIAL:
		UninitTutorial();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	case MODE_GAMEOVER:
		UninitGameover();
		break;

	case MODE_RANKING:
		UninitRanking();
		break;
	}

	//初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_TUTORIAL:
		InitTutorial();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;

	case MODE_GAMEOVER:
		InitGameover();
		break;

	case MODE_RANKING:
		InitRanking();
		break;
	}

	g_mode = mode; //モードを取得する
}

//=================
//モードの取得
//=================
MODE GetMode(void)
{
	return g_mode;
}