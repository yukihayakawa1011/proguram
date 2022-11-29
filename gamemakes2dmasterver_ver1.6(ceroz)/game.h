//============================
//
//ゲーム処理(game.h)
//Author:早川 友貴
//
//============================

#ifndef _GAME_H_   //このマクロ定義がされていなかったら
#define _GAME_H_   //2重インクルード防止のマクロを定義する

#include "main.h"
#include <stdio.h>

//ゲームの状態
typedef enum
{
	GAMESTATE_NONE = 0, //何もしていない状態
	GAMESTATE_NORMAL,	//通常状態(ゲーム進行)
	GAMESTATE_GAMEOVER, //ゲームオーバー
	GAMESTATE_END,		//終了状態
	GAMESTATE_MAX,
}GAMESTATE;

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state, int nCounter);
//void SetEnablePause(bool bPause);
//GAMESTATE GetGameState(void);
//bool GetPause(void);
void LoadMap(void);

#endif
