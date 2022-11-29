//============================
//
//�Q�[������(game.cpp)
//Author:���� �F�M
//
//============================
#include "main.h"
#include "game.h"
#include "bg.h"
#include "player.h"
#include"block.h"
#include "enemy.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "black.h"
#include "goal.h"
#include "time.h"
//#include "effect.h"
#include "life.h"
#include "key.h"
#include "edit.h"
#include "pattack.h"
//#include "pause.h"
//#include "particle.h"

//�}�N��
#define BLOCK_X (200.0f)
#define BLOCK_Y (20.0f)
#define BLOCK_LOAD (56 * 3)
#define NUM_KEY (3)

//�O���[�o���ϐ��錾
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
//bool g_bPause = false;			//�|�[�Y��Ԃ�ON/OFF
bool g_Fade = false;
GOAL g_nGoal;
FILE *pFile;
float g_aBlockMap[BLOCK_LOAD];
int g_GetKey;

//======================
//�Q�[����ʂ̏���������
//======================
void InitGame(void)
{
	int nCnt;

	//�w�i�̏���������
	InitBg();

	//�S�[���̏�����
	InitGoal();

	//�v���C���[�̏�����
	InitPlayer();

	//�u���b�N�̏�����
	InitBlock();

	//���̏�����
	InitKey();

	//�U���̏�����
	InitPattack();

	//�G�̏�����
	InitEnemy();
	SetEnemy(D3DXVECTOR3(500.0f, 690.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(600.0f, 180.0f, 0.0f), 1);

	//�Èł̏�����
	InitBlack();

#ifdef _DEBUG

	//�G�f�B�b�g�̏�����
	InitEdit();

#endif

	//�ݒu�u���b�N
	//���u���b�N
	//�V��u���b�N
	LoadMap();

	for (nCnt = 0; nCnt < BLOCK_LOAD; nCnt += 3)
	{//��ʂɓǂݍ���ł����u���b�N��ݒu����
		SetBlock(D3DXVECTOR3(g_aBlockMap[nCnt], g_aBlockMap[nCnt + 1], g_aBlockMap[nCnt + 2]), BLOCK_X, BLOCK_Y);
	}

	//�^�C���̏���������
	InitTime();

	////�G�t�F�N�g�̏���������
	//InitEffect();

	////�p�[�e�B�N���̏���������
	//InitParticle();

	//���C�t�̏���������
	InitLife();

	////�|�[�Y�̏�����
	//InitPause();

	g_gameState = GAMESTATE_NORMAL;  //�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
	/*g_bPause = false;*/

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM001);
}

//===========================
//�Q�[����ʂ̏I������
//===========================
void UninitGame(void)
{

	//�T�E���h�̒�~
	StopSound();

	//�w�i�̏I������
	UninitBg();

	//�S�[���̏I������
	UninitGoal();

	//�v���C���[�̏I������
	UninitPlayer();

	//�u���b�N�̏I������
	UninitBlock();

	//���̏I������
	UninitKey();

	//�U���̏I������
	UninitPattack();

	//�G�̏I������
	UninitEnemy();

	//�Èł̏I������
	UninitBlack();

#ifdef _DEBUG

	//�G�f�B�b�g�̏I������
	UninitEdit();

#endif

	//�^�C���̏I������
	UninitTime();

	////�G�t�F�N�g�̏I������
	//UninitEffect();

	////�p�[�e�B�N���̏I������
	//UninitParticle();

	//���C�t�̏I������
	UninitLife();

	////�|�[�Y�̏I��
	//UninitPause();

}

