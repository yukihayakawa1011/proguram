//============================
//
//�G�Ɋւ��鏈��X(enemy.h)
//Author:���� �F�M
//
//============================

#ifndef _ENEMY_H_   //���̃}�N����`������Ă��Ȃ�������
#define _ENEMY_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define MAX_ENEMY   (128)   //�G�̍ő吔

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMEGE,
	ENEMYSTATE_MAX,
}ENEMYSTATE;

//�G�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;   //�ʒu
	ENEMYSTATE state;  //���
	//D3DXVECTOR3 rot;  //����
	D3DXVECTOR3 move;  //�ړ���
	int nType;         //���
	int nLife;		   //�̗�
	int nCounterState; //��ԊǗ��J�E���^�[
	bool bUse;         //�g�p���Ă��邩�ǂ���
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
Enemy *GetEnemy(void);
int ENEMY(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif