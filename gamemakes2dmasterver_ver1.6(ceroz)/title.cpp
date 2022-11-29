//============================
//
//�^�C�g������(title.h)
//Author:���� �F�M
//
//============================
#include "title.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "ranking.h"

//�}�N��
#define NUM_TITLE (2) //�^�C�g����ʂɎg��
#define MOVE_COLOR (0.01f) //�F�̈ړ���
#define MOVE_ENTER (0.5f)  //�G���^�[��������̈ړ�
#define CNT_DATA    (360)  //�����J�ڂ̐��𐔂���f�[�^

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureTitle[NUM_TITLE] = {};		//�e�N�X�`��(2����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;  //���_�o�b�t�@�ւ̃|�C���^
bool g_Keycheck; //�L�[�������ꂽ���m�F����
D3DXCOLOR col;			//�F�Ɋւ��Ďg��
float g_Movecol;		//�F�̈ړ���
float g_Moveenter;		//�G���^�[��������̈ړ���
int g_CntTrance;		//�����L���O�ɑJ�ڂ���܂ł̎��Ԃ𐔂���f�[�^

//======================
//�^�C�g����ʂ̏���������
//======================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//������(�L�[�`�F�b�N)
	 g_Keycheck = false;

	 //������(�F�̈ړ���)
	 g_Movecol = MOVE_COLOR;
	 g_Moveenter = MOVE_ENTER;

	 //�J���[��������
	 col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	 //�����L���O�ɑJ�ڂ��鎞�Ԃ𐔂���f�[�^��������
	 g_CntTrance = 0;

	 //�v���X�G���^�[�_�ł�������
	 col.a = g_Movecol;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\escape.png",
		&g_apTextureTitle[0]);
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pressenter.png",
		&g_apTextureTitle[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < NUM_TITLE; nCnt++)
	{
		if (nCnt == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		}

		if(nCnt == 1)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 300.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(700.0f, 300.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(700.0f, 600.0f, 0.0f);
		}

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

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM000);
}

//============================
//�^�C�g���̏I������
//============================
void UninitTitle(void)
{
	//�T�E���h�̒�~
	StopSound();

	int nCnt;

	for (nCnt = 0; nCnt < NUM_TITLE; nCnt++)
	{
		if (g_apTextureTitle[nCnt] != NULL)
		{
			g_apTextureTitle[nCnt]->Release();
			g_apTextureTitle[nCnt] = NULL;
		}
	}

		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffTitle != NULL)
		{
			g_pVtxBuffTitle->Release();
			g_pVtxBuffTitle = NULL;
		}
}

//===============================
//�^�C�g����ʂ̍X�V����
//===============================
void UpdateTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	FADE pFade;
	pFade = GetFade();
	int nCnt = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�^�C�g���̃v���X�G���^�[��_�ł��鏈��
	for (nCnt = 0; nCnt < NUM_TITLE; nCnt++)
	{
		if (nCnt == 1)
		{
			col.a -= g_Movecol;

			if (col.a < 0.0f || col.a > 1.0f)
			{
			 g_Movecol *= -1.0f;
			}

			//���_�J���[�̐ݒ�
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	g_CntTrance++;

	if (g_CntTrance >= CNT_DATA)
	{//6�b�o������
	 //���[�h�ݒ�(�����L���O��ʂɈڍs)

		ResetData();

		if (pFade == FADE_NONE)
		{
			SetFade(MODE_RANKING);
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
	{//����(ENTER�L�[)�������ꂽ
		if (g_Keycheck == false)
		{
			//���[�h�ݒ�(�Q�[����ʂɈڍs)

			//�T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_ENTER);

			g_Movecol = g_Moveenter;

			g_Keycheck = true;

			SetFade(MODE_TUTORIAL);
		}
	}
}

//=================================
//�^�C�g����ʂ̕`�揈��
//=================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < NUM_TITLE; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureTitle[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //�v���~�e�B�u�̎��
	}

#ifdef _DEBUG

	//FPS�̕\��
	DrawFPS();

#endif

}