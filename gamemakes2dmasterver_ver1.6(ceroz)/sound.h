//=============================================================================
//
// サウンド処理 (sound.h)
// Author : 早川　友貴
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// タイトルBGM0
	SOUND_LABEL_BGM0015,		//チュートリアルBGM
	SOUND_LABEL_BGM001,			//ゲームBGM
	SOUND_LABEL_BGM002,			//ゲームオーバーBGM
	SOUND_LABEL_BGM003,			//リザルトBGM
	SOUND_LABEL_RANKING,		//ランキング画面BGM
	SOUND_LABEL_GAMEOVER,		//ゲームオーバーボイス
	SOUND_LABEL_DAMAGE,			//ダメージボイス
	SOUND_LABEL_ENEMYDEATH,		//敵の死亡ボイス
	SOUND_LABEL_HIT,			//攻撃ヒットサウンド
	SOUND_LABEL_KEY,			//鍵をゲットしたときの音
	SOUND_LABEL_ENTER,			//エンターキーを押したときの音
	SOUND_LABEL_RUN,			//走る音
	SOUND_LABEL_WINDOW,			//窓ガラスの割れる音
	SOUND_LABEL_TIMEUP,			//時間切れになったときのボイス
	SOUND_LABEL_MAX
	
	
	
	
	
	
	
	
	
	
	
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
