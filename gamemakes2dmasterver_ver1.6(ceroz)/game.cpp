//============================
//
//ゲーム処理(game.cpp)
//Author:早川 友貴
//
//============================
#include "main.h"
#include "game.h"
#include "bg.h"
#include "player.h"
#include"block.h"
#include "enemy.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "black.h"
#include "goal.h"
#include "time.h"
//#include "effect.h"
#include "life.h"
#include "key.h"
#include "edit.h"
#include "pattack.h"
//#include "pause.h"
//#include "particle.h"

//マクロ
#define BLOCK_X (200.0f)
#define BLOCK_Y (20.0f)
#define BLOCK_LOAD (56 * 3)
#define NUM_KEY (3)

//グローバル変数宣言
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
//bool g_bPause = false;			//ポーズ状態のON/OFF
bool g_Fade = false;
GOAL g_nGoal;
FILE *pFile;
float g_aBlockMap[BLOCK_LOAD];
int g_GetKey;

//======================
//ゲーム画面の初期化処理
//======================
void InitGame(void)
{
	int nCnt;

	//背景の初期化処理
	InitBg();

	//ゴールの初期化
	InitGoal();

	//プレイヤーの初期化
	InitPlayer();

	//ブロックの初期化
	InitBlock();

	//鍵の初期化
	InitKey();

	//攻撃の初期化
	InitPattack();

	//敵の初期化
	InitEnemy();
	SetEnemy(D3DXVECTOR3(500.0f, 690.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(600.0f, 180.0f, 0.0f), 1);

	//暗闇の初期化
	InitBlack();

#ifdef _DEBUG

	//エディットの初期化
	InitEdit();

#endif

	//設置ブロック
	//床ブロック
	//天井ブロック
	LoadMap();

	for (nCnt = 0; nCnt < BLOCK_LOAD; nCnt += 3)
	{//画面に読み込んできたブロックを設置する
		SetBlock(D3DXVECTOR3(g_aBlockMap[nCnt], g_aBlockMap[nCnt + 1], g_aBlockMap[nCnt + 2]), BLOCK_X, BLOCK_Y);
	}

	//タイムの初期化処理
	InitTime();

	////エフェクトの初期化処理
	//InitEffect();

	////パーティクルの初期化処理
	//InitParticle();

	//ライフの初期化処理
	InitLife();

	////ポーズの初期化
	//InitPause();

	g_gameState = GAMESTATE_NORMAL;  //通常状態に設定
	g_nCounterGameState = 0;
	/*g_bPause = false;*/

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM001);
}

//===========================
//ゲーム画面の終了処理
//===========================
void UninitGame(void)
{

	//サウンドの停止
	StopSound();

	//背景の終了処理
	UninitBg();

	//ゴールの終了処理
	UninitGoal();

	//プレイヤーの終了処理
	UninitPlayer();

	//ブロックの終了処理
	UninitBlock();

	//鍵の終了処理
	UninitKey();

	//攻撃の終了処理
	UninitPattack();

	//敵の終了処理
	UninitEnemy();

	//暗闇の終了処理
	UninitBlack();

#ifdef _DEBUG

	//エディットの終了処理
	UninitEdit();

#endif

	//タイムの終了処理
	UninitTime();

	////エフェクトの終了処理
	//UninitEffect();

	////パーティクルの終了処理
	//UninitParticle();

	//ライフの終了処理
	UninitLife();

	////ポーズの終了
	//UninitPause();

}

