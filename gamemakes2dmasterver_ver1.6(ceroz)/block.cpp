//============================
//
//�u���b�N�̏���(block.cpp)
//Author:���� �F�M
//
//============================
#include "block.h"
#include "player.h"
#include "edit.h"

//�}�N��
#define BLOCK_X (200.0f)
#define BLOCK_Y (20.0f)
#define BLOCK_HEIGHT (20.0f)

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL; //���_�o�b�t�@�ւ̃|�C���^
BLOCK g_aBlock[MAX_BLOCK];

//========================
//�u���b�N�̏���������
//========================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

    //�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\block.png",
		&g_pTextureBlock);

	//�u���b�N�̏���������
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(500.0f, 300.0f, 0.0f);  //�ʒu��������

		g_aBlock[nCntBlock].fWidth = 50.0f;	  //���̏�����

		g_aBlock[nCntBlock].fHeight = 50.0f;	  //�����̏�����

		g_aBlock[nCntBlock].bUse = false;  //�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_X, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_X, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

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
	g_pVtxBuffBlock->Unlock();
}

//========================
//�u���b�N�̏I������
//========================
void UninitBlock(void)
{
	/*int nCntBlock;*/

	//�e�N�X�`���̔j��
		if (g_pTextureBlock != NULL)
		{
			g_pTextureBlock->Release();
			g_pTextureBlock = NULL;
		}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}
//=================================
//�u���b�N�̍X�V����
//=================================
void UpdateBlock(void)
{
}

//==========================
//�u���b�N�̕`�揈��
//==========================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBlock);

		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse == true)
			{
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2); //�v���~�e�B�u�̎��
			}
		}
}

//====================
//�u���b�N�̐ݒ菈��
//====================
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nCntBlock;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			//�u���b�N���g�p����Ă��Ȃ�
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			break;
		}
		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

}

//===============================
//�u���b�N�̓����蔻��
//===============================
bool colisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight,bool bJump)
{
	int nCntBlock;
	bool bLand = false; //���n�������ǂ���

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g���Ă�����
			if (bJump == true)
			{//�W�����v���g�p����Ă�����
				if (pPos->y > g_aBlock[nCntBlock].pos.y
					&& pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + BLOCK_Y)
				{//�u���b�N��Y�͈͓̔��̎�,���̓����蔻��
					if (pPosOld->x + fWidth <= g_aBlock[nCntBlock].pos.x
						&&pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x - fWidth;
						pMove->x = 0.0f; //�ړ��ʂ�0�ɂ���
					}

					else if (pPosOld->x - fWidth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
						&& pPos->x - fWidth < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
					{
						pPos->x = fWidth + g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
						pMove->x = 0.0f; //�ړ��ʂ�0�ɂ���
					}
				}

				if (pPos->x - fWidth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
					&& pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x)
				{//�u���b�N�͈͓̔��̎�,�c�̓����蔻��
					if (pPosOld->y <= g_aBlock[nCntBlock].pos.y
						&& pPos->y >= g_aBlock[nCntBlock].pos.y)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y; //�u���b�N�̏�ɗ�������
						pMove->y = 0.0f; //�ړ��ʂ�0�ɂ���
					}

					else if (pPosOld->y - fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight
						&& pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
					{//�u���b�N��艺�Ŕ͈͓��̎�
						pPos->y = fHeight + g_aBlock[nCntBlock].pos.y + 50.0f;
						pMove->y = 0.0f; //�ړ��ʂ�0�ɂ���
					}
				}
			}

			else
			{//�W�����v���g�p����Ă��Ȃ�������
				if (pPos->x - fWidth < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
					&& pPos->x + fWidth > g_aBlock[nCntBlock].pos.x)
				{//�u���b�N�͈͓̔��̎�,�c�̓����蔻��
					if (pPosOld->y <= g_aBlock[nCntBlock].pos.y
						&& pPos->y > g_aBlock[nCntBlock].pos.y)
					{
						bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y; //�u���b�N�̏�ɗ�������
						pMove->y = 0.0f; //�ړ��ʂ�0�ɂ���
					}

					else if (pPosOld->y - fHeight > g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight
						&& pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
					{//�u���b�N��艺�Ŕ͈͓��̎�
						pPos->y = fHeight + g_aBlock[nCntBlock].pos.y + 50.0f;
						pMove->y = 0.0f; //�ړ��ʂ�0�ɂ���
					}
				}

				if (pPos->y > g_aBlock[nCntBlock].pos.y
					&& pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + BLOCK_Y)
				{//�u���b�N��Y�͈͓̔��̎�,���̓����蔻��
					if (pPosOld->x + fWidth <= g_aBlock[nCntBlock].pos.x
						&&pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x)
					{
						pPos->x = g_aBlock[nCntBlock].pos.x - fWidth;
						pMove->x = 0.0f; //�ړ��ʂ�0�ɂ���
					}

					else if (pPosOld->x - fWidth >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth
						&& pPos->x - fWidth < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
					{
						pPos->x = fWidth + g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
						pMove->x = 0.0f; //�ړ��ʂ�0�ɂ���
					}
				}
			}
		}
	}
	return bLand;
}

//========================
//�u���b�N�𖾂��n��
//========================
BLOCK *GetBlock(void)
{
	return &g_aBlock[0];
}