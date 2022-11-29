//============================
//
//�v���C���[�̏���(player.h)
//Author:���� �F�M
//
//============================

#ifndef _PLAYER_H_   //���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_NORMAL = 0,     //�ʏ���
	PLAYERSTATE_DAMAGE,     //�_���[�W
	PLAYERSTATE_MUTEKI,		//���G���
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;  //���݂̈ʒu
	D3DXVECTOR3 posold; //�Â��ʒu
	D3DXVECTOR3 rot;  //����
	D3DXVECTOR3 move;  //�ړ���
	int nCounterAnim; //�A�j���[�V�����J�E���^�[
	int nPatternAnim; //�A�j���[�V�����p�^�[��
	bool bJump;		  //�W�����v�����ǂ���
	float fWidth;    //�v���C���[��
	float fHeight;   //�v���C���[����
	int nLife;		  //�̗�
	bool bUse;   //�g�p���Ă��邩�ǂ���
	int nAnimCounter;
	PLAYERSTATE state;  //�v���C���[�̏��
	int nCounterState;	//��ԊǗ��J�E���^�[
	bool bDisp;			//�\�����邩���Ȃ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
void CollisionPlayer(void);
Player *GetPlayer(void);

#endif
