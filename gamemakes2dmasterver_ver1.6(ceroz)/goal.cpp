//============================
//
//�S�[������(goal.h)
//Author:���� �F�M
//
//============================
#include "goal.h"
#include "main.h"
#include "game.h"
//#include "sound.h"
#include "player.h"
#include "input.h"
#include "fade.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;  //���_�o�b�t�@�ւ̃|�C���^
GOAL g_Goal; //�S�[���̏��

//======================
//�S�[����ʂ̏���������
//======================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�S�[���̈ʒu��������
	g_Goal.pos = D3DXVECTOR3(1250.0f, 700.0f, 0.0f);

	//�S�[���̗L����������
	g_Goal.bUse = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\door.png",
		&g_pTextureGoal);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(1250.0f, 630.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 630.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1250.0f, 710.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 710.0f, 0.0f);

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

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();

	////�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_BGM002);
}

//============================
//�S�[���̏I������
//============================
void UninitGoal(void)
{
	////�T�E���h�̒�~
	//StopSound();

	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//===============================
//�S�[����ʂ̍X�V����
//===============================
void UpdateGoal(void)
{
}

//=================================
//�S�[����ʂ̕`�揈��
//=================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGoal);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��

													   ////�X�R�A�̕`��
													   //DrawScore();
}

//==========================
//�S�[���̏��𖾂��n������
//==========================
GOAL GetGoal(void)
{
	return g_Goal;
}
