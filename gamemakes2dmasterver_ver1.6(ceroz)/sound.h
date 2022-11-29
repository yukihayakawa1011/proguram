//=============================================================================
//
// �T�E���h���� (sound.h)
// Author : ����@�F�M
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �^�C�g��BGM0
	SOUND_LABEL_BGM0015,		//�`���[�g���A��BGM
	SOUND_LABEL_BGM001,			//�Q�[��BGM
	SOUND_LABEL_BGM002,			//�Q�[���I�[�o�[BGM
	SOUND_LABEL_BGM003,			//���U���gBGM
	SOUND_LABEL_RANKING,		//�����L���O���BGM
	SOUND_LABEL_GAMEOVER,		//�Q�[���I�[�o�[�{�C�X
	SOUND_LABEL_DAMAGE,			//�_���[�W�{�C�X
	SOUND_LABEL_ENEMYDEATH,		//�G�̎��S�{�C�X
	SOUND_LABEL_HIT,			//�U���q�b�g�T�E���h
	SOUND_LABEL_KEY,			//�����Q�b�g�����Ƃ��̉�
	SOUND_LABEL_ENTER,			//�G���^�[�L�[���������Ƃ��̉�
	SOUND_LABEL_RUN,			//���鉹
	SOUND_LABEL_WINDOW,			//���K���X�̊���鉹
	SOUND_LABEL_TIMEUP,			//���Ԑ؂�ɂȂ����Ƃ��̃{�C�X
	SOUND_LABEL_MAX
	
	
	
	
	
	
	
	
	
	
	
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
