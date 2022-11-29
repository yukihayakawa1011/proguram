//============================
//
//鍵処理(key.cpp)
//Author:早川 友貴
//
//============================
#include "key.h"
#include "sound.h"
#include "fade.h"
#include "life.h"
#include "player.h"

//マクロ定義
#define NUM_PLACE (3)		//鍵の数
#define KEY_DATA (10.0f)      //鍵のサイズ
#define KEY_GET  (30.0f)  //鍵の当たり判定

typedef enum
{
	KEYTYPE_RED = 0,
	KEYTYPE_BLUE,
	KEYTYPE_GREEN,
	KEYTYPE_MAX
}KEYTYPE;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureKey[KEYTYPE_MAX] = {};  //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKey = NULL; //頂点バッファへのポインタ
D3DXVECTOR3 g_posKey[NUM_PLACE];  //鍵の位置
KEYSTATE g_Key[NUM_PLACE];
int nKey = 3;

//テクスチャファイル名
const char *c_apFilenameKey[KEYTYPE_MAX] =
{
	"data/TEXTURE/keyred.png",
	"data/TEXTURE/keyblue.png",
	"data/TEXTURE/keygreen.png",
};

//=============================
//  鍵の初期化
//=============================
void InitKey(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntKey;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFilenameKey[nCntKey],
			&g_apTextureKey[nCntKey]);
	}

	g_posKey[0] = D3DXVECTOR3(100.0f , 590.0f, 0.0f);  //位置を初期化
	g_posKey[1] = D3DXVECTOR3(1200.0f , 370.0f, 0.0f);  //位置を初期化
	g_posKey[2] = D3DXVECTOR3(1200.0f , 70.0f, 0.0f);  //位置を初期化

	nKey = 3;

	//鍵の情報を初期化
	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		g_Key[nCntKey].bUse = true;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * KEYTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffKey,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posKey[nCntKey].x - KEY_DATA, g_posKey[nCntKey].y - KEY_DATA, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posKey[nCntKey].x + KEY_DATA, g_posKey[nCntKey].y - KEY_DATA, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posKey[nCntKey].x - KEY_DATA, g_posKey[nCntKey].y + KEY_DATA, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posKey[nCntKey].x + KEY_DATA, g_posKey[nCntKey].y + KEY_DATA, 0.0f);

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

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffKey->Unlock();
}

//=====================
//鍵の終了処理
//=====================
void UninitKey(void)
{
	int nCntkey;

	//テクスチャの破棄
	for (nCntkey = 0; nCntkey < KEYTYPE_MAX; nCntkey++)
	{
		if (g_apTextureKey[nCntkey] != NULL)
		{
			g_apTextureKey[nCntkey]->Release();
			g_apTextureKey[nCntkey] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffKey != NULL)
	{
		g_pVtxBuffKey->Release();
		g_pVtxBuffKey = NULL;
	}
}

//==========================
//鍵の更新処理
//=========================
void UpdateKey(void)
{
	FADE pFade;
	pFade = GetFade();
	LPDIRECT3DDEVICE9 pDevice;
	int nCntKey;
	Player *pPlayer = GetPlayer();

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}

	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{//鍵が使用されていたら
			if (g_posKey[nCntKey].x + KEY_DATA + KEY_GET >= pPlayer->pos.x
				&& g_posKey[nCntKey].x - KEY_DATA - KEY_GET<= pPlayer->pos.x
				&& g_posKey[nCntKey].y + KEY_DATA + KEY_GET >= pPlayer->pos.y
				&& g_posKey[nCntKey].y - KEY_DATA - KEY_GET <= pPlayer->pos.y)
			{//プレイヤーと鍵の当たり判定
				nKey--;

				g_Key[nCntKey].bUse = false;

				PlaySound(SOUND_LABEL_KEY);

			}
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffKey->Unlock();

}

//======================
//鍵の描画処理
//======================
void DrawKey(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntKey = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffKey, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureKey[nCntKey]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntKey * 4, 2);
		}
	}
}

//==========================
//鍵の情報を渡す処理
//==========================
int GetKey(void)
{
	return nKey;
}