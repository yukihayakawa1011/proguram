//============================
//
//フェード処理(fade.h)
//Author:早川 友貴
//
//============================

#ifndef _FADE_H_   //このマクロ定義がされていなかったら
#define _FADE_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//フェードの状態
typedef enum
{
	FADE_NONE = 0,  //何もしていない
	FADE_IN,    //フェードイン
	FADE_OUT,	//フェードアウト状態
	FADE_MAX	
}FADE;

//プロトタイプ宣言
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);

#endif

