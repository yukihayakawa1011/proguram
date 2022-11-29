//============================
//
//�u���b�N�Ɋւ��鏈��(block.h)
//Author:���� �F�M
//
//============================

#ifndef _BLOCK_H_   //���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define MAX_BLOCK   (128)   //�G�̍ő吔

//�u���b�N�\����
typedef struct
{
	D3DXVECTOR3 pos;  //�u���b�N�̈ʒu
	float fWidth;	  //��
	float fHeight;	  //����
	bool bUse;		  //�g���Ă��邩�ǂ���
}BLOCK;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight);
bool colisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove , float fWidth, float fHeight, bool bJump);
BLOCK *GetBlock(void);

#endif
