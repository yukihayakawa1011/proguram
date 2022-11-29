//============================
//
//�t�F�[�h����(fade.h)
//Author:���� �F�M
//
//============================

#ifndef _FADE_H_   //���̃}�N����`������Ă��Ȃ�������
#define _FADE_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�t�F�[�h�̏��
typedef enum
{
	FADE_NONE = 0,  //�������Ă��Ȃ�
	FADE_IN,    //�t�F�[�h�C��
	FADE_OUT,	//�t�F�[�h�A�E�g���
	FADE_MAX	
}FADE;

//�v���g�^�C�v�錾
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);

#endif

