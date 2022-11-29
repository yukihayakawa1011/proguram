//============================
//
//�v���C���[����(player.cpp)
//Author:���� �F�M
//
//============================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "black.h"
#include "life.h"
#include "game.h"
#include "enemy.h"
#include "edit.h"
#include "sound.h"
#include "pattack.h"

//�}�N��
#define Press_PLAYER (2.0f)
#define PLAYER_JUNP  (20.0f)
#define PLAYER_HEIGHT (19.0f) 
#define PLAYER_WIDTH (9.0f)
#define PLAYER_HITSPACEX (10.0f) //�v���C���[�̓����蔻��X
#define PLAYER_HITSPACEY (10.0f) //�v���C���[�̓����蔻��Y
#define PLAYER_ATTACKSPACE (20.0f) //�v���C���[�̍U������
#define ENEMY_HITSPACE (10.0f)  //�G�̓����蔻��
#define ENEMY_DAMAGESPACE (20.0f) //�G�̍U�����󂯂�͈�


//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;        //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;  //���_�o�b�t�@�ւ̃|�C���^
Player g_player;						//�v���C���[�̏��
int g_nCounterAnimPlayer;				//�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer;					//�A�j���[�V�����p�^�[��No.               
D3DXVECTOR3 g_moverotPlayer;				//�����̈ړ���
float g_fLengthPlayer;						//�Ίp���̒���
float g_movefLengthPlayer;                   //�Ίp���̈ړ���
float g_fAnglePlayer;						//�Ίp���̊p�x

//======================
//�v���C���[�̏���������
//======================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\playerwalkanim.png",
		&g_pTexturePlayer);

	g_nCounterAnimPlayer = 0;  //�J�E���^�[������������
	g_nPatternAnimPlayer = 0;	   //�p�^�[��������������
	g_player.pos = D3DXVECTOR3(50.0,700.0, 0.0);  //���݂̈ʒu��������
	g_player.posold = D3DXVECTOR3(50.0, 700.0, 0.0);  //�Â��ʒu��������
	g_player.move = D3DXVECTOR3(0.0, 0.0, 0.0);      //�ړ��ʂ�������
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����������������(z�l���g�p)
	g_player.bJump = false;							//�W�����v����
	g_moverotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�����̈ړ��p��������
	g_movefLengthPlayer = 0.0f; //�Ίp���̈ړ��ʂ�������
	g_player.bUse = true;  //�g���Ă��邩�ǂ���
	g_player.nAnimCounter = 0; //�A�j���[�V�����̃J�E���^�[��������
	g_player.fWidth = 20.0f; //�v���C���[�̕���������
	g_player.fHeight = 50.0f; //�v���C���[�̍�����������
	g_player.nLife = 3; //�v���C���[�̗̑͂�������
	g_player.nCounterState = 300;  //��ԊǗ��̃J�E���^�[��������
	g_player.state = PLAYERSTATE_NORMAL;  //�v���C���[�̏�Ԃ�������

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, 0.0f);
	
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

}