//===========================
//�Q�[���̍X�V����
//===========================
void UpdateGame(void)
{
	Player *pPlayer = GetPlayer();
	g_nGoal = GetGoal();
	g_GetKey = GetKey();

	//if (GetKeyboardTrigger(DIK_P) == true)
	//{//P�L�[�������ꂽ�Ƃ��Ƀ|�[�Y
	//	g_bPause = g_bPause ? false : true;
	//}
	//	/*if (g_bPause == true)*/
	//	/*{*///P�L�[��������Ă��Ȃ���
	//		�|�[�Y��ʂ̍X�V����

			/*UpdatePause();*/
	/*	}*/

		/*else if (g_bPause == false)
		{*/
			//�w�i�̍X�V����
			UpdateBg();

			//�S�[���̍X�V����
			UpdateGoal();

			//�v���C���[�̍X�V����
			UpdatePlayer();

			//�u���b�N�̍X�V����
			UpdateBlock();

			//���̍X�V����
			UpdateKey();

			//�U���̍X�V����
			UpdatePattack();

			//�G�̍X�V����
			UpdateEnemy();

			//�Èł̍X�V����
			UpdateBlack();

#ifdef _DEBUG


			//�G�f�B�b�g�̍X�V����
			UpdateEdit();

#endif

			if (g_gameState != GAMESTATE_NONE)
			{
				//�^�C���̍X�V����
				UpdateTime();
			}

			////�G�t�F�N�g�̍X�V����
			//UpdateEffect();

			////�p�[�e�B�N���̍X�V����
			//UpdateParticle();

			//���C�t�̍X�V����
			UpdateLife();

			////�|�[�Y���j���[��������
			//ResetPause();
	/*	}*/

	//if ( pPlayer->bUse == false)
	//{
	//	//���[�h�ݒ�(���U���g��ʂɈڍs)
	//	//SetMode(MODE_RESULT);
	//}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:  //�ʏ���

#ifdef _DEBUG

		if (GetKeyboardTrigger(DIK_F7) == true || GetGamepadTrigger(BUTTON_START, 0) == true)
		{
			g_gameState = GAMESTATE_END;
		}

#endif
		if (g_nGoal.pos.x - 5.0f <= pPlayer->pos.x && g_nGoal.pos.y - 30.0f <= pPlayer->pos.y && g_GetKey == 0)
		{
			g_gameState = GAMESTATE_END;
		}

		break;

	case GAMESTATE_GAMEOVER:

		g_nCounterGameState--;

			if (g_nCounterGameState <= 0)
			{
				g_gameState = GAMESTATE_NONE;

				/*g_bPause = true;*/

				//���[�h�ݒ�
				SetFade(MODE_GAMEOVER);
			}

		break;

	case GAMESTATE_END:  //�I��

		g_nCounterGameState--;
		
		if (g_nCounterGameState <= 0)
		{
			g_gameState = GAMESTATE_NONE;

			/*g_bPause = true;*/

			//���[�h�ݒ�
			SetFade(MODE_RESULT);
		}

		break;

	}
}

//===========================
//�Q�[����ʂ̕`�揈��
//===========================
void DrawGame(void)
{
   /* FADE g_Fade = GetFade();*/

	    //�w�i�̕`�揈��
		DrawBg();

		//�u���b�N�̕`�揈��
		DrawBlock();

		//���̕`�揈��
		DrawKey();

		//�G�̕`�揈��
		DrawEnemy();

		/*�Èł̕`�揈��*/
		DrawBlack();

		if (g_GetKey == 0)
		{
			//�S�[���̕`�揈��
			DrawGoal();
		}

		//�v���C���[�̕`�揈��
		DrawPlayer();

		//�U���̕`�揈��
		DrawPattack();

		//�^�C���̕`�揈��
		DrawTime();

		////�G�t�F�N�g�̕`�揈��
		//DrawEffect();

		////�p�[�e�B�N���̕`�揈��
		//DrawParticle();

		//���C�t�̕`�揈��
		DrawLife();

		//if (g_bPause == true && g_Fade == FADE_NONE)
		//{
		//	//�|�[�Y�̕`��
		//	DrawPause();
		//}

#ifdef _DEBUG

		//FPS�̕\��
		DrawFPS();

		//�G�f�B�b�g�̕`�揈��
		DrawEdit();

		//�G�̐���\��
		DrawEnemyCnt();

#endif

}

//=======================
//�Q�[���̏�Ԃ̐ݒ�
//=======================
void SetGameState(GAMESTATE state, int nCounter)
{
	g_gameState = state;

	g_nCounterGameState = nCounter;
}

//===================================
//�|�[�Y��Ԃ̎擾
//===================================
//void SetEnablePause(bool bPause)
//{
//	g_bPause = bPause;
//}

////=====================
////�Q�[����Ԃ̎擾
////=====================
//GAMESTATE GetGameState(void)
//{
//	return g_gameState;
//}

//========================
//�|�[�Y��Ԃ̎擾
//========================
//bool GetPause(void)
//{
//	return g_bPause;
//}

//=======================
//�}�b�v�̃��[�h����
//=======================
void LoadMap(void)
{
	int nCnt;

	//�}�b�v�̏����O���t�@�C������ǂݍ���
	pFile = fopen("map.txt", "r");

	

	if (pFile != NULL)
	{//�t�@�C����ǂݍ��߂��ꍇ
	 //�t�@�C�����當�����œǂݍ���

		for (nCnt = 0; nCnt < BLOCK_LOAD; nCnt++)
		{
			fscanf(pFile, "%f", &g_aBlockMap[nCnt]);
		}
		//�t�@�C�������
		fclose(pFile);
	}
}
