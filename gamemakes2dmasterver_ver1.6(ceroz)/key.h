//===============================
//
//������(key.h)
//
//===============================
#ifndef _KET_H_   //���̃}�N����`������Ă��Ȃ�������
#define _KET_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

typedef struct
{
	bool bUse;
}KEYSTATE;

//�v���g�^�C�v�錾
void InitKey(void);
void UninitKey(void);
void UpdateKey(void);
void DrawKey(void);
int GetKey(void);

#endif
