//============================
//
//ブロックに関する処理(block.h)
//Author:早川 友貴
//
//============================

#ifndef _BLOCK_H_   //このマクロ定義がされていなかったら
#define _BLOCK_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define MAX_BLOCK   (128)   //敵の最大数

//ブロック構造体
typedef struct
{
	D3DXVECTOR3 pos;  //ブロックの位置
	float fWidth;	  //幅
	float fHeight;	  //高さ
	bool bUse;		  //使っているかどうか
}BLOCK;

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight);
bool colisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove , float fWidth, float fHeight, bool bJump);
BLOCK *GetBlock(void);

#endif
