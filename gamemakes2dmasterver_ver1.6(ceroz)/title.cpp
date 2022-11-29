//============================
//
//タイトル処理(title.h)
//Author:早川 友貴
//
//============================
#include "title.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "ranking.h"

//マクロ
#define NUM_TITLE (2) //タイトル画面に使う
#define MOVE_COLOR (0.01f) //色の移動量
#define MOVE_ENTER (0.5f)  //エンター押した後の移動
#define CNT_DATA    (360)  //自動遷移の数を数えるデータ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureTitle[NUM_TITLE] = {};		//テクスチャ(2枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;  //頂点バッファへのポインタ
bool g_Keycheck; //キーが押されたか確認する
D3DXCOLOR col;			//色に関して使う
float g_Movecol;		//色の移動量
float g_Moveenter;		//エンター押した後の移動量
int g_CntTrance;		//ランキングに遷移するまでの時間を数えるデータ

//======================
//タイトル画面の初期化処理
//======================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;

	//デバイスの取得
	pDevice = GetDevice();

	//初期化(キーチェック)
	 g_Keycheck = false;

	 //初期化(色の移動量)
	 g_Movecol = MOVE_COLOR;
	 g_Moveenter = MOVE_ENTER;

	 //カラーを初期化
	 col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	 //ランキングに遷移する時間を数えるデータを初期化
	 g_CntTrance = 0;

	 //プレスエンター点滅を初期化
	 col.a = g_Movecol;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\escape.png",
		&g_apTextureTitle[0]);
	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pressenter.png",
		&g_apTextureTitle[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < NUM_TITLE; nCnt++)
	{
		if (nCnt == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}

		if(nCnt == 1)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 300.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(700.0f, 300.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(700.0f, 600.0f, 0.0f);
		}

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

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM000);
}

//============================
//タイトルの終了処理
//============================
void UninitTitle(void)
{
	//サウンドの停止
	StopSound();

	int nCnt;

	for (nCnt = 0; nCnt < NUM_TITLE; nCnt++)
	{
		if (g_apTextureTitle[nCnt] != NULL)
		{
			g_apTextureTitle[nCnt]->Release();
			g_apTextureTitle[nCnt] = NULL;
		}
	}

		//頂点バッファの破棄
		if (g_pVtxBuffTitle != NULL)
		{
			g_pVtxBuffTitle->Release();
			g_pVtxBuffTitle = NULL;
		}
}

//===============================
//タイトル画面の更新処理
//===============================
void UpdateTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	FADE pFade;
	pFade = GetFade();
	int nCnt = 0;

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//タイトルのプレスエンターを点滅する処理
	for (nCnt = 0; nCnt < NUM_TITLE; nCnt++)
	{
		if (nCnt == 1)
		{
			col.a -= g_Movecol;

			if (col.a < 0.0f || col.a > 1.0f)
			{
			 g_Movecol *= -1.0f;
			}

			//頂点カラーの設定
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	g_CntTrance++;

	if (g_CntTrance >= CNT_DATA)
	{//6秒経ったら
	 //モード設定(ランキング画面に移行)

		ResetData();

		if (pFade == FADE_NONE)
		{
			SetFade(MODE_RANKING);
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
	{//決定(ENTERキー)が押された
		if (g_Keycheck == false)
		{
			//モード設定(ゲーム画面に移行)

			//サウンドの再生
			PlaySound(SOUND_LABEL_ENTER);

			g_Movecol = g_Moveenter;

			g_Keycheck = true;

			SetFade(MODE_TUTORIAL);
		}
	}
}

//=================================
//タイトル画面の描画処理
//=================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < NUM_TITLE; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTitle[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //プリミティブの種類
	}

#ifdef _DEBUG

	//FPSの表示
	DrawFPS();

#endif

}