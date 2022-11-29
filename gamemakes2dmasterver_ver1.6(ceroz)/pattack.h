//============================
//
//�U������(pattack.h)
//Author:���� �F�M
//
//============================

#ifndef _PATTACK_H_   //���̃}�N����`������Ă��Ȃ�������
#define _PATTACK_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�U���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //�ʒu
	D3DXCOLOR col;    //�F
	int nCounterAnim;  //�A�j���[�V�����J�E���^�[
	int nPatternAnim;  //�A�j���[�V�����p�^�[��No.
	bool bUse;         //�g�p���Ă��邩�ǂ���
}PATTACK;

//�v���g�^�C�v�錾
void InitPattack(void);
void UninitPattack(void);
void UpdatePattack(void);
void DrawPattack(void);
void SetPattack(D3DXVECTOR3 pos);
PATTACK *GetPattack(void);
void RightPattack(void);
void LeftPattack(void);

#endif
