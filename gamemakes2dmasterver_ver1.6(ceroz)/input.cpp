//============================
//
//入力処理(input.cpp)
//Author:早川 友貴
//
//============================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX (256)  //キーの最大数
#define MAX_PLAYER  (4) //キーの最大数

//グローバル変数宣言
LPDIRECTINPUT8 g_pInput = NULL;  //DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;  //入力デバイス（キーボード)へのポインタ

BYTE g_aKeyState[NUM_KEY_MAX];  //キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX]; //キーボードのトリガー情報
BYTE g_aKeyStateRelease[NUM_KEY_MAX]; //キーボードのリリース情報

XINPUT_STATE g_aGamepadState[NUM_KEY_MAX]; //パッドのプレス情報
XINPUT_STATE g_aGamepadStateTrigger[NUM_KEY_MAX]; //パッドのトリガー情報
XINPUT_STATE g_aGamepadStateRelease[NUM_KEY_MAX]; //パッドのリリース情報

//======================
//キーボードの初期化処理
//======================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//============================
//ゲームパッドの初期化
//============================
HRESULT InitGamepad(void)
{
	int nCnt;

	//ゲームパッド設定を有効にする
	XInputEnable(true);
	
	//メモリの情報の初期化
	for (nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		memset(&g_aGamepadState[nCnt], 0, sizeof(XINPUT_STATE)); //プレス情報

		memset(&g_aGamepadStateTrigger[nCnt], 0, sizeof(XINPUT_STATE)); //トリガー情報

		memset(&g_aGamepadStateRelease[nCnt], 0, sizeof(XINPUT_STATE)); //リリース情報
	}

	return S_OK;
}

//======================
//キーボード終了処理
//======================
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();  //キーボードのアクセス権を放棄

		g_pDevKeyboard->Release();   

		g_pDevKeyboard = NULL;  
	}
}

//======================
//キーボード更新処理
//======================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];  //キーボードの入力情報

	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //キーボードのトリガー情報を保存

			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) &~ aKeyState[nCntKey]; //キーボードのリリース情報を保存
			
			g_aKeyState[nCntKey] = aKeyState[nCntKey];  //キーボードのプレス情報を保存
		}
	}

	else
	{
		g_pDevKeyboard->Acquire();   //キーボードへのアクセス権を獲得
	}

}

//======================
//ゲームパッドの終了
//======================
void UninitGamepad(void)
{
	//ゲームパッド設定を有効にする
	XInputEnable(false);
}

//======================
//ゲームパッドの更新
//======================
void UpdateGamepad(void)
{
	int nCnt;

	XINPUT_STATE aGamepadState[NUM_KEY_MAX];

	for (nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		//入力デバイスからデータを取得
		if (XInputGetState(nCnt, &aGamepadState[nCnt]) == ERROR_SUCCESS)
		{
			g_aGamepadStateTrigger[nCnt].Gamepad.wButtons = (g_aGamepadState[nCnt].Gamepad.wButtons ^ aGamepadState[nCnt].Gamepad.wButtons)
				& aGamepadState[nCnt].Gamepad.wButtons; //トリガーのデータを取得

			g_aGamepadStateRelease[nCnt].Gamepad.wButtons = (g_aGamepadState[nCnt].Gamepad.wButtons ^ aGamepadState[nCnt].Gamepad.wButtons) 
				&~aGamepadState[nCnt].Gamepad.wButtons; //リリースのデータを取得

			g_aGamepadState[nCnt] = aGamepadState[nCnt];  //プレスのデータを取得
		}
	}
}

//キーボードのプレス情報を取得
	bool GetKeyboardPress(int nKey)
	{
		return (g_aKeyState[nKey] & 0x80) ? true : false;
	}

//キーボードのトリガー情報を取得
	bool GetKeyboardTrigger(int nKey)
	{
		return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
	}

//キーボードのリリース情報を取得
	bool GetKeyboardRelease(int nKey)
	{
		return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
	}

	//ゲームパッドのプレス情報を取得
	bool GetGamepadPress(JOYKEY nKey, int nPlayer)
	{
		return(g_aGamepadState[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true: false;
	}

	//ゲームパッドのトリガー情報を取得
	bool GetGamepadTrigger(JOYKEY nKey, int nPlayer)
	{
		return(g_aGamepadStateTrigger[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true : false;
	}

	//ゲームパッドのリリース情報を取得
	bool GetGamepadRelease(JOYKEY nKey, int nPlayer)
	{
		return(g_aGamepadStateRelease[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true : false;
	}

	//左スティックの関数(X軸のプレス)
	SHORT GetGameStickL_X_Press(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadState[nPlayer].Gamepad.sThumbLX;
	}

	//左スティックの関数(Y軸のプレス)
	SHORT GetGameStickL_Y_Press(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadState[nPlayer].Gamepad.sThumbLY;
	}

	//左スティックの関数(X軸のトリガー)
	SHORT GetGameStickL_X_Trigger(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateTrigger[nPlayer].Gamepad.sThumbLX;
	}

	//左スティックの関数(Y軸のトリガー)
	SHORT GetGameStickL_Y_Trigger(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateTrigger[nPlayer].Gamepad.sThumbLY;
	}

	//左スティックの関数(X軸のリリース)
	SHORT GetGameStickL_X_Release(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateRelease[nPlayer].Gamepad.sThumbLX;
	}

	//左スティックの関数(Y軸のリリース)
	SHORT GetGameStickL_Y_Release(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateRelease[nPlayer].Gamepad.sThumbLY;
	}

	//右スティックの関数(X軸のプレス)
	SHORT GetGameStickR_X_Press(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadState[nPlayer].Gamepad.sThumbRX;
	}
	//右スティックの関数(Y軸のプレス)
	SHORT GetGameStickR_Y_Press(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadState[nPlayer].Gamepad.sThumbRY;
	}

	//右スティックの関数(X軸のトリガー)
	SHORT GetGameStickR_X_Trigger(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateTrigger[nPlayer].Gamepad.sThumbRX;
	}

	//右スティックの関数(Y軸のトリガー)
	SHORT GetGameStickR_Y_Trigger(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateTrigger[nPlayer].Gamepad.sThumbRY;
	}

	//右スティックの関数(X軸のリリース)
	SHORT GetGameStickR_X_Release(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateRelease[nPlayer].Gamepad.sThumbRX;
	}

	//右スティックの関数(Y軸のリリース)
	SHORT GetGameStickR_Y_Release(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateRelease[nPlayer].Gamepad.sThumbRY;
	}