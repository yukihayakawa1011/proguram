//============================
//
//�S�[������(goal.h)
//Author:���� �F�M
//
//============================

#ifndef _GOAL_H_   //���̃}�N����`������Ă��Ȃ�������
#define _GOAL_H   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�S�[���\����
typedef struct
{
	D3DXVECTOR3 pos;
	bool bUse;
}GOAL;

//�v���g�^�C�v�錾
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
GOAL GetGoal(void);

#endif