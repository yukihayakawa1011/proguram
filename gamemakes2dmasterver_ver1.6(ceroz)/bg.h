//============================
//
//背景処理(bg.h)
//Author:早川 友貴
//
//============================

#ifndef _BG_H_   //このマクロ定義がされていなかったら
#define _BG_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitBg(void);
void UninitBg(void);
void UpdateBg(void);
void DrawBg(void);

#endif
