//============================
//
//�^�C������(time.cpp)
//Author:���� �F�M
//
//============================
//#include "bullet.h"
//#include "enemy.h"
#include "sound.h"
#include "time.h"
#include "fade.h"
#include "game.h"
#include"player.h"

//�}�N����`
#define NUM_PLACE (3)		//�^�C���̌���
#define MAX_TIME (128)
#define POS_DATA  (200.0f)  //�^�C���̕������߂�

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTime;  //�^�C���̈ʒu
int g_Timelog;			//�^�C���̕b�𑪂�
int g_nTime;			//�^�C���̒l
bool g_bfade;
float g_fWindth;		//���̒l
float g_fHeight;		//�����̒l

//=============================
//  �^�C���̏�����
//=============================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTime;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&g_pTextureTime);

	//�^�C���̏���������
	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		g_posTime = D3DXVECTOR3(500.0f, 50.0f, 0.0f);  //�ʒu��������

		g_Timelog = 0;      //�^�C���̕b

		g_nTime = 180;		//�^�C���̒l

		g_bfade = false;	//�t�F�[�h�Ɏg���ϐ�

		g_fWindth = (0.0f);	  //���̒l
		g_fHeight = (0.0f);   //�����̒l
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - 60.0f + (nCntTime * 100.0f), g_posTime.y - 60.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + 60.0f + (nCntTime * 100.0f), g_posTime.y - 60.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - 60.0f + (nCntTime * 100.0f), g_posTime.y + 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + 60.0f + (nCntTime * 100.0f), g_posTime.y + 60.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (nCntTime == 0)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.2f, 1.0f);
		}

		if (nCntTime == 1)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.8f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.9f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.8f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.9f, 1.0f);
		}

		if (nCntTime == 2)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//=====================
//�^�C���̏I������
//=====================
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=====================
//�^�C���̍X�V����
//=====================
void UpdateTime(void)
{
	FADE pFade;
	pFade = GetFade();
	Player *pPlayer = GetPlayer();

	LPDIRECT3DDEVICE9 pDevice;
	int aTexU[NUM_PLACE];  //�e���̐������i�[
	int nCntTime;

	g_Timelog++;

	if (g_Timelog % 60 == 0)
	{
		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		if (pFade == FADE_NONE)
		{
			g_nTime --;
		}

		aTexU[0] = g_nTime % 1000 / 100;
		aTexU[1] = g_nTime % 100 / 10;
		aTexU[2] = g_nTime % 10 / 1;

		VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntTime] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntTime] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntTime] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntTime] * 0.1f), 1.0f);

			pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTime->Unlock();
	}

	if (pPlayer->nLife == 0)
	{
		g_nTime = 1;
	}

	//�^�C���̏��
	else if (g_nTime <= 0)
	{//0�ɂȂ�����
		g_nTime = 1;

		PlaySound(SOUND_LABEL_WINDOW);

		PlaySound(SOUND_LABEL_TIMEUP);
	}

	//�Q�[���I�[�o�[��ʂւ̈ڍs
	if (g_bfade == false && g_nTime <= 1)
	{
		g_bfade = true;

		//�Q�[����Ԃ̐ݒ�
		SetGameState(GAMESTATE_GAMEOVER, 120);
	}
}

//======================
//�^�C���̕`�揈��
//======================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntTime;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
	{//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}

//===============================
//�^�C���̐ݒ菈��
//===============================
void SetTime(int nTime)
{
	LPDIRECT3DDEVICE9 pDevice;
	int aTexU[NUM_PLACE];  //�e���̐������i�[
	int nCntTime;
	g_nTime = nTime;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	aTexU[0] = g_nTime % 1000 / 100;
	aTexU[1] = g_nTime % 100 / 10;
	aTexU[2] = g_nTime % 10 / 1;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntTime] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntTime] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntTime] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntTime] * 0.1f), 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//==================================
//�^�C���̈ʒu�ݒ�
//==================================
void SetPosTime(D3DXVECTOR3 pos, float fWindth, float fHeight)
{
	int nCntTime;

	//�^�C���̐ݒ����������
	g_posTime = pos;

	g_fWindth = fWindth;

	g_fHeight = fHeight;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < NUM_PLACE; nCntTime++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x + (nCntTime * POS_DATA) - g_fWindth, g_posTime.y - g_fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + (nCntTime * POS_DATA) + g_fWindth, g_posTime.y - g_fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x + (nCntTime * POS_DATA) - g_fWindth, g_posTime.y + g_fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + (nCntTime * POS_DATA) + g_fWindth, g_posTime.y + g_fHeight , 0.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//======================
//�^�C���𖾂��n������
//======================
int GetTime(void)
{
	return g_nTime;
}