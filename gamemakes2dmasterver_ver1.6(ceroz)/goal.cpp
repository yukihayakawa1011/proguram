//============================
//
//ゴール処理(goal.h)
//Author:早川 友貴
//
//============================
#include "goal.h"
#include "main.h"
#include "game.h"
//#include "sound.h"
#include "player.h"
#include "input.h"
#include "fade.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;  //頂点バッファへのポインタ
GOAL g_Goal; //ゴールの情報

//======================
//ゴール画面の初期化処理
//======================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ゴールの位置を初期化
	g_Goal.pos = D3DXVECTOR3(1250.0f, 700.0f, 0.0f);

	//ゴールの有無を初期化
	g_Goal.bUse = false;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\door.png",
		&g_pTextureGoal);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(1250.0f, 630.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 630.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1250.0f, 710.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 710.0f, 0.0f);

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
	g_pVtxBuffGoal->Unlock();

	////サウンドの再生
	//PlaySound(SOUND_LABEL_BGM002);
}

//============================
//ゴールの終了処理
//============================
void UninitGoal(void)
{
	////サウンドの停止
	//StopSound();

	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//===============================
//ゴール画面の更新処理
//===============================
void UpdateGoal(void)
{
}

//=================================
//ゴール画面の描画処理
//=================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGoal);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類

													   ////スコアの描画
													   //DrawScore();
}

//==========================
//ゴールの情報を明け渡す処理
//==========================
GOAL GetGoal(void)
{
	return g_Goal;
}
