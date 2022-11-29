//============================
//
//���U���g����(result.h)
//Author:���� �F�M
//
//============================
#include "result.h"
#include "main.h"
#include "game.h"
#include "sound.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "time.h"

//�}�N����`
#define TRANCE_DATA (300)

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;  //���_�o�b�t�@�ւ̃|�C���^
int g_ResultTime;  //�X�R�A���i�[����
int g_ResultTrance; //�J�ڂ܂ł̎��Ԃ�}�鏈��

//======================
//���U���g��ʂ̏���������
//======================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�J�ڂ܂ł̎��Ԃ�}�鏈����������
	g_ResultTrance = 0;

	//�^�C���̐��l�����U���g�Ŏ󂯎�鏈��
	g_ResultTime = GetTime();

	//�^�C���̏�����
	InitTime();

	//�X�R�A�̍��W��ݒ�
	SetPosTime(D3DXVECTOR3(750.0f, 500.0f, 0.0f),(100.0f),(100.0f));

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gameclear.png",
		&g_pTextureResult);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM003);
}

//============================
//���U���g�̏I������
//============================
void UninitResult(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�^�C���̏I��
	UninitTime();

	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//===============================
//���U���g��ʂ̍X�V����
//===============================
void UpdateResult(void)
{
	FADE pFade;
	pFade = GetFade();

	SetTime(g_ResultTime);

	g_ResultTrance++;

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_A, 0) == true || g_ResultTrance >= TRANCE_DATA)
	{//����(ENTER�L�[)�������ꂽ
	 //���[�h�ݒ�(�Q�[����ʂɈڍs)

		if (pFade == FADE_NONE)
		{
			SetFade(MODE_RANKING);
		}
	}

}

//=================================
//���U���g��ʂ̕`�揈��
//=================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��

	//�X�R�A�̕`��
	DrawTime();

#ifdef _DEBUG

	//FPS�̕\��
	DrawFPS();

#endif
}
