//============================
//
//チュートリアル処理(tutorial.h)
//Author:早川 友貴
//
//============================

#ifndef _TUTORIAL_H_   //このマクロ定義がされていなかったら
#define _TUTORIAL_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void ColEntTutorial(int nCnt);
void ColBackTutorial(int nCnt);

#endif
