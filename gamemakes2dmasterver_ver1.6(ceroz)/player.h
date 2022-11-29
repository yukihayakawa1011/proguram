//============================
//
//プレイヤーの処理(player.h)
//Author:早川 友貴
//
//============================

#ifndef _PLAYER_H_   //このマクロ定義がされていなかったら
#define _PLAYER_H_   //2重インクルード防止のマクロを定義する

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_NORMAL = 0,     //通常状態
	PLAYERSTATE_DAMAGE,     //ダメージ
	PLAYERSTATE_MUTEKI,		//無敵状態
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;  //現在の位置
	D3DXVECTOR3 posold; //古い位置
	D3DXVECTOR3 rot;  //向き
	D3DXVECTOR3 move;  //移動量
	int nCounterAnim; //アニメーションカウンター
	int nPatternAnim; //アニメーションパターン
	bool bJump;		  //ジャンプ中かどうか
	float fWidth;    //プレイヤー幅
	float fHeight;   //プレイヤー高さ
	int nLife;		  //体力
	bool bUse;   //使用しているかどうか
	int nAnimCounter;
	PLAYERSTATE state;  //プレイヤーの状態
	int nCounterState;	//状態管理カウンター
	bool bDisp;			//表示するかしないか
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
void CollisionPlayer(void);
Player *GetPlayer(void);

#endif
