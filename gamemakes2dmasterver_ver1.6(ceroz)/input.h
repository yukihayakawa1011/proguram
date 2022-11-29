//============================
//
//入力処理(input.h)
//Author:早川 友貴
//
//============================

#ifndef _INPUT_H_   //このマクロ定義がされていなかったら
#define _INPUT_H_  //2重インクルード防止のマクロを定義する

#include "main.h"
#include <Xinput.h>

#pragma comment(lib,"xinput.lib")

//コントローラーのボタンを定義
typedef enum
{
	BUTTON_UP = 0, //上十字ボタン
	BUTTON_DOWN,   //下十字ボタン
	BUTTON_LEFT,   //左十字ボタン
	BUTTON_RIGHT,  //右十字ボタン
	BUTTON_START,  //スタートボタン
	BUTTON_BACK,   //バックボタン
	BUTTON_LEFT_STICK_PUSH, //左スティック押し込み
	BUTTON_RIGHT_STICK_PUSH, //右スティック押し込み
	BUTTON_LB,  //LBボタン
	BUTTON_RB,  //RBボタン
	BUTTON_LT,  //LTボタン
	BUTTON_RT,  //RTボタン
	BUTTON_A,   //Aボタン
	BUTTON_B,   //Bボタン
	BUTTON_X,   //Xボタン
	BUTTON_Y,   //Yボタン
	BUTTON_STICK_LX,  //左スティックのX
	BUTTON_STICK_LY, //左スティックのY
	BUTTON_STICK_RX,  //右スティックのX
	BUTTON_STICK_RY,
	BUTTON_MAX
}JOYKEY;

//プロトタイプ宣言(キーボード・ゲームパッド)
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
HRESULT InitGamepad(void);

//キーボードの関数
void UninitKeyboard(void);
void UpdateKeyboard(void);
void UninitGamepad(void);
void UpdateGamepad(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);

//ゲームパッドの関数
bool GetGamepadPress(JOYKEY nKey,int nPlayer);
bool GetGamepadTrigger(JOYKEY nKey, int nPlayer);
bool GetGamepadRelease(JOYKEY nKey, int nPlayer);

//左スティックの関数
SHORT GetGameStickL_X_Press(JOYKEY nKey, int nPlayer);
SHORT GetGameStickL_Y_Press(JOYKEY nKey, int nPlayer);

SHORT GetGameStickL_X_Trigger(JOYKEY nKey, int nPlayer);
SHORT GetGameStickL_Y_Trigger(JOYKEY nKey, int nPlayer);

SHORT GetGameStickL_X_Release(JOYKEY nKey, int nPlayer);
SHORT GetGameStickL_Y_Release(JOYKEY nKey, int nPlayer);

//右スティックの関数
SHORT GetGameStickR_X_Press(JOYKEY nKey, int nPlayer);
SHORT GetGameStickR_Y_Press(JOYKEY nKey, int nPlayer);

SHORT GetGameStickR_X_Trigger(JOYKEY nKey, int nPlayer);
SHORT GetGameStickR_Y_Trigger(JOYKEY nKey, int nPlayer);

SHORT GetGameStickR_X_Release(JOYKEY nKey, int nPlayer);
SHORT GetGameStickR_Y_Release(JOYKEY nKey, int nPlayer);






#endif 

