//============================
//
//敵に関する処理X(enemy.h)
//Author:早川 友貴
//
//============================

#ifndef _ENEMY_H_   //このマクロ定義がされていなかったら
#define _ENEMY_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define MAX_ENEMY   (128)   //敵の最大数

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMEGE,
	ENEMYSTATE_MAX,
}ENEMYSTATE;

//敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;   //位置
	ENEMYSTATE state;  //状態
	//D3DXVECTOR3 rot;  //向き
	D3DXVECTOR3 move;  //移動量
	int nType;         //種類
	int nLife;		   //体力
	int nCounterState; //状態管理カウンター
	bool bUse;         //使用しているかどうか
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
Enemy *GetEnemy(void);
int ENEMY(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif