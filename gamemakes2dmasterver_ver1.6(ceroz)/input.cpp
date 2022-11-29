//============================
//
//���͏���(input.cpp)
//Author:���� �F�M
//
//============================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256)  //�L�[�̍ő吔
#define MAX_PLAYER  (4) //�L�[�̍ő吔

//�O���[�o���ϐ��錾
LPDIRECTINPUT8 g_pInput = NULL;  //DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;  //���̓f�o�C�X�i�L�[�{�[�h)�ւ̃|�C���^

BYTE g_aKeyState[NUM_KEY_MAX];  //�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX]; //�L�[�{�[�h�̃g���K�[���
BYTE g_aKeyStateRelease[NUM_KEY_MAX]; //�L�[�{�[�h�̃����[�X���

XINPUT_STATE g_aGamepadState[NUM_KEY_MAX]; //�p�b�h�̃v���X���
XINPUT_STATE g_aGamepadStateTrigger[NUM_KEY_MAX]; //�p�b�h�̃g���K�[���
XINPUT_STATE g_aGamepadStateRelease[NUM_KEY_MAX]; //�p�b�h�̃����[�X���

//======================
//�L�[�{�[�h�̏���������
//======================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//============================
//�Q�[���p�b�h�̏�����
//============================
HRESULT InitGamepad(void)
{
	int nCnt;

	//�Q�[���p�b�h�ݒ��L���ɂ���
	XInputEnable(true);
	
	//�������̏��̏�����
	for (nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		memset(&g_aGamepadState[nCnt], 0, sizeof(XINPUT_STATE)); //�v���X���

		memset(&g_aGamepadStateTrigger[nCnt], 0, sizeof(XINPUT_STATE)); //�g���K�[���

		memset(&g_aGamepadStateRelease[nCnt], 0, sizeof(XINPUT_STATE)); //�����[�X���
	}

	return S_OK;
}

//======================
//�L�[�{�[�h�I������
//======================
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();  //�L�[�{�[�h�̃A�N�Z�X�������

		g_pDevKeyboard->Release();   

		g_pDevKeyboard = NULL;  
	}
}

//======================
//�L�[�{�[�h�X�V����
//======================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];  //�L�[�{�[�h�̓��͏��

	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //�L�[�{�[�h�̃g���K�[����ۑ�

			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) &~ aKeyState[nCntKey]; //�L�[�{�[�h�̃����[�X����ۑ�
			
			g_aKeyState[nCntKey] = aKeyState[nCntKey];  //�L�[�{�[�h�̃v���X����ۑ�
		}
	}

	else
	{
		g_pDevKeyboard->Acquire();   //�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

}

//======================
//�Q�[���p�b�h�̏I��
//======================
void UninitGamepad(void)
{
	//�Q�[���p�b�h�ݒ��L���ɂ���
	XInputEnable(false);
}

//======================
//�Q�[���p�b�h�̍X�V
//======================
void UpdateGamepad(void)
{
	int nCnt;

	XINPUT_STATE aGamepadState[NUM_KEY_MAX];

	for (nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		//���̓f�o�C�X����f�[�^���擾
		if (XInputGetState(nCnt, &aGamepadState[nCnt]) == ERROR_SUCCESS)
		{
			g_aGamepadStateTrigger[nCnt].Gamepad.wButtons = (g_aGamepadState[nCnt].Gamepad.wButtons ^ aGamepadState[nCnt].Gamepad.wButtons)
				& aGamepadState[nCnt].Gamepad.wButtons; //�g���K�[�̃f�[�^���擾

			g_aGamepadStateRelease[nCnt].Gamepad.wButtons = (g_aGamepadState[nCnt].Gamepad.wButtons ^ aGamepadState[nCnt].Gamepad.wButtons) 
				&~aGamepadState[nCnt].Gamepad.wButtons; //�����[�X�̃f�[�^���擾

			g_aGamepadState[nCnt] = aGamepadState[nCnt];  //�v���X�̃f�[�^���擾
		}
	}
}

//�L�[�{�[�h�̃v���X�����擾
	bool GetKeyboardPress(int nKey)
	{
		return (g_aKeyState[nKey] & 0x80) ? true : false;
	}

//�L�[�{�[�h�̃g���K�[�����擾
	bool GetKeyboardTrigger(int nKey)
	{
		return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
	}

//�L�[�{�[�h�̃����[�X�����擾
	bool GetKeyboardRelease(int nKey)
	{
		return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
	}

	//�Q�[���p�b�h�̃v���X�����擾
	bool GetGamepadPress(JOYKEY nKey, int nPlayer)
	{
		return(g_aGamepadState[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true: false;
	}

	//�Q�[���p�b�h�̃g���K�[�����擾
	bool GetGamepadTrigger(JOYKEY nKey, int nPlayer)
	{
		return(g_aGamepadStateTrigger[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true : false;
	}

	//�Q�[���p�b�h�̃����[�X�����擾
	bool GetGamepadRelease(JOYKEY nKey, int nPlayer)
	{
		return(g_aGamepadStateRelease[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true : false;
	}

	//���X�e�B�b�N�̊֐�(X���̃v���X)
	SHORT GetGameStickL_X_Press(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadState[nPlayer].Gamepad.sThumbLX;
	}

	//���X�e�B�b�N�̊֐�(Y���̃v���X)
	SHORT GetGameStickL_Y_Press(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadState[nPlayer].Gamepad.sThumbLY;
	}

	//���X�e�B�b�N�̊֐�(X���̃g���K�[)
	SHORT GetGameStickL_X_Trigger(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateTrigger[nPlayer].Gamepad.sThumbLX;
	}

	//���X�e�B�b�N�̊֐�(Y���̃g���K�[)
	SHORT GetGameStickL_Y_Trigger(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateTrigger[nPlayer].Gamepad.sThumbLY;
	}

	//���X�e�B�b�N�̊֐�(X���̃����[�X)
	SHORT GetGameStickL_X_Release(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateRelease[nPlayer].Gamepad.sThumbLX;
	}

	//���X�e�B�b�N�̊֐�(Y���̃����[�X)
	SHORT GetGameStickL_Y_Release(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateRelease[nPlayer].Gamepad.sThumbLY;
	}

	//�E�X�e�B�b�N�̊֐�(X���̃v���X)
	SHORT GetGameStickR_X_Press(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadState[nPlayer].Gamepad.sThumbRX;
	}
	//�E�X�e�B�b�N�̊֐�(Y���̃v���X)
	SHORT GetGameStickR_Y_Press(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadState[nPlayer].Gamepad.sThumbRY;
	}

	//�E�X�e�B�b�N�̊֐�(X���̃g���K�[)
	SHORT GetGameStickR_X_Trigger(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateTrigger[nPlayer].Gamepad.sThumbRX;
	}

	//�E�X�e�B�b�N�̊֐�(Y���̃g���K�[)
	SHORT GetGameStickR_Y_Trigger(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateTrigger[nPlayer].Gamepad.sThumbRY;
	}

	//�E�X�e�B�b�N�̊֐�(X���̃����[�X)
	SHORT GetGameStickR_X_Release(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateRelease[nPlayer].Gamepad.sThumbRX;
	}

	//�E�X�e�B�b�N�̊֐�(Y���̃����[�X)
	SHORT GetGameStickR_Y_Release(JOYKEY nKey, int nPlayer)
	{
		return g_aGamepadStateRelease[nPlayer].Gamepad.sThumbRY;
	}