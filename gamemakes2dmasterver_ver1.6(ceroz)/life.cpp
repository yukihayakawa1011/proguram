//============================
//
//���C�t����(life.cpp)
//Author:���� �F�M
//
//============================
//#include "enemy.h"
#include "sound.h"
#include "Life.h"
#include "fade.h"
#include "life.h"
#include "player.h"

//�}�N����`
#define NUM_PLACE (3)		//���C�t�̐�
#define LIFE_DATA (20.0f)      //���C�t�̃T�C�Y

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posLife;  //���C�t�̈ʒu
int g_nLife;			//���C�t�̒l

//=============================
//  ���C�t�̏�����
//=============================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLife;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\LIFE.png",
		&g_pTextureLife);

	//���C�t�̏���������
	for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
	{
		g_posLife = D3DXVECTOR3(100.0f, 40.0f, 0.0f);  //�ʒu��������
	}

	g_nLife = 3;		//���C�t�̒l��������

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posLife.x - LIFE_DATA + (nCntLife * 75.0f), g_posLife.y - LIFE_DATA, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posLife.x + LIFE_DATA + (nCntLife * 75.0f), g_posLife.y - LIFE_DATA, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posLife.x - LIFE_DATA + (nCntLife * 75.0f), g_posLife.y + LIFE_DATA, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posLife.x + LIFE_DATA + (nCntLife * 75.0f), g_posLife.y + LIFE_DATA, 0.0f);

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

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//=====================
//���C�t�̏I������
//=====================
void UninitLife(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//==========================
//���C�t�̍X�V����
//=========================
void UpdateLife(void)
{
	FADE pFade;
	pFade = GetFade();
	LPDIRECT3DDEVICE9 pDevice;
	int nCntLife;
	Player *pPlayer = GetPlayer();

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntLife = 0; nCntLife < NUM_PLACE; nCntLife++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffLife->Unlock();

		//�v���C���[�̏����擾
		g_nLife = pPlayer->nLife;

	//���C�t�̏��
	if (g_nLife == 0)
	{//0�ɂȂ�����
		g_nLife = pPlayer->nLife;

		pPlayer->state = PLAYERSTATE_DEATH;
	}

	if (pFade == FADE_NONE)
	{
		if (g_nLife == 0)
		{
			
		}
	}
}

//======================
//���C�t�̕`�揈��
//======================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntLife;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLife);

	for (nCntLife = 0; nCntLife < g_nLife; nCntLife++)
	{//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
	}
}
