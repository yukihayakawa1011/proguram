//======================
//
//�U���̏���(pattack.cpp)
//Author: ���� �F�M
//
//======================

#include "sound.h"
#include "pattack.h"
#include "player.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePattack = NULL;  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPattack = NULL; //���_�o�b�t�@�ւ̃|�C���^
PATTACK g_aPattack;  //�U���̏��

//======================
//�U���̏�����
//======================
void InitPattack(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\playerattackanim.png",
		&g_pTexturePattack);

	g_aPattack.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ʒu��������

	g_aPattack.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);    //�F��������

	g_aPattack.nCounterAnim = 0;  //�A�j���[�V�����J�E���^�[��������

	g_aPattack.nPatternAnim = 0;  //�A�j���[�V�����p�^�[��No.��������

	g_aPattack.bUse = false;  //�g�p���Ă��Ȃ���Ԃɂ���

								//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPattack,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPattack->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aPattack.pos.x - 20.0f, g_aPattack.pos.y - 150.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aPattack.pos.x + 20.0f, g_aPattack.pos.y - 150.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aPattack.pos.x - 20.0f, g_aPattack.pos.y - 50.0f , 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aPattack.pos.x - 20.0f, g_aPattack.pos.y - 50.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPattack->Unlock();
}

//===========================
//�U���̏I������
//===========================
void UninitPattack(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePattack != NULL)
	{
		g_pTexturePattack->Release();
		g_pTexturePattack = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPattack != NULL)
	{
		g_pVtxBuffPattack->Release();
		g_pVtxBuffPattack = NULL;
	}
}

//==================
//�U���̍X�V����
//==================
void UpdatePattack(void)
{
}

//======================
//�U���̕`�揈��
//======================
void DrawPattack(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPattack, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePattack);

	if (g_aPattack.bUse == true)
	{//�U�����g�p����Ă���
	 //�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	}
}

//======================
//�U���̐ݒ菈��
//======================
void SetPattack(D3DXVECTOR3 pos)
{

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^
						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPattack->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aPattack.bUse == false)
	{//�U�����g�p����Ă��Ȃ�

	 //���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aPattack.pos.x - 50.0f, g_aPattack.pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPattack.pos.x + 50.0f, g_aPattack.pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPattack.pos.x - 50.0f, g_aPattack.pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPattack.pos.x + 50.0f, g_aPattack.pos.y + 50.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aPattack.nPatternAnim) * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aPattack.nPatternAnim) * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aPattack.nPatternAnim) * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aPattack.nPatternAnim) * 0.1f, 1.0f);

		//g_aExplosion[nCntEXPLOSION].move = move;
		//g_aExplosion[nCntEXPLOSION].nLife = 100;
		g_aPattack.bUse = true;  //�g�p���Ă����Ԃɂ���
		g_aPattack.nCounterAnim = 0;  //�A�j���[�V�����J�E���^�[
		g_aPattack.nPatternAnim = 0;  //�A�j���[�V�����p�^�[��No.
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPattack->Unlock();
}

//======================
//�U���̏���n��
//======================
PATTACK *GetPattack(void)
{
	return  &g_aPattack;
}

//=====================
//�E�U���̏���
//=====================
void RightPattack(void)
{
	/*int nCnt;*/

	Player *pPlayer = GetPlayer();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPattack->Lock(0, 0, (void**)&pVtx, 0);

	g_aPattack.bUse = true;


	//for (nCnt = 0; nCnt < 4; nCnt++)
	//{
		if (g_aPattack.bUse == true)
		{//�U�����g�p����Ă���

			g_aPattack.nCounterAnim++;

		 //���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - 20.0f, pPlayer->pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x + 20.0f, pPlayer->pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x - 20.0f, pPlayer->pos.y - 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + 20.0f, pPlayer->pos.y - 0.0f, 0.0f);

			if ((g_aPattack.nCounterAnim % 6) == 0)
			{
				g_aPattack.nPatternAnim = (g_aPattack.nPatternAnim + 1) % 4;		//�p�^�[��NO.���X�V����
			}
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f + 0.25f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f, 0.5f);
			pVtx[3].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f + 0.25f, 0.5f);

			////���p�^�[�����𒴂���
			//if (g_aPattack.nPatternAnim == 3)
			//{
			//	g_aPattack.bUse = false;  //�g�p���Ă��Ȃ���Ԃɂ���
			//}

		}

	//}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPattack->Unlock();
}

//=====================
//���U���̏���
//=====================
void LeftPattack(void)
{
	/*int nCnt;*/

	Player *pPlayer = GetPlayer();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPattack->Lock(0, 0, (void**)&pVtx, 0);

	g_aPattack.bUse = true;

	/*for (nCnt = 0; nCnt < 4; nCnt++)
	{*/
		if (g_aPattack.bUse == true)
		{//�U�����g�p����Ă���

			g_aPattack.nCounterAnim++;

		 //���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - 20.0f, pPlayer->pos.y - 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x + 20.0f, pPlayer->pos.y - 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x - 20.0f, pPlayer->pos.y - 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + 20.0f, pPlayer->pos.y - 0.0f, 0.0f);

			if ((g_aPattack.nCounterAnim % 6) == 0)
			{
				g_aPattack.nPatternAnim = (g_aPattack.nPatternAnim + 1) % 4;		//�p�^�[��NO.���X�V����
			}

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f + 0.25f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_aPattack.nPatternAnim % 4) * 0.25f + 0.25f, 1.0f);
		/*}*/

		////���p�^�[�����𒴂���
		//if (g_aPattack.nPatternAnim == 3)
		//{
		//	g_aPattack.bUse = false;  //�g�p���Ă��Ȃ���Ԃɂ���
		//}

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPattack->Unlock();
}
