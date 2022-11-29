//============================
//
//プレイヤー処理(player.cpp)
//Author:早川 友貴
//
//============================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "black.h"
#include "life.h"
#include "game.h"
#include "enemy.h"
#include "edit.h"
#include "sound.h"
#include "pattack.h"

//マクロ
#define Press_PLAYER (2.0f)
#define PLAYER_JUNP  (20.0f)
#define PLAYER_HEIGHT (19.0f) 
#define PLAYER_WIDTH (9.0f)
#define PLAYER_HITSPACEX (10.0f) //プレイヤーの当たり判定X
#define PLAYER_HITSPACEY (10.0f) //プレイヤーの当たり判定Y
#define PLAYER_ATTACKSPACE (20.0f) //プレイヤーの攻撃判定
#define ENEMY_HITSPACE (10.0f)  //敵の当たり判定
#define ENEMY_DAMAGESPACE (20.0f) //敵の攻撃を受ける範囲


//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;        //テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;  //頂点バッファへのポインタ
Player g_player;						//プレイヤーの情報
int g_nCounterAnimPlayer;				//アニメーションカウンター
int g_nPatternAnimPlayer;					//アニメーションパターンNo.               
D3DXVECTOR3 g_moverotPlayer;				//向きの移動量
float g_fLengthPlayer;						//対角線の長さ
float g_movefLengthPlayer;                   //対角線の移動量
float g_fAnglePlayer;						//対角線の角度

//======================
//プレイヤーの初期化処理
//======================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\playerwalkanim.png",
		&g_pTexturePlayer);

	g_nCounterAnimPlayer = 0;  //カウンターを初期化する
	g_nPatternAnimPlayer = 0;	   //パターンを初期化する
	g_player.pos = D3DXVECTOR3(50.0,700.0, 0.0);  //現在の位置を初期化
	g_player.posold = D3DXVECTOR3(50.0, 700.0, 0.0);  //古い位置を初期化
	g_player.move = D3DXVECTOR3(0.0, 0.0, 0.0);      //移動量を初期化
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きを初期化する(z値を使用)
	g_player.bJump = false;							//ジャンプ見る
	g_moverotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //向きの移動用を初期化
	g_movefLengthPlayer = 0.0f; //対角線の移動量を初期化
	g_player.bUse = true;  //使っているかどうか
	g_player.nAnimCounter = 0; //アニメーションのカウンターを初期化
	g_player.fWidth = 20.0f; //プレイヤーの幅を初期化
	g_player.fHeight = 50.0f; //プレイヤーの高さを初期化
	g_player.nLife = 3; //プレイヤーの体力を初期化
	g_player.nCounterState = 300;  //状態管理のカウンターを初期化
	g_player.state = PLAYERSTATE_NORMAL;  //プレイヤーの状態を初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, 0.0f);
	
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

}

