//============================
//
//�����L���O����(ranking.h)
//Author:���� �F�M
//
//============================
#include "result.h"
#include "main.h"
#include "game.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "time.h"
#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>

//�}�N��
#define HI_DATA (5)		//�񂷐�
#define ZERO_DATA  (0)  //�����Ȃ��f�[�^
#define MAX_DATA   (5)  //�ő吔
#define ONE_DATA  (1)  //1�������Ɏg��
#define MAXONE_DATA (6) //�ő吔���1�傫���f�[�^
#define X_DATA  (500.0f)  //x���̃f�[�^
#define Y_DATA  (180.0f)  //y���̃f�[�^
#define SPACE_DATA (120.0f)  //�X�R�A�̊Ԋu�̃f�[�^
#define NEWRANK_DATA (50.0f)  //�V�L�^��Y��
#define NUM_RANKING  (2)	//�e�N�X�`���̐�
#define CNT_DATA	 (300)	//�J�ڂ܂ł̎��Ԃ𐔂���f�[�^

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureRanking[NUM_RANKING] = {};		//�e�N�X�`��(2����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;  //���_�o�b�t�@�ւ̃|�C���^
int g_RankingTime;		 //�X�R�A���i�[����
FILE *pnFile;
int g_aData[MAX_DATA];  //�f�[�^�̐�
int g_Rank;			//�v���C���[�̃X�R�A�����L���O���o����
bool g_Ranking;
int g_TranceCnt;
bool g_Keychack;

//======================
//�����L���O��ʂ̏���������
//======================
void InitRanking(void)
{
	int nCnt;

	int nTemp;				//��r�Ɏg�p

	int nCount1, nCount2;  //�v�f1,�v�f2

	LPDIRECT3DDEVICE9 pDevice;

	//�o���郉���L���O��������
	g_Rank = -1;

	//�����L���O���X�V���ꂽ���X�V
	g_Ranking = false;

	//�����őJ��
	g_TranceCnt = 0;

	//�L�[�`�F�b�N��������
	g_Keychack = false;

	//�X�R�A�̐��l�������L���O�Ŏ󂯎�鏈��
	g_RankingTime = GetTime();

	////�^�C���̏�����
	InitTime();

	//���[�h����
	LoadData();

	//�^�C���̕`��
	for (nCnt = 0; nCnt < HI_DATA; nCnt++)
	{
		//�^�C���̍��W��ݒ�
		SetPosTime(D3DXVECTOR3(X_DATA, Y_DATA + (nCnt * SPACE_DATA), 0.0f), (100.0f), (1000.0f));

		SetTime(g_aData[nCnt]);

		//�^�C���̕`��
		DrawTime();
	}

	//�\�[�g�̍~������
	if (g_aData[HI_DATA - 1] < g_RankingTime)
	{
		g_aData[HI_DATA - 1] = g_RankingTime;
	}

	//�\�[�g�̍~������
	for (nCount1 = ZERO_DATA; nCount1 < HI_DATA - 1; nCount1++)
	{
		for (nCount2 = nCount1 + ONE_DATA; nCount2 < MAX_DATA; nCount2++)
		{
			if (g_aData[nCount1] < g_aData[nCount2])
			{
				//1�x�ʂ̕ϐ��Ƀf�[�^���m�ۂ��Ă���㏑������
				nTemp = g_aData[nCount1];
				g_aData[nCount1] = g_aData[nCount2];
				g_aData[nCount2] = nTemp;
			}
		}
	}

	for (nCount1 = ZERO_DATA; nCount1 < HI_DATA; nCount1++)
	{
		if (g_RankingTime == g_aData[nCount1])
		{
			g_Rank = nCount1;

			g_Ranking = true;

			break;
		}
	}

	//�Z�[�u�f�[�^����
	SaveData();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking.png",
		&g_apTextureRanking[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Yourtime.png",
		&g_apTextureRanking[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < NUM_RANKING; nCnt++)
	{
		if (nCnt == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}

		if (nCnt == 1)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(1000.0f, Y_DATA - (NEWRANK_DATA) + (g_Rank * SPACE_DATA), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1200.0f, Y_DATA - (NEWRANK_DATA) + (g_Rank * SPACE_DATA), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1000.0f, Y_DATA + (NEWRANK_DATA) + (g_Rank * SPACE_DATA), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1200.0f, Y_DATA + (NEWRANK_DATA) + (g_Rank * SPACE_DATA), 0.0f);
		}
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_RANKING);
}

