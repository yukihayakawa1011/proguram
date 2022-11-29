//============================
//
//���͏���(input.h)
//Author:���� �F�M
//
//============================

#ifndef _INPUT_H_   //���̃}�N����`������Ă��Ȃ�������
#define _INPUT_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include <Xinput.h>

#pragma comment(lib,"xinput.lib")

//�R���g���[���[�̃{�^�����`
typedef enum
{
	BUTTON_UP = 0, //��\���{�^��
	BUTTON_DOWN,   //���\���{�^��
	BUTTON_LEFT,   //���\���{�^��
	BUTTON_RIGHT,  //�E�\���{�^��
	BUTTON_START,  //�X�^�[�g�{�^��
	BUTTON_BACK,   //�o�b�N�{�^��
	BUTTON_LEFT_STICK_PUSH, //���X�e�B�b�N��������
	BUTTON_RIGHT_STICK_PUSH, //�E�X�e�B�b�N��������
	BUTTON_LB,  //LB�{�^��
	BUTTON_RB,  //RB�{�^��
	BUTTON_LT,  //LT�{�^��
	BUTTON_RT,  //RT�{�^��
	BUTTON_A,   //A�{�^��
	BUTTON_B,   //B�{�^��
	BUTTON_X,   //X�{�^��
	BUTTON_Y,   //Y�{�^��
	BUTTON_STICK_LX,  //���X�e�B�b�N��X
	BUTTON_STICK_LY, //���X�e�B�b�N��Y
	BUTTON_STICK_RX,  //�E�X�e�B�b�N��X
	BUTTON_STICK_RY,
	BUTTON_MAX
}JOYKEY;

//�v���g�^�C�v�錾(�L�[�{�[�h�E�Q�[���p�b�h)
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
HRESULT InitGamepad(void);

//�L�[�{�[�h�̊֐�
void UninitKeyboard(void);
void UpdateKeyboard(void);
void UninitGamepad(void);
void UpdateGamepad(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);

//�Q�[���p�b�h�̊֐�
bool GetGamepadPress(JOYKEY nKey,int nPlayer);
bool GetGamepadTrigger(JOYKEY nKey, int nPlayer);
bool GetGamepadRelease(JOYKEY nKey, int nPlayer);

//���X�e�B�b�N�̊֐�
SHORT GetGameStickL_X_Press(JOYKEY nKey, int nPlayer);
SHORT GetGameStickL_Y_Press(JOYKEY nKey, int nPlayer);

SHORT GetGameStickL_X_Trigger(JOYKEY nKey, int nPlayer);
SHORT GetGameStickL_Y_Trigger(JOYKEY nKey, int nPlayer);

SHORT GetGameStickL_X_Release(JOYKEY nKey, int nPlayer);
SHORT GetGameStickL_Y_Release(JOYKEY nKey, int nPlayer);

//�E�X�e�B�b�N�̊֐�
SHORT GetGameStickR_X_Press(JOYKEY nKey, int nPlayer);
SHORT GetGameStickR_Y_Press(JOYKEY nKey, int nPlayer);

SHORT GetGameStickR_X_Trigger(JOYKEY nKey, int nPlayer);
SHORT GetGameStickR_Y_Trigger(JOYKEY nKey, int nPlayer);

SHORT GetGameStickR_X_Release(JOYKEY nKey, int nPlayer);
SHORT GetGameStickR_Y_Release(JOYKEY nKey, int nPlayer);






#endif 

