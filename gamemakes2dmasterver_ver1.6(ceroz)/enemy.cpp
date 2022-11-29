//============================
//
//敵の処理(enemy.cpp)
//Author:早川 友貴
//
//============================
#include "enemy.h"
#include "player.h"
#include "sound.h"
#include "game.h"
//#include "particle.h"
//#include "effect.h"

//マクロ
#define NUM_ENEMY (2)  //敵の種類
#define X_DATA (1.0f) //Xの速度
#define Y_DATA (2.0f) //Yの速度
#define TRY_LIFE       (1)	//三角形の体力
#define PARTICLE_LIFE   (100) //パーティクルの体力
#define MOVE_PARTICLE	(100.0f) //パーティクルの移動量
#define PARTICLE_USELIFE	(1)		 //パーティクルのライフ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEnemy[MAX_ENEMY] = {};  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL; //頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];  //敵の情報
int g_EnemyCount;         //敵カウント
//float g_fLengthEnemy;
//float g_fAngleEnemy;
//int g_GetLife;   //パーティクルのライフを受け取る

//========================
//敵の初期化処理
//========================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	g_EnemyCount = 0;  //初期化

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\zombie1.png",
		&g_pTextureEnemy[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\zombie1.png",
		&g_pTextureEnemy[1]);

	////対角線の長さを算出する
	//g_fLengthEnemy = sqrtf(BULLET_WINDS * BULLET_WINDS + BULLET_HEIGHT * BULLET_HEIGHT) * 0.5f;

	////対角線の角度を算出する
	//g_fAngleEnemy = atan2f(BULLET_WINDS, BULLET_HEIGHT);

	//敵の情報を初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //位置を初期化

		g_aEnemy[nCntEnemy].nType = 0; //敵の種類を初期化

		g_aEnemy[nCntEnemy].nLife = 1;		   //体力を初期化

		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	   //移動量を初期化

		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;  //状態

		g_aEnemy[nCntEnemy].nCounterState = 0; //状態管理カウンター

		g_aEnemy[nCntEnemy].bUse = false;  //使用していない状態にする

		float g_fLengthEnemy = 0.0f;

		float g_fAngleEnemy = 0.0f;

		//g_GetCol = 1.0f;	//変わる色を受け取る変数
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 10.0f, g_aEnemy[nCntEnemy].pos.y - 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 10.0f, g_aEnemy[nCntEnemy].pos.y - 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 10.0f, g_aEnemy[nCntEnemy].pos.y + 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 10.0f, g_aEnemy[nCntEnemy].pos.y + 10.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点データのポインタを4つ分進める

	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//========================
