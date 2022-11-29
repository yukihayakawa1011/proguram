//============================
//
//�G�f�B�b�g����(title.h)
//Author:���� �F�M
//
//============================
#include "edit.h"
#include "main.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "block.h"
//#include "ranking.h"

//�}�N��
#define EDIT_MOVE (10.0f)  //�G�f�B�b�g�̈ړ���
#define EDIT_X  (20.0f)
#define EDIT_Y  (20.0f)

//�G�f�B�b�g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	bool bUse;
}Edit;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEdit = NULL;		//�e�N�X�`��(2����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEdit = NULL;  //���_�o�b�t�@�ւ̃|�C���^
Edit g_Edit;  //�G�f�B�b�g�̏��

//======================
//�G�f�B�b�g��ʂ̏���������
//======================
void InitEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�G�f�B�b�g�̏���������
	g_Edit.pos = D3DXVECTOR3(g_Edit.pos.x, g_Edit.pos.y, 0.0f);

	g_Edit.bUse = false; //�@�g�p���Ă��邩�ǂ�����������

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block000.png",
		&g_pTextureEdit);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEdit,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Edit.pos.x, g_Edit.pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Edit.pos.x + 20.0f, g_Edit.pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Edit.pos.x, g_Edit.pos.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Edit.pos.x + 20.0f, g_Edit.pos.y + 20.0f, 0.0f);
		
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
		g_pVtxBuffEdit->Unlock();
}

//============================
//�G�f�B�b�g�̏I������
//============================
void UninitEdit(void)
{
		if (g_pTextureEdit != NULL)
		{
			g_pTextureEdit->Release();
			g_pTextureEdit = NULL;
		}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEdit != NULL)
	{
		g_pVtxBuffEdit->Release();
		g_pVtxBuffEdit = NULL;
	}
}

//===============================
//�G�f�B�b�g��ʂ̍X�V����
//===============================
void UpdateEdit(void)
{
	if (GetKeyboardTrigger(DIK_LEFTARROW) == true)
	{
		g_Edit.pos.x -= EDIT_MOVE;
	}

	if (GetKeyboardTrigger(DIK_RIGHTARROW) == true)
	{
		g_Edit.pos.x += EDIT_MOVE;
	}

	if (GetKeyboardTrigger(DIK_DOWNARROW) == true)
	{
		g_Edit.pos.y += EDIT_MOVE;
	}

	if (GetKeyboardTrigger(DIK_UPARROW) == true)
	{
		g_Edit.pos.y -= EDIT_MOVE;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetBlock(D3DXVECTOR3(g_Edit.pos.x - 20.0f, g_Edit.pos.y - 20.0f, 0.0f), 40.0f, 40.0f);
		g_Edit.bUse = true;
	}

	if (GetKeyboardTrigger(DIK_BACKSPACE) == true)
	{
		DelEdit();
	}

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Edit.pos.x - EDIT_X, g_Edit.pos.y - EDIT_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Edit.pos.x + EDIT_X, g_Edit.pos.y - EDIT_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Edit.pos.x - EDIT_X,g_Edit.pos.y + EDIT_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Edit.pos.x + EDIT_X, g_Edit.pos.y +EDIT_Y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEdit->Unlock();

}

//=================================
//�G�f�B�b�g��ʂ̕`�揈��
//=================================
void DrawEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEdit, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureEdit);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2); //�v���~�e�B�u�̎��
}

//===========================
//�u���b�N���폜���鏈��
//===========================
void DelEdit(void)
{
	int nCnt;

	BLOCK *Block = GetBlock();

	for (nCnt = 0; nCnt < MAX_BLOCK; nCnt++, Block++)
	{
		if (Block->bUse == true)
		{

			if (nCnt == 56)
			{
				int a = 0;
			}

			if (g_Edit.pos.x - 20.0f == Block->pos.x
			&&  g_Edit.pos.y - 20.0f == Block->pos.y)
			{
				Block->bUse = false;
			}
		}
	}
}