//======================
//プレイヤーの終了処理
//======================
void UninitPlayer(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//==============================
//プレイヤーの更新処理
//==============================
void UpdatePlayer(void)
{
	g_player.posold = g_player.pos; //前回の位置を記録

	Enemy *pEnemy = GetEnemy();

	PATTACK * pPattack = GetPattack();

	int nCntEnemy;

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//壁の当たり判定
	if (g_player.pos.x > 1257)
	{
		g_player.pos.x = 1257;
		g_player.move.x = 0;
	}

	else if (g_player.pos.x < 20)
	{
		g_player.pos.x = 20;
		g_player.move.x = 0;
	}

	if (g_player.pos.y > 725)
	{
		g_player.pos.y = 680;
		g_player.move.y = 0;
	}

	else if (g_player.pos.y <50)
	{
		g_player.pos.y = 50;
		g_player.move.y = 0;
	}

	g_player.nCounterAnim++;			//カウンターを加算

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardPress(DIK_A) == true || GetGameStickL_X_Press(BUTTON_STICK_LX, 0)  <= -1)
	{
		g_player.move.x -= 0.4f;
		/*g_player.nPatternAnim = 0;*/
		
			g_player.nAnimCounter = 1;

			//g_player.nCounterAnim = 0; //カウンターを初期化する

			if ((g_player.nCounterAnim % 10) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;		//パターンNO.を更新する

				/*PlaySound(SOUND_LABEL_RUN);*/
			}
	}

	else if (GetKeyboardPress(DIK_D) == true || GetGameStickL_X_Press(BUTTON_STICK_LX, 0) >= 1)
	{
		g_player.move.x += 0.4f;

		g_player.nAnimCounter = 0;

		if ((g_player.nCounterAnim % 10) == 0)
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;		//パターンNO.を更新する

			/*PlaySound(SOUND_LABEL_RUN);*/
		}
	}

	if (GetKeyboardPress(DIK_D) == true && GetKeyboardPress(DIK_A) == true)
	{
		g_player.move.x = 0.0f;
		g_player.nPatternAnim = 0;
	}

	else
	{
		if (g_player.nPatternAnim != 0)
		{
			if ((g_player.nCounterAnim % 8) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;		//パターンNO.を更新する
			}
		}
	}

	if (g_player.nAnimCounter == 0)
	{//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_player.nPatternAnim) * 0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f + (g_player.nPatternAnim) * 0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_player.nPatternAnim) * 0.25f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f + (g_player.nPatternAnim) * 0.25f, 0.5f);
		
			//攻撃処理
			if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
			{
				pPattack->bUse = true;
				g_player.bUse = false;

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (g_player.pos.x - PLAYER_ATTACKSPACE >= (pEnemy->pos.x - ENEMY_DAMAGESPACE) - ((g_player.pos.x - (g_player.pos.x - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.x + PLAYER_ATTACKSPACE <= (pEnemy->pos.x + ENEMY_DAMAGESPACE) + ((g_player.pos.x - (g_player.pos.x - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.y - PLAYER_ATTACKSPACE >= (pEnemy->pos.y - ENEMY_DAMAGESPACE) - ((g_player.pos.y - (g_player.pos.y - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.y + PLAYER_ATTACKSPACE <= (pEnemy->pos.y + ENEMY_DAMAGESPACE) + ((g_player.pos.y - (g_player.pos.y - PLAYER_ATTACKSPACE)) * 2))
					{

						if (pEnemy->bUse == true)
						{
							HitEnemy(nCntEnemy, 1);
							PlaySound(SOUND_LABEL_HIT);
							PlaySound(SOUND_LABEL_ENEMYDEATH);
						}
					}
				}
			}

			if (pPattack->bUse == true)
			{
				//右側に攻撃アニメーション
				RightPattack();


				//総パターン数を超えた
				if (pPattack->nPatternAnim == 3)
				{
					pPattack->nPatternAnim = 0;
					pPattack->nCounterAnim = 0;

					pPattack->bUse = false;  //使用していない状態にする
					g_player.bUse = true;      //プレイヤーを使用している状態にする
				}
			}

		}

		else if (g_player.nAnimCounter == 1)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_player.nPatternAnim) * 0.25f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.25f + (g_player.nPatternAnim) * 0.25f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_player.nPatternAnim) * 0.25f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f + (g_player.nPatternAnim) * 0.25f, 1.0f);

			//攻撃処理
			if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
			{
				pPattack->bUse = true;
				g_player.bUse = false;

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (g_player.pos.x - PLAYER_ATTACKSPACE >= (pEnemy->pos.x - ENEMY_DAMAGESPACE) - ((g_player.pos.x - (g_player.pos.x - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.x + PLAYER_ATTACKSPACE <= (pEnemy->pos.x + ENEMY_DAMAGESPACE) + ((g_player.pos.x - (g_player.pos.x - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.y - PLAYER_ATTACKSPACE >= (pEnemy->pos.y - ENEMY_DAMAGESPACE) - ((g_player.pos.y - (g_player.pos.y - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.y + PLAYER_ATTACKSPACE <= (pEnemy->pos.y + ENEMY_DAMAGESPACE) + ((g_player.pos.y - (g_player.pos.y - PLAYER_ATTACKSPACE)) * 2))
					{
						if (pEnemy->bUse == true)
						{
							HitEnemy(nCntEnemy, 1);
							PlaySound(SOUND_LABEL_HIT);
							PlaySound(SOUND_LABEL_ENEMYDEATH);
						}
					}
				}
			}

			if (pPattack->bUse == true)
			{
				//左側に攻撃
				LeftPattack();

				//総パターン数を超えた
				if (pPattack->nPatternAnim == 3)
				{
					pPattack->nPatternAnim = 0;
					pPattack->nCounterAnim = 0;

					pPattack->bUse = false;  //使用していない状態にする
					g_player.bUse = true; //プレイヤーの描画をする
				}
			}

		}

	

	//ジャンプ処理
	if (GetKeyboardTrigger(DIK_J) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
	{
		if (g_player.bJump == false)
		{
			g_player.bJump = true;

			g_player.move.y -= PLAYER_JUNP;
		}
	}

	//重力処理
	g_player.move.y += Press_PLAYER;

	//位置情報を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//移動量を更新
	g_player.move.x += (0.0f - g_player.move.x) * 0.1f;

	//ブロックとの当たり判定
	if (colisionBlock(&g_player.pos, &g_player.posold, &g_player.move,g_player.fWidth - PLAYER_WIDTH,g_player.fHeight - PLAYER_HEIGHT, g_player.bJump) == true)
	{
		g_player.bJump = false;  //着地状態にする
	}
	else
	{
		g_player.bJump = true;  //着地状態にする
	}

	if (g_player.pos.y >= 725.0f)
	{
		g_player.bJump = false;
		g_player.move.y = 0.0f;
		g_player.pos.y = 725.0f;
	}

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, 0.0f);

	CollisionPlayer();

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		break;

	case PLAYERSTATE_DAMAGE:

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_player.state = PLAYERSTATE_MUTEKI;

		break;

	case PLAYERSTATE_DEATH:

		g_player.bUse = false;

		break;

	case PLAYERSTATE_MUTEKI:

			g_player.nCounterState--;

			if (g_player.nCounterState <= 0)
			{
				g_player.state = PLAYERSTATE_NORMAL;
			}

			break;

	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//======================
//プレイヤーの描画処理
//======================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_player.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(NULL, g_pTexturePlayer);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類
	}
}

//========================
//プレイヤーのヒット処理
//========================
void HitPlayer(int nDamage)
{

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);


	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{
		g_player.bUse = false;

		g_player.state = PLAYERSTATE_DEATH;
		g_player.bDisp = false;

		//ゲーム状態の設定
		SetGameState(GAMESTATE_GAMEOVER, 120);
	}

	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;

		g_player.nCounterState = 60;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

}

//======================
//プレイヤーの当たり判定
//======================
void CollisionPlayer(void)
{
	Enemy *pEnemy = GetEnemy();
	int nCntEnemy;

	if (g_player.bUse == true)
	{//	プレイヤーが使用されている

		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{//敵が使用されている

			if (pEnemy->bUse == true && g_player.state == PLAYERSTATE_NORMAL)
			{

				if (g_player.pos.x - PLAYER_HITSPACEX >= (pEnemy->pos.x - ENEMY_HITSPACE) - ((g_player.pos.x - (g_player.pos.x - PLAYER_HITSPACEX)) * 2)
					&& g_player.pos.x + PLAYER_HITSPACEX <= (pEnemy->pos.x + ENEMY_HITSPACE) + ((g_player.pos.x - (g_player.pos.x - PLAYER_HITSPACEX)) * 2)
					&& g_player.pos.y - PLAYER_HITSPACEY >= (pEnemy->pos.y - ENEMY_HITSPACE) - ((g_player.pos.y - (g_player.pos.y - PLAYER_HITSPACEY)) * 2)
					&& g_player.pos.y + PLAYER_HITSPACEY <= (pEnemy->pos.y + ENEMY_HITSPACE) + ((g_player.pos.y - (g_player.pos.y - PLAYER_HITSPACEY)) * 2))
				{//プレイヤーと敵が当たった
				 //プレイヤーのヒット処理
  				 HitPlayer(1);

				 PlaySound(SOUND_LABEL_HIT);

 				PlaySound(SOUND_LABEL_DAMAGE);
				}
			}

			else
			{

			}
		}
	}
}

//============================
//プレイヤーを明け渡す
//============================
Player *GetPlayer(void)
{
	return &g_player;
}


