//============================
//
//暗闇処理(black.h)
//Author:早川 友貴
//
//============================
#include "black.h"
#include "main.h"
#include "game.h"
#include "player.h"

//マクロ
#define BLACK_X (1500.0f)  //暗闇の幅
#define BLACK_Y (1000.0f)  //暗闇の高さ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBlack = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlack = NULL;  //頂点バッファへのポインタ

//======================
//暗闇画面の初期化処理
//======================
void InitBlack(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer = GetPlayer();

	//デバイスの取得
	pDevice = GetDevice();

	//プレイヤーの情報を初期化
	pPlayer->bUse = true;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\black1.png",
		&g_pTextureBlack);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlack,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlack->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffBlack->Unlock();

}

//============================
//暗闇の終了処理
//============================
void UninitBlack(void)
{

	if (g_pTextureBlack != NULL)
	{
		g_pTextureBlack->Release();
		g_pTextureBlack = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBlack != NULL)
	{
		g_pVtxBuffBlack->Release();
		g_pVtxBuffBlack = NULL;
	}
}

//===============================
//暗闇画面の更新処理
//===============================
void UpdateBlack(void)
{
	//プレイヤーの情報を受け取る
	Player *pPlayer = GetPlayer();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlack->Lock(0, 0, (void**)&pVtx, 0);

	if (pPlayer->bUse == true)
	{//プレイヤーが使用されていたら
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - BLACK_X, pPlayer->pos.y - BLACK_Y,0.0f);
		pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x + BLACK_X, pPlayer->pos.y - BLACK_Y,0.0f);
		pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x - BLACK_X, pPlayer->pos.y + BLACK_Y,0.0f);
		pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + BLACK_X, pPlayer->pos.y + BLACK_Y,0.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlack->Unlock();
}

//=================================
//暗闇画面の描画処理
//=================================
void DrawBlack(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlack, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBlack);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類
}
