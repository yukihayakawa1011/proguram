//============================
//
//ゴール処理(goal.h)
//Author:早川 友貴
//
//============================

#ifndef _GOAL_H_   //このマクロ定義がされていなかったら
#define _GOAL_H   //2重インクルード防止のマクロを定義する

#include "main.h"

//ゴール構造体
typedef struct
{
	D3DXVECTOR3 pos;
	bool bUse;
}GOAL;

//プロトタイプ宣言
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
GOAL GetGoal(void);

#endif