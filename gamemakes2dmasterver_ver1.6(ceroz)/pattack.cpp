//======================
//
//攻撃の処理(pattack.cpp)
//Author: 早川 友貴
//
//======================

#include "sound.h"
#include "pattack.h"
#include "player.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePattack = NULL;  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPattack = NULL; //頂点バッファへのポインタ
PATTACK g_aPattack;  //攻撃の情報

//======================
//攻撃の初期化
//======================
void InitPattack(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\playerattackanim.png",
		&g_pTexturePattack);

	g_aPattack.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置を初期化

	g_aPattack.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);    //色を初期化

	g_aPattack.nCounterAnim = 0;  //アニメーションカウンターを初期化

	g_aPattack.nPatternAnim = 0;  //アニメーションパターンNo.を初期化

	g_aPattack.bUse = false;  //使用していない状態にする

								//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPattack,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPattack->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aPattack.pos.x - 20.0f, g_aPattack.pos.y - 150.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPattack.pos.x + 20.0f, g_aPattack.pos.y - 150.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPattack.pos.x - 20.0f, g_aPattack.pos.y - 50.0f , 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPattack.pos.x - 20.0f, g_aPattack.pos.y - 50.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffPattack->Unlock();
}

//===========================
//攻撃の終了処理
//===========================
void UninitPattack(void)
{
	//テクスチャの破棄
	if (g_pTexturePattack != NULL)
	{
		g_pTexturePattack->Release();
		g_pTexturePattack = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPattack != NULL)
	{
		g_pVtxBuffPattack->Release();
		g_pVtxBuffPattack = NULL;
	}
}

//==================
//攻撃の更新処理
//==================
void UpdatePattack(void)
{
}

//======================
//攻撃の描画処理
//======================
void DrawPattack(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPattack, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePattack);

	if (g_aPattack.bUse == true)
	{//攻撃が使用されている
	 //ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	}
}

//======================
//攻撃の設定処理
//======================
void SetPattack(D3DXVECTOR3 pos)
{

	VERTEX_2D *pVtx;    //頂点情報へのポインタ
						//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPattack->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aPattack.bUse == false)
	{//攻撃が使用されていない

	 //頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aPattack.pos.x - 50.0f, g_aPattack.pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPattack.pos.x + 50.0f, g_aPattack.pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPattack.pos.x - 50.0f, g_aPattack.pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPattack.pos.x + 50.0f, g_aPattack.pos.y + 50.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aPattack.nPatternAnim) * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aPattack.nPatternAnim) * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aPattack.nPatternAnim) * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aPattack.nPatternAnim) * 0.1f, 1.0f);

		//g_aExplosion[nCntEXPLOSION].move = move;
		//g_aExplosion[nCntEXPLOSION].nLife = 100;
		g_aPattack.bUse = true;  //使用している状態にする
		g_aPattack.nCounterAnim = 0;  //アニメーションカウンター
		g_aPattack.nPatternAnim = 0;  //アニメーションパターンNo.
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPattack->Unlock();
}

//======================
//攻撃の情報を渡す
//======================
PATTACK *GetPattack(void)
{
	return  &g_aPattack;
}

//=====================
//右攻撃の処理
//=====================
void RightPattack(void)
{
	/*int nCnt;*/

	Player *pPlayer = GetPlayer();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPattack->Lock(0, 0, (void**)&pVtx, 0);

	g_aPattack.bUse = true;


	//for (nCnt = 0; nCnt < 4; nCnt++)
	//{
		if (g_aPattack.bUse == true)
		{//攻撃が使用されている

			g_aPattack.nCounterAnim++;

		 //頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - 20.0f, pPlayer->pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x + 20.0f, pPlayer->pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x - 20.0f, pPlayer->pos.y - 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + 20.0f, pPlayer->pos.y - 0.0f, 0.0f);

			if ((g_aPattack.nCounterAnim % 6) == 0)
			{
				g_aPattack.nPatternAnim = (g_aPattack.nPatternAnim + 1) % 4;		//パターンNO.を更新する
			}
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f + 0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f + 0.25f, 0.5f);

			////総パターン数を超えた
			//if (g_aPattack.nPatternAnim == 3)
			//{
			//	g_aPattack.bUse = false;  //使用していない状態にする
			//}

		}

	//}
	//頂点バッファをアンロックする
	g_pVtxBuffPattack->Unlock();
}

//=====================
//左攻撃の処理
//=====================
void LeftPattack(void)
{
	/*int nCnt;*/

	Player *pPlayer = GetPlayer();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPattack->Lock(0, 0, (void**)&pVtx, 0);

	g_aPattack.bUse = true;

	/*for (nCnt = 0; nCnt < 4; nCnt++)
	{*/
		if (g_aPattack.bUse == true)
		{//攻撃が使用されている

			g_aPattack.nCounterAnim++;

		 //頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - 20.0f, pPlayer->pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x + 20.0f, pPlayer->pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x - 20.0f, pPlayer->pos.y - 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + 20.0f, pPlayer->pos.y - 0.0f, 0.0f);

			if ((g_aPattack.nCounterAnim % 6) == 0)
			{
				g_aPattack.nPatternAnim = (g_aPattack.nPatternAnim + 1) % 4;		//パターンNO.を更新する
			}

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f + 0.25f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f + 0.25f, 1.0f);
		/*}*/

		////総パターン数を超えた
		//if (g_aPattack.nPatternAnim == 3)
		//{
		//	g_aPattack.bUse = false;  //使用していない状態にする
		//}

	}

	//頂点バッファをアンロックする
	g_pVtxBuffPattack->Unlock();
}
