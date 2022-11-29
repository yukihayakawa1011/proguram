//============================
//
//エディット処理(title.h)
//Author:早川 友貴
//
//============================
#include "edit.h"
#include "main.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "block.h"
//#include "ranking.h"

//マクロ
#define EDIT_MOVE (10.0f)  //エディットの移動量
#define EDIT_X  (20.0f)
#define EDIT_Y  (20.0f)

//エディットの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	bool bUse;
}Edit;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEdit = NULL;		//テクスチャ(2枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEdit = NULL;  //頂点バッファへのポインタ
Edit g_Edit;  //エディットの情報

//======================
//エディット画面の初期化処理
//======================
void InitEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//エディットの情報を初期化
	g_Edit.pos = D3DXVECTOR3(g_Edit.pos.x, g_Edit.pos.y, 0.0f);

	g_Edit.bUse = false; //　使用しているかどうかを初期化

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block000.png",
		&g_pTextureEdit);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEdit,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Edit.pos.x, g_Edit.pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Edit.pos.x + 20.0f, g_Edit.pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Edit.pos.x, g_Edit.pos.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Edit.pos.x + 20.0f, g_Edit.pos.y + 20.0f, 0.0f);
		
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
		g_pVtxBuffEdit->Unlock();
}

//============================
//エディットの終了処理
//============================
void UninitEdit(void)
{
		if (g_pTextureEdit != NULL)
		{
			g_pTextureEdit->Release();
			g_pTextureEdit = NULL;
		}

	//頂点バッファの破棄
	if (g_pVtxBuffEdit != NULL)
	{
		g_pVtxBuffEdit->Release();
		g_pVtxBuffEdit = NULL;
	}
}

//===============================
//エディット画面の更新処理
//===============================
void UpdateEdit(void)
{
	if (GetKeyboardTrigger(DIK_LEFTARROW) == true)
	{
		g_Edit.pos.x -= EDIT_MOVE;
	}

	if (GetKeyboardTrigger(DIK_RIGHTARROW) == true)
	{
		g_Edit.pos.x += EDIT_MOVE;
	}

	if (GetKeyboardTrigger(DIK_DOWNARROW) == true)
	{
		g_Edit.pos.y += EDIT_MOVE;
	}

	if (GetKeyboardTrigger(DIK_UPARROW) == true)
	{
		g_Edit.pos.y -= EDIT_MOVE;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetBlock(D3DXVECTOR3(g_Edit.pos.x - 20.0f, g_Edit.pos.y - 20.0f, 0.0f), 40.0f, 40.0f);
		g_Edit.bUse = true;
	}

	if (GetKeyboardTrigger(DIK_BACKSPACE) == true)
	{
		DelEdit();
	}

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Edit.pos.x - EDIT_X, g_Edit.pos.y - EDIT_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Edit.pos.x + EDIT_X, g_Edit.pos.y - EDIT_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Edit.pos.x - EDIT_X,g_Edit.pos.y + EDIT_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Edit.pos.x + EDIT_X, g_Edit.pos.y +EDIT_Y, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffEdit->Unlock();

}

//=================================
//エディット画面の描画処理
//=================================
void DrawEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEdit, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureEdit);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2); //プリミティブの種類
}

//===========================
//ブロックを削除する処理
//===========================
void DelEdit(void)
{
	int nCnt;

	BLOCK *Block = GetBlock();

	for (nCnt = 0; nCnt < MAX_BLOCK; nCnt++, Block++)
	{
		if (Block->bUse == true)
		{

			if (nCnt == 56)
			{
				int a = 0;
			}

			if (g_Edit.pos.x - 20.0f == Block->pos.x
			&&  g_Edit.pos.y - 20.0f == Block->pos.y)
			{
				Block->bUse = false;
			}
		}
	}
}