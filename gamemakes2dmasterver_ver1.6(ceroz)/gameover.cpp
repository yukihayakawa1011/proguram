//============================
//
//ゲームオーバー処理(gameover.h)
//Author:早川 友貴
//
//============================
#include "gameover.h"
#include "result.h"
#include "main.h"
#include "game.h"
#include "sound.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "time.h"

//マクロ定義
#define TRANCE_DATA (300)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureGameover = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameover = NULL;  //頂点バッファへのポインタ

int g_GameoverTrance; //遷移までの時間を図る処理

//======================
//ゲームオーバー画面の初期化処理
//======================
void InitGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//遷移までの時間を図る処理を初期化
	g_GameoverTrance = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gameover.png",
		&g_pTextureGameover);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameover,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGameover->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffGameover->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM002);		//ゲームオーバーBGM

	//サウンドの再生
	PlaySound(SOUND_LABEL_GAMEOVER);   //ゲームオーバーボイス
}

//============================
//ゲームオーバーの終了処理
//============================
void UninitGameover(void)
{
	//サウンドの停止
	StopSound();

	if (g_pTextureGameover != NULL)
	{
		g_pTextureGameover->Release();
		g_pTextureGameover = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGameover != NULL)
	{
		g_pVtxBuffGameover->Release();
		g_pVtxBuffGameover = NULL;
	}
}

//===============================
//ゲームオーバー画面の更新処理
//===============================
void UpdateGameover(void)
{
	FADE pFade;
	pFade = GetFade();

	g_GameoverTrance++;

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_A, 0) == true || g_GameoverTrance >= TRANCE_DATA)
	{//決定(ENTERキー)が押された
	 //モード設定(ゲーム画面に移行)

		if (pFade == FADE_NONE)
		{
			SetFade(MODE_RANKING);
		}
	}
}

//=================================
//ゲームオーバー画面の描画処理
//=================================
void DrawGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGameover, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGameover);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類

#ifdef _DEBUG

													   //FPSの表示
	DrawFPS();

#endif
}
