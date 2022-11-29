//===============================
//
//鍵処理(key.h)
//
//===============================
#ifndef _KET_H_   //このマクロ定義がされていなかったら
#define _KET_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

typedef struct
{
	bool bUse;
}KEYSTATE;

//プロトタイプ宣言
void InitKey(void);
void UninitKey(void);
void UpdateKey(void);
void DrawKey(void);
int GetKey(void);

#endif
