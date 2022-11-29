//============================
//
//攻撃処理(pattack.h)
//Author:早川 友貴
//
//============================

#ifndef _PATTACK_H_   //このマクロ定義がされていなかったら
#define _PATTACK_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//攻撃構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;  //位置
	D3DXCOLOR col;    //色
	int nCounterAnim;  //アニメーションカウンター
	int nPatternAnim;  //アニメーションパターンNo.
	bool bUse;         //使用しているかどうか
}PATTACK;

//プロトタイプ宣言
void InitPattack(void);
void UninitPattack(void);
void UpdatePattack(void);
void DrawPattack(void);
void SetPattack(D3DXVECTOR3 pos);
PATTACK *GetPattack(void);
void RightPattack(void);
void LeftPattack(void);

#endif
