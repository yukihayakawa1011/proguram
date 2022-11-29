//============================
//
//ゲームオーバー処理(gameover.h)
//Author:早川 友貴
//
//============================

#ifndef _GAMEOVER_H_   //このマクロ定義がされていなかったら
#define _GAMEOVER_H   //2重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitGameover(void);
void UninitGameover(void);
void UpdateGameover(void);
void DrawGameover(void);

#endif
