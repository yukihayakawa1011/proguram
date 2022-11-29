//============================
//
//�`���[�g���A������(tutorial.h)
//Author:���� �F�M
//
//============================
#include "title.h"
#include "main.h"
#include "game.h"
#include "sound.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "tutorial.h"

//�}�N����`
#define NUM_TUTORIAL  (4)  //�L�[�̍ő吔
#define MOVE_COL (0.01f) //�F�̈ړ���
//#define MOVE_ENT (0.1f)  //�G���^�[��������̈ړ�

//�`���[�g���A���\����
typedef struct
{
	bool bUse;
	D3DXCOLOR col;
}TUTORIAL;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureTutorial[NUM_TUTORIAL] = {};		//�e�N�X�`����(4����)�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;  //���_�o�b�t�@�ւ̃|�C���^
bool g_Kcheck = false; //�L�[�������ꂽ���m�F����
int g_Tutorial;		   //�`���[�g���A���̉摜���`�F�b�N
TUTORIAL g_aTutorial[NUM_TUTORIAL];
float g_Movcol;		//�F�̈ړ���
//float g_Moventer;	//�G���^�[��������̈ړ���

//======================
//�`���[�g���A����ʂ̏���������
//======================
void InitTutorial(void)
{
	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial1.png",
		&g_apTextureTutorial[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial2.png",
		&g_apTextureTutorial[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enter.png",
		&g_apTextureTutorial[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\back1.png",
		&g_apTextureTutorial[3]);

	//�L�[�`�F�b�N��������
	g_Kcheck = false;

	//�`���[�g���A����������
    g_Tutorial = 0;

	//������(�F�̈ړ���)
	g_Movcol = MOVE_COL;
	/*g_Moventer = MOVE_ENT;*/

	for (nCnt = 0; nCnt < NUM_TUTORIAL; nCnt++)
	{
		//�g�p���Ă��邩�ǂ���������
		g_aTutorial[nCnt].bUse = false;

		//�F��������
		g_aTutorial[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TUTORIAL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < NUM_TUTORIAL; nCnt++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		if (nCnt == 2)
		{
			pVtx[0].pos = D3DXVECTOR3(800.0f, 620.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1000.0f, 620.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800.0f, 710.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1000.0f, 710.0f, 0.0f);
		}

		if (nCnt == 3)
		{
			pVtx[0].pos = D3DXVECTOR3(300.0f, 620.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500.0f, 620.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(300.0f, 710.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(500.0f, 710.0f, 0.0f);
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

		pVtx += 4;   //���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM0015);
}

//============================
//�`���[�g���A���̏I������
//============================
void UninitTutorial(void)
{
	int nCnt;

	//�T�E���h�̒�~
	StopSound();

	for (nCnt = 0; nCnt < NUM_TUTORIAL; nCnt++)
	{
		if (g_apTextureTutorial[nCnt] != NULL)
		{
			g_apTextureTutorial[nCnt]->Release();
			g_apTextureTutorial[nCnt] = NULL;
		}

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}

//===============================
//�`���[�g���A���̍X�V����
//===============================
void UpdateTutorial(void)
{
	FADE pFade;
	pFade = GetFade();
	int nCnt = 0;

	//ENTER�L�[�̓_�ŏ���
	ColEntTutorial(nCnt);

	//BACK�L�[�̓_�ŏ���
	ColBackTutorial(nCnt);

	if (g_Tutorial == 0)
	{
		g_aTutorial[0].bUse = true;

		g_aTutorial[2].bUse = true;
	}

	else
	{
		g_aTutorial[1].bUse = true;

		g_aTutorial[2].bUse = true;

		g_aTutorial[3].bUse = true;
	}

	    //���̃y�[�W�ֈړ����鏈��
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
		{
			if (g_Tutorial == 0)
			{

				g_Tutorial = 1;

				g_aTutorial[1].bUse = true;

				g_aTutorial[3].bUse = true;

				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_ENTER);

				/*g_Movcol = g_Moventer;*/
			}

			//�Q�[����ʂֈڍs���鏈��
			else if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
			{//����(ENTER�L�[)�������ꂽ
			 //���[�h�ݒ�(�Q�[����ʂɈڍs)

				if (g_Kcheck == false && g_Tutorial == 1)
				{
					g_Kcheck = true;

					//�T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_ENTER);

					/*g_Movcol = g_Moventer;*/

					SetFade(MODE_GAME);
				}
			}
		}

		//�O�̃y�[�W�֖߂鏈��
		if (GetKeyboardTrigger(DIK_BACK) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
		{
			if (g_Tutorial == 1)
			{
				g_Tutorial = 0;

				g_aTutorial[1].bUse = false;

				g_aTutorial[3].bUse = false;

				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_ENTER);

				/*g_Movcol = g_Moventer;*/
			}
		}
}

//=================================
//�`���[�g���A���̕`�揈��
//=================================
void DrawTutorial(void)
{
	int nCnt;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < NUM_TUTORIAL; nCnt++)
	{
		if (g_aTutorial[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureTutorial[nCnt]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //�v���~�e�B�u�̎��
		}
	}
}

//==================
//�_�ŏ���(ENTER)
//==================
void ColEntTutorial(int nCnt)
{

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 8;

			if (g_aTutorial[nCnt].col.a < 0.0f || g_aTutorial[nCnt].col.a > 1.0f)
			{
				g_Movcol *= -1.0f;
			}

			g_aTutorial[nCnt].col.a -= g_Movcol;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aTutorial[nCnt].col;
		pVtx[1].col = g_aTutorial[nCnt].col;
		pVtx[2].col = g_aTutorial[nCnt].col;
		pVtx[3].col = g_aTutorial[nCnt].col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

}

//==================
//�_�ŏ���(BACK)
//==================
void ColBackTutorial(int nCnt)
{
	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 12;

		if (g_aTutorial[nCnt].col.a < 0.0f || g_aTutorial[nCnt].col.a > 1.0f)
		{
		g_Movcol *= -1.0f;
		}

		g_aTutorial[nCnt].col.a -= g_Movcol;
	
		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aTutorial[nCnt].col;
		pVtx[1].col = g_aTutorial[nCnt].col;
		pVtx[2].col = g_aTutorial[nCnt].col;
		pVtx[3].col = g_aTutorial[nCnt].col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
}