//============================
//�����L���O�̏I������
//============================
void UninitRanking(void)
{
	int nCnt;

	//�T�E���h�̒�~
	StopSound();

	//�X�R�A�̏I��
	UninitTime();

	for (nCnt = 0; nCnt < NUM_RANKING; nCnt++)
	{
		if (g_apTextureRanking[nCnt] != NULL)
		{
			g_apTextureRanking[nCnt]->Release();
			g_apTextureRanking[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//===============================
//�����L���O��ʂ̍X�V����
//===============================
void UpdateRanking(void)
{
	/*int nCnt;*/

	FADE pFade;
	pFade = GetFade();

	g_TranceCnt++;

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_A, 0) == true || g_TranceCnt >= CNT_DATA)
	{//����(ENTER�L�[)�������ꂽ
		if (g_Keychack == false)
		{
			//���[�h�ݒ�(�Q�[����ʂɈڍs)

			//�T�E���h�̍Đ�
			//PlaySound(SOUND_LABEL_SE_ENTER);

			g_Keychack = true;

			SetFade(MODE_TITLE);
		}
	}

}

//=================================
//�����L���O��ʂ̕`�揈��
//=================================
void DrawRanking(void)
{
	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < NUM_RANKING; nCnt++)
	{
		if (nCnt == 0 && g_Ranking == false)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureRanking[nCnt]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //�v���~�e�B�u�̎��
			break;
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureRanking[nCnt]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //�v���~�e�B�u�̎��
		}
	}

	//�^�C���̕`��
	for (nCnt = 0; nCnt < HI_DATA; nCnt++)
	{
		//�X�R�A�̍��W��ݒ�
		SetPosTime(D3DXVECTOR3(X_DATA, Y_DATA + (nCnt * SPACE_DATA), 0.0f), (50.0f), (50.0f));

		SetTime(g_aData[nCnt]);

		//�X�R�A�̕`��
		DrawTime();

		SetTime(0);
	}

#ifdef _DEBUG

	//FPS�̕\��
	DrawFPS();

#endif
}

//================================
//�Z�[�u�f�[�^����
//================================
void SaveData(void)
{
	int nCount;

	//�t�@�C�����J��
	pnFile = fopen("time.txt", "w");

	if (pnFile != NULL)
	{//�t�@�C�����J�����ꍇ
	 //��������t�@�C���ɏ�������
		for (nCount = ZERO_DATA; nCount < MAX_DATA; nCount++)
		{
			fprintf(pnFile, "%d\n", g_aData[nCount]);
		}

		//�t�@�C�������
		fclose(pnFile);
	}

	else
	{//�t�@�C�����ǂݍ��߂Ȃ������ꍇ
		g_RankingTime = 0;                 //�t�@�C����ǂݍ��߂Ȃ��������Ƃ�\��
	}
}

//================================
//���[�h����
//================================
void LoadData(void)
{
	int nCount;

	//�t�@�C�����J��
	pnFile = fopen("time.txt", "r");

	if (pnFile != NULL)
	{//�t�@�C�����J�����ꍇ

		for (nCount = ZERO_DATA; nCount < HI_DATA; nCount++)
		{
			fscanf(pnFile, "%d", &g_aData[nCount]);
		}

		fclose(pnFile);
	}

	else
	{//�t�@�C�����ǂݍ��߂Ȃ������ꍇ
		printf("***�t�@�C����ǂݍ��߂܂���ł���***\n\n");                  //�t�@�C����ǂݍ��߂Ȃ��������Ƃ�\��
	}
}

//=================================================
//�����L���O���X�V���ꂽ���ǂ��������Z�b�g���鏈��
//=================================================
void ResetData(void)
{
	//�����L���O���X�V���ꂽ���X�V
	g_Ranking = false;
}


