//============================
//
//ブロックの処理(block.cpp)
//Author:早川 友貴
//
//============================
#include "block.h"
#include "player.h"
#include "edit.h"

//マクロ
#define BLOCK_X (200.0f)
#define BLOCK_Y (20.0f)
#define BLOCK_HEIGHT (20.0f)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL; //頂点バッファへのポインタ
BLOCK g_aBlock[MAX_BLOCK];

//========================
//ブロックの初期化処理
//========================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

    //テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block.png",
		&g_pTextureBlock);

	//ブロックの情報を初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(500.0f, 300.0f, 0.0f);  //位置を初期化

		g_aBlock[nCntBlock].fWidth = 50.0f;	  //幅の初期化

		g_aBlock[nCntBlock].fHeight = 50.0f;	  //高さの初期化

		g_aBlock[nCntBlock].bUse = false;  //使用していない状態にする
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_X, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_X, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

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
	g_pVtxBuffBlock->Unlock();
}

//========================
//ブロックの終了処理
//========================
void UninitBlock(void)
{
	/*int nCntBlock;*/

	//テクスチャの破棄
		if (g_pTextureBlock != NULL)
		{
			g_pTextureBlock->Release();
			g_pTextureBlock = NULL;
		}

	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}
//=================================
//ブロックの更新処理
//=================================
void UpdateBlock(void)
{
}

//==========================
//ブロックの描画処理
//==========================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBlock);

		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse == true)
			{
				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2); //プリミティブの種類
			}
		}
}

//====================
//ブロックの設定処理
//====================
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nCntBlock;

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			//ブロックが使用されていない
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].bUse = true;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			break;
		}
		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

}

//===============================
//ブロックの当たり判定
//===============================
bool colisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight,bool bJump)
{
	int nCntBlock;
	bool bLand = false; //着地したかどうか

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//ブロックが使われていたら
			if (bJump == true)
			{//ジャンプが使用されていたら
				if (pPos->y > g_aBlock[nCntBlock].pos.y
					&& pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + BLOCK_Y)
				{//ブロックのYの範囲内の時,横の当たり判定
					if (pPosOld->x + fWidth <= g_aBlock[nCntBlock].pos.x
						&&pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x - fWidth;
						pMove->x = 0.0f; //移動量を0にする
					}

					else if (pPosOld->x - fWidth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
						&& pPos->x - fWidth < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
					{
						pPos->x = fWidth + g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
						pMove->x = 0.0f; //移動量を0にする
					}
				}

				if (pPos->x - fWidth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
					&& pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x)
				{//ブロックの範囲内の時,縦の当たり判定
					if (pPosOld->y <= g_aBlock[nCntBlock].pos.y
						&& pPos->y >= g_aBlock[nCntBlock].pos.y)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y; //ブロックの上に立たせる
						pMove->y = 0.0f; //移動量を0にする
					}

					else if (pPosOld->y - fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight
						&& pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
					{//ブロックより下で範囲内の時
						pPos->y = fHeight + g_aBlock[nCntBlock].pos.y + 50.0f;
						pMove->y = 0.0f; //移動量を0にする
					}
				}
			}

			else
			{//ジャンプが使用されていなかったら
				if (pPos->x - fWidth < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
					&& pPos->x + fWidth > g_aBlock[nCntBlock].pos.x)
				{//ブロックの範囲内の時,縦の当たり判定
					if (pPosOld->y <= g_aBlock[nCntBlock].pos.y
						&& pPos->y > g_aBlock[nCntBlock].pos.y)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y; //ブロックの上に立たせる
						pMove->y = 0.0f; //移動量を0にする
					}

					else if (pPosOld->y - fHeight > g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight
						&& pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
					{//ブロックより下で範囲内の時
						pPos->y = fHeight + g_aBlock[nCntBlock].pos.y + 50.0f;
						pMove->y = 0.0f; //移動量を0にする
					}
				}

				if (pPos->y > g_aBlock[nCntBlock].pos.y
					&& pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + BLOCK_Y)
				{//ブロックのYの範囲内の時,横の当たり判定
					if (pPosOld->x + fWidth <= g_aBlock[nCntBlock].pos.x
						&&pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x - fWidth;
						pMove->x = 0.0f; //移動量を0にする
					}

					else if (pPosOld->x - fWidth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
						&& pPos->x - fWidth < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
					{
						pPos->x = fWidth + g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
						pMove->x = 0.0f; //移動量を0にする
					}
				}
			}
		}
	}
	return bLand;
}

//========================
//ブロックを明け渡す
//========================
BLOCK *GetBlock(void)
{
	return &g_aBlock[0];
}