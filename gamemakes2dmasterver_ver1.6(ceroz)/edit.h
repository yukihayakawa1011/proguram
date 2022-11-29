//============================
//
//エディット処理(edit.h)
//Author:早川 友貴
//
//============================

#ifndef _EDIT_H_   //このマクロ定義がされていなかったら
#define _EDIT_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//プロトタイプ宣言
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void DelEdit(void);

#endif