//敵の終了処理
//========================
void UninitEnemy(void)
{
	int nCntEnemy;

	//4枚目のテクスチャの破棄
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();
			g_pTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//=================================
//敵の更新処理
//=================================
void UpdateEnemy(void)
{
	int nCntEnemy = 0;
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使われている場合

				if (g_aEnemy[nCntEnemy].nType == 0)
				{
					//敵の移動処理
					g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].move.x;

					//壁に当たったら跳ね返る処理
					if (g_aEnemy[nCntEnemy].pos.x <= 100 || g_aEnemy[nCntEnemy].pos.x >= 1200)
					{
						g_aEnemy[nCntEnemy].move.x *= -1;
					}

					if (g_aEnemy[nCntEnemy].pos.x <= 100)
					{
						//テクスチャ座標の設定
						pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
						pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
						pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
						pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
					}

					else if (g_aEnemy[nCntEnemy].pos.x >= 1200)
					{
						//テクスチャ座標の設定
						pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + 0.5f);
						pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + 0.5f);
						pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f + 0.5f);
						pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f + 0.5f);
					}
					
				}

				if (g_aEnemy[nCntEnemy].nType == 1)
				{
					//敵の移動処理
					g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].move.x;

					//壁に当たったら跳ね返る処理
					if (g_aEnemy[nCntEnemy].pos.x <= 500 || g_aEnemy[nCntEnemy].pos.x >= 800)
					{
						g_aEnemy[nCntEnemy].move.x *= -1;
					}

					if (g_aEnemy[nCntEnemy].pos.x <= 500)
					{
						//テクスチャ座標の設定
						pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
						pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
						pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
						pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
					}

					else if (g_aEnemy[nCntEnemy].pos.x >= 800)
					{
						//テクスチャ座標の設定
						pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + 0.5f);
						pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + 0.5f);
						pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f + 0.5f);
						pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f + 0.5f);
					}
				}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y - 20.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 20.0f, g_aEnemy[nCntEnemy].pos.y - 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 20.0f, g_aEnemy[nCntEnemy].pos.y + 20.0f, 0.0f);

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:

				break;

			case ENEMYSTATE_DAMEGE:

				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				}
				break;
			}
		}

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//==========================
//敵の描画処理
//==========================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	g_EnemyCount = 0;

	for (nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCnt].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //プリミティブの種類

			g_EnemyCount++;         //敵カウント
		}

		else
		{

		}
	}

}
//====================
//敵の設定処理
//====================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy = 0;

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//敵が使用されていない
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(X_DATA, Y_DATA, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y - 20.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 20.0f, g_aEnemy[nCntEnemy].pos.y - 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 20.0f, g_aEnemy[nCntEnemy].pos.y + 20.0f, 0.0f);

			g_aEnemy[nCntEnemy].bUse = true;

			switch (g_aEnemy[nCntEnemy].nType)
			{
			case 0:
				g_aEnemy[nCntEnemy].nLife = TRY_LIFE;

				break;

			case 1:
				g_aEnemy[nCntEnemy].nLife = TRY_LIFE;

				break;
			}
			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

}
//=================
//敵の取得
//=================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0]; //敵の情報の先頭アドレスを渡す
}
//====================
//敵の数を返す
//===================
int ENEMY(void)
{
	return g_EnemyCount;
}
//==========================
//敵のヒット処理
//==========================
void HitEnemy(int nCntEnemy, int nDamage)
{
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();
	LPDIRECT3DDEVICE9 pDevice;
	/*g_GetCol = ChangeEffect();*/

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	pVtx += nCntEnemy * 4;

	/*SetParticle(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, (g_aEnemy[nCntEnemy].pos.y + 50.0f), g_aEnemy[nCntEnemy].pos.z),
		D3DXVECTOR3(g_aEnemy[nCntEnemy].move.x, g_aEnemy[nCntEnemy].move.y + MOVE_PARTICLE, g_aEnemy[nCntEnemy].move.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		10.0f,
		PARTICLE_DAMAGE,
		PARTICLE_USELIFE);*/

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{//敵の体力が0になったら
		//爆発の設定

 		g_aEnemy[nCntEnemy].bUse = false;

		for (int nCount = 0; nCount < NUM_ENEMY; nCount++, pEnemy++)
		{//敵が使用されている

			if (pPlayer->pos.x - 20.0f >= (pEnemy->pos.x - 20.0f) - ((pPlayer->pos.x - (pPlayer->pos.x - 20.0f)) * 2)
				&& pPlayer->pos.x + 20.0f <= (pEnemy->pos.x + 20.0f) + ((pPlayer->pos.x - (pPlayer->pos.x - 20.0f)) * 2)
				&& pPlayer->pos.y - 20.0f >= (pEnemy->pos.y - 20.0f) - ((pPlayer->pos.y - (pPlayer->pos.y - 20.0f)) * 2)
				&& pPlayer->pos.y + 20.0f <= (pEnemy->pos.y + 20.0f) + ((pPlayer->pos.y - (pPlayer->pos.y - 20.0f)) * 2))
			{//プレイヤーと敵が当たった	

			}
		}

		g_EnemyCount--;  //敵の総数を減らす
	}

	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;

		g_aEnemy[nCntEnemy].nCounterState = 5;

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

}