//======================
//�v���C���[�̏I������
//======================
void UninitPlayer(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//==============================
//�v���C���[�̍X�V����
//==============================
void UpdatePlayer(void)
{
	g_player.posold = g_player.pos; //�O��̈ʒu���L�^

	Enemy *pEnemy = GetEnemy();

	PATTACK * pPattack = GetPattack();

	int nCntEnemy;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//�ǂ̓����蔻��
	if (g_player.pos.x > 1257)
	{
		g_player.pos.x = 1257;
		g_player.move.x = 0;
	}

	else if (g_player.pos.x < 20)
	{
		g_player.pos.x = 20;
		g_player.move.x = 0;
	}

	if (g_player.pos.y > 725)
	{
		g_player.pos.y = 680;
		g_player.move.y = 0;
	}

	else if (g_player.pos.y <50)
	{
		g_player.pos.y = 50;
		g_player.move.y = 0;
	}

	g_player.nCounterAnim++;			//�J�E���^�[�����Z

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardPress(DIK_A) == true || GetGameStickL_X_Press(BUTTON_STICK_LX, 0)  <= -1)
	{
		g_player.move.x -= 0.4f;
		/*g_player.nPatternAnim = 0;*/
		
			g_player.nAnimCounter = 1;

			//g_player.nCounterAnim = 0; //�J�E���^�[������������

			if ((g_player.nCounterAnim % 10) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;		//�p�^�[��NO.���X�V����

				/*PlaySound(SOUND_LABEL_RUN);*/
			}
	}

	else if (GetKeyboardPress(DIK_D) == true || GetGameStickL_X_Press(BUTTON_STICK_LX, 0) >= 1)
	{
		g_player.move.x += 0.4f;

		g_player.nAnimCounter = 0;

		if ((g_player.nCounterAnim % 10) == 0)
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;		//�p�^�[��NO.���X�V����

			/*PlaySound(SOUND_LABEL_RUN);*/
		}
	}

	if (GetKeyboardPress(DIK_D) == true && GetKeyboardPress(DIK_A) == true)
	{
		g_player.move.x = 0.0f;
		g_player.nPatternAnim = 0;
	}

	else
	{
		if (g_player.nPatternAnim != 0)
		{
			if ((g_player.nCounterAnim % 8) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;		//�p�^�[��NO.���X�V����
			}
		}
	}

	if (g_player.nAnimCounter == 0)
	{//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_player.nPatternAnim) * 0.25f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.25f + (g_player.nPatternAnim) * 0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_player.nPatternAnim) * 0.25f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.25f + (g_player.nPatternAnim) * 0.25f, 0.5f);
		
			//�U������
			if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
			{
				pPattack->bUse = true;
				g_player.bUse = false;

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (g_player.pos.x - PLAYER_ATTACKSPACE >= (pEnemy->pos.x - ENEMY_DAMAGESPACE) - ((g_player.pos.x - (g_player.pos.x - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.x + PLAYER_ATTACKSPACE <= (pEnemy->pos.x + ENEMY_DAMAGESPACE) + ((g_player.pos.x - (g_player.pos.x - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.y - PLAYER_ATTACKSPACE >= (pEnemy->pos.y - ENEMY_DAMAGESPACE) - ((g_player.pos.y - (g_player.pos.y - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.y + PLAYER_ATTACKSPACE <= (pEnemy->pos.y + ENEMY_DAMAGESPACE) + ((g_player.pos.y - (g_player.pos.y - PLAYER_ATTACKSPACE)) * 2))
					{

						if (pEnemy->bUse == true)
						{
							HitEnemy(nCntEnemy, 1);
							PlaySound(SOUND_LABEL_HIT);
							PlaySound(SOUND_LABEL_ENEMYDEATH);
						}
					}
				}
			}

			if (pPattack->bUse == true)
			{
				//�E���ɍU���A�j���[�V����
				RightPattack();


				//���p�^�[�����𒴂���
				if (pPattack->nPatternAnim == 3)
				{
					pPattack->nPatternAnim = 0;
					pPattack->nCounterAnim = 0;

					pPattack->bUse = false;  //�g�p���Ă��Ȃ���Ԃɂ���
					g_player.bUse = true;      //�v���C���[���g�p���Ă����Ԃɂ���
				}
			}

		}

		else if (g_player.nAnimCounter == 1)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_player.nPatternAnim) * 0.25f, 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.25f + (g_player.nPatternAnim) * 0.25f, 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_player.nPatternAnim) * 0.25f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.25f + (g_player.nPatternAnim) * 0.25f, 1.0f);

			//�U������
			if (GetKeyboardTrigger(DIK_SPACE) == true || GetGamepadTrigger(BUTTON_A, 0) == true)
			{
				pPattack->bUse = true;
				g_player.bUse = false;

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (g_player.pos.x - PLAYER_ATTACKSPACE >= (pEnemy->pos.x - ENEMY_DAMAGESPACE) - ((g_player.pos.x - (g_player.pos.x - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.x + PLAYER_ATTACKSPACE <= (pEnemy->pos.x + ENEMY_DAMAGESPACE) + ((g_player.pos.x - (g_player.pos.x - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.y - PLAYER_ATTACKSPACE >= (pEnemy->pos.y - ENEMY_DAMAGESPACE) - ((g_player.pos.y - (g_player.pos.y - PLAYER_ATTACKSPACE)) * 2)
						&& g_player.pos.y + PLAYER_ATTACKSPACE <= (pEnemy->pos.y + ENEMY_DAMAGESPACE) + ((g_player.pos.y - (g_player.pos.y - PLAYER_ATTACKSPACE)) * 2))
					{
						if (pEnemy->bUse == true)
						{
							HitEnemy(nCntEnemy, 1);
							PlaySound(SOUND_LABEL_HIT);
							PlaySound(SOUND_LABEL_ENEMYDEATH);
						}
					}
				}
			}

			if (pPattack->bUse == true)
			{
				//�����ɍU��
				LeftPattack();

				//���p�^�[�����𒴂���
				if (pPattack->nPatternAnim == 3)
				{
					pPattack->nPatternAnim = 0;
					pPattack->nCounterAnim = 0;

					pPattack->bUse = false;  //�g�p���Ă��Ȃ���Ԃɂ���
					g_player.bUse = true; //�v���C���[�̕`�������
				}
			}

		}

	

	//�W�����v����
	if (GetKeyboardTrigger(DIK_J) == true || GetGamepadTrigger(BUTTON_B, 0) == true)
	{
		if (g_player.bJump == false)
		{
			g_player.bJump = true;

			g_player.move.y -= PLAYER_JUNP;
		}
	}

	//�d�͏���
	g_player.move.y += Press_PLAYER;

	//�ʒu�����X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//�ړ��ʂ��X�V
	g_player.move.x += (0.0f - g_player.move.x) * 0.1f;

	//�u���b�N�Ƃ̓����蔻��
	if (colisionBlock(&g_player.pos, &g_player.posold, &g_player.move,g_player.fWidth - PLAYER_WIDTH,g_player.fHeight - PLAYER_HEIGHT, g_player.bJump) == true)
	{
		g_player.bJump = false;  //���n��Ԃɂ���
	}
	else
	{
		g_player.bJump = true;  //���n��Ԃɂ���
	}

	if (g_player.pos.y >= 725.0f)
	{
		g_player.bJump = false;
		g_player.move.y = 0.0f;
		g_player.pos.y = 725.0f;
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y - g_player.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - g_player.fWidth, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + g_player.fWidth, g_player.pos.y, 0.0f);

	CollisionPlayer();

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		break;

	case PLAYERSTATE_DAMAGE:

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_player.state = PLAYERSTATE_MUTEKI;

		break;

	case PLAYERSTATE_DEATH:

		g_player.bUse = false;

		break;

	case PLAYERSTATE_MUTEKI:

			g_player.nCounterState--;

			if (g_player.nCounterState <= 0)
			{
				g_player.state = PLAYERSTATE_NORMAL;
			}

			break;

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//======================
//�v���C���[�̕`�揈��
//======================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_player.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(NULL, g_pTexturePlayer);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��
	}
}

//========================
//�v���C���[�̃q�b�g����
//========================
void HitPlayer(int nDamage)
{

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);


	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{
		g_player.bUse = false;

		g_player.state = PLAYERSTATE_DEATH;
		g_player.bDisp = false;

		//�Q�[����Ԃ̐ݒ�
		SetGameState(GAMESTATE_GAMEOVER, 120);
	}

	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;

		g_player.nCounterState = 60;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

}

//======================
//�v���C���[�̓����蔻��
//======================
void CollisionPlayer(void)
{
	Enemy *pEnemy = GetEnemy();
	int nCntEnemy;

	if (g_player.bUse == true)
	{//	�v���C���[���g�p����Ă���

		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{//�G���g�p����Ă���

			if (pEnemy->bUse == true && g_player.state == PLAYERSTATE_NORMAL)
			{

				if (g_player.pos.x - PLAYER_HITSPACEX >= (pEnemy->pos.x - ENEMY_HITSPACE) - ((g_player.pos.x - (g_player.pos.x - PLAYER_HITSPACEX)) * 2)
					&& g_player.pos.x + PLAYER_HITSPACEX <= (pEnemy->pos.x + ENEMY_HITSPACE) + ((g_player.pos.x - (g_player.pos.x - PLAYER_HITSPACEX)) * 2)
					&& g_player.pos.y - PLAYER_HITSPACEY >= (pEnemy->pos.y - ENEMY_HITSPACE) - ((g_player.pos.y - (g_player.pos.y - PLAYER_HITSPACEY)) * 2)
					&& g_player.pos.y + PLAYER_HITSPACEY <= (pEnemy->pos.y + ENEMY_HITSPACE) + ((g_player.pos.y - (g_player.pos.y - PLAYER_HITSPACEY)) * 2))
				{//�v���C���[�ƓG����������
				 //�v���C���[�̃q�b�g����
  				 HitPlayer(1);

				 PlaySound(SOUND_LABEL_HIT);

 				PlaySound(SOUND_LABEL_DAMAGE);
				}
			}

			else
			{

			}
		}
	}
}

//============================
//�v���C���[�𖾂��n��
//============================
Player *GetPlayer(void)
{
	return &g_player;
}


