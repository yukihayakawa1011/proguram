//===============================
//
//�^�C������(time.h)
//
//===============================
#ifndef _TIME_H_   //���̃}�N����`������Ă��Ȃ�������
#define _TIME_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�v���g�^�C�v�錾
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetTime(int nTime);
void SetPosTime(D3DXVECTOR3 pos, float fWindth, float fHeight);
int GetTime(void);

#endif
