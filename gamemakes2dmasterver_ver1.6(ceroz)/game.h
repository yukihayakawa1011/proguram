//============================
//
//�Q�[������(game.h)
//Author:���� �F�M
//
//============================

#ifndef _GAME_H_   //���̃}�N����`������Ă��Ȃ�������
#define _GAME_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include <stdio.h>

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE = 0, //�������Ă��Ȃ����
	GAMESTATE_NORMAL,	//�ʏ���(�Q�[���i�s)
	GAMESTATE_GAMEOVER, //�Q�[���I�[�o�[
	GAMESTATE_END,		//�I�����
	GAMESTATE_MAX,
}GAMESTATE;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state, int nCounter);
//void SetEnablePause(bool bPause);
//GAMESTATE GetGameState(void);
//bool GetPause(void);
void LoadMap(void);

#endif
