//============================
//
//�Èŏ���(black.h)
//Author:���� �F�M
//
//============================
#include "black.h"
#include "main.h"
#include "game.h"
#include "player.h"

//�}�N��
#define BLACK_X (1500.0f)  //�Èł̕�
#define BLACK_Y (1000.0f)  //�Èł̍���

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBlack = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlack = NULL;  //���_�o�b�t�@�ւ̃|�C���^

//======================
//�Èŉ�ʂ̏���������
//======================
void InitBlack(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer = GetPlayer();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���C���[�̏���������
	pPlayer->bUse = true;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\black1.png",
		&g_pTextureBlack);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlack,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlack->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffBlack->Unlock();

}

//============================
//�Èł̏I������
//============================
void UninitBlack(void)
{

	if (g_pTextureBlack != NULL)
	{
		g_pTextureBlack->Release();
		g_pTextureBlack = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlack != NULL)
	{
		g_pVtxBuffBlack->Release();
		g_pVtxBuffBlack = NULL;
	}
}

//===============================
//�Èŉ�ʂ̍X�V����
//===============================
void UpdateBlack(void)
{
	//�v���C���[�̏����󂯎��
	Player *pPlayer = GetPlayer();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlack->Lock(0, 0, (void**)&pVtx, 0);

	if (pPlayer->bUse == true)
	{//�v���C���[���g�p����Ă�����
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - BLACK_X, pPlayer->pos.y - BLACK_Y,0.0f);
		pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x + BLACK_X, pPlayer->pos.y - BLACK_Y,0.0f);
		pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x - BLACK_X, pPlayer->pos.y + BLACK_Y,0.0f);
		pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + BLACK_X, pPlayer->pos.y + BLACK_Y,0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlack->Unlock();
}

//=================================
//�Èŉ�ʂ̕`�揈��
//=================================
void DrawBlack(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlack, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBlack);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��
}