//===========================
//ゲームの更新処理
//===========================
void UpdateGame(void)
{
	Player *pPlayer = GetPlayer();
	g_nGoal = GetGoal();
	g_GetKey = GetKey();

	//if (GetKeyboardTrigger(DIK_P) == true)
	//{//Pキーが押されたときにポーズ
	//	g_bPause = g_bPause ? false : true;
	//}
	//	/*if (g_bPause == true)*/
	//	/*{*///Pキーが押されていない時
	//		ポーズ画面の更新処理

			/*UpdatePause();*/
	/*	}*/

		/*else if (g_bPause == false)
		{*/
			//背景の更新処理
			UpdateBg();

			//ゴールの更新処理
			UpdateGoal();

			//プレイヤーの更新処理
			UpdatePlayer();

			//ブロックの更新処理
			UpdateBlock();

			//鍵の更新処理
			UpdateKey();

			//攻撃の更新処理
			UpdatePattack();

			//敵の更新処理
			UpdateEnemy();

			//暗闇の更新処理
			UpdateBlack();

#ifdef _DEBUG


			//エディットの更新処理
			UpdateEdit();

#endif

			if (g_gameState != GAMESTATE_NONE)
			{
				//タイムの更新処理
				UpdateTime();
			}

			////エフェクトの更新処理
			//UpdateEffect();

			////パーティクルの更新処理
			//UpdateParticle();

			//ライフの更新処理
			UpdateLife();

			////ポーズメニューを初期化
			//ResetPause();
	/*	}*/

	//if ( pPlayer->bUse == false)
	//{
	//	//モード設定(リザルト画面に移行)
	//	//SetMode(MODE_RESULT);
	//}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:  //通常状態

#ifdef _DEBUG

		if (GetKeyboardTrigger(DIK_F7) == true || GetGamepadTrigger(BUTTON_START, 0) == true)
		{
			g_gameState = GAMESTATE_END;
		}

#endif
		if (g_nGoal.pos.x - 5.0f <= pPlayer->pos.x && g_nGoal.pos.y - 30.0f <= pPlayer->pos.y && g_GetKey == 0)
		{
			g_gameState = GAMESTATE_END;
		}

		break;

	case GAMESTATE_GAMEOVER:

		g_nCounterGameState--;

			if (g_nCounterGameState <= 0)
			{
				g_gameState = GAMESTATE_NONE;

				/*g_bPause = true;*/

				//モード設定
				SetFade(MODE_GAMEOVER);
			}

		break;

	case GAMESTATE_END:  //終了

		g_nCounterGameState--;
		
		if (g_nCounterGameState <= 0)
		{
			g_gameState = GAMESTATE_NONE;

			/*g_bPause = true;*/

			//モード設定
			SetFade(MODE_RESULT);
		}

		break;

	}
}

//===========================
//ゲーム画面の描画処理
//===========================
void DrawGame(void)
{
   /* FADE g_Fade = GetFade();*/

	    //背景の描画処理
		DrawBg();

		//ブロックの描画処理
		DrawBlock();

		//鍵の描画処理
		DrawKey();

		//敵の描画処理
		DrawEnemy();

		/*暗闇の描画処理*/
		DrawBlack();

		if (g_GetKey == 0)
		{
			//ゴールの描画処理
			DrawGoal();
		}

		//プレイヤーの描画処理
		DrawPlayer();

		//攻撃の描画処理
		DrawPattack();

		//タイムの描画処理
		DrawTime();

		////エフェクトの描画処理
		//DrawEffect();

		////パーティクルの描画処理
		//DrawParticle();

		//ライフの描画処理
		DrawLife();

		//if (g_bPause == true && g_Fade == FADE_NONE)
		//{
		//	//ポーズの描画
		//	DrawPause();
		//}

#ifdef _DEBUG

		//FPSの表示
		DrawFPS();

		//エディットの描画処理
		DrawEdit();

		//敵の数を表示
		DrawEnemyCnt();

#endif

}

//=======================
//ゲームの状態の設定
//=======================
void SetGameState(GAMESTATE state, int nCounter)
{
	g_gameState = state;

	g_nCounterGameState = nCounter;
}

//===================================
//ポーズ状態の取得
//===================================
//void SetEnablePause(bool bPause)
//{
//	g_bPause = bPause;
//}

////=====================
////ゲーム状態の取得
////=====================
//GAMESTATE GetGameState(void)
//{
//	return g_gameState;
//}

//========================
//ポーズ状態の取得
//========================
//bool GetPause(void)
//{
//	return g_bPause;
//}

//=======================
//マップのロード処理
//=======================
void LoadMap(void)
{
	int nCnt;

	//マップの情報を外部ファイルから読み込む
	pFile = fopen("map.txt", "r");

	

	if (pFile != NULL)
	{//ファイルを読み込めた場合
	 //ファイルから文字を列で読み込む

		for (nCnt = 0; nCnt < BLOCK_LOAD; nCnt++)
		{
			fscanf(pFile, "%f", &g_aBlockMap[nCnt]);
		}
		//ファイルを閉じる
		fclose(pFile);
	}
}
