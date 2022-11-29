//============================
//
//�G�̏���(enemy.cpp)
//Author:���� �F�M
//
//============================
#include "enemy.h"
#include "player.h"
#include "sound.h"
#include "game.h"
//#include "particle.h"
//#include "effect.h"

//�}�N��
#define NUM_ENEMY (2)  //�G�̎��
#define X_DATA (1.0f) //X�̑��x
#define Y_DATA (2.0f) //Y�̑��x
#define TRY_LIFE       (1)	//�O�p�`�̗̑�
#define PARTICLE_LIFE   (100) //�p�[�e�B�N���̗̑�
#define MOVE_PARTICLE	(100.0f) //�p�[�e�B�N���̈ړ���
#define PARTICLE_USELIFE	(1)		 //�p�[�e�B�N���̃��C�t

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEnemy[MAX_ENEMY] = {};  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL; //���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];  //�G�̏��
int g_EnemyCount;         //�G�J�E���g
//float g_fLengthEnemy;
//float g_fAngleEnemy;
//int g_GetLife;   //�p�[�e�B�N���̃��C�t���󂯎��

//========================
//�G�̏���������
//========================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_EnemyCount = 0;  //������

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\zombie1.png",
		&g_pTextureEnemy[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\zombie1.png",
		&g_pTextureEnemy[1]);

	////�Ίp���̒������Z�o����
	//g_fLengthEnemy = sqrtf(BULLET_WINDS * BULLET_WINDS + BULLET_HEIGHT * BULLET_HEIGHT) * 0.5f;

	////�Ίp���̊p�x���Z�o����
	//g_fAngleEnemy = atan2f(BULLET_WINDS, BULLET_HEIGHT);

	//�G�̏���������
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //�ʒu��������

		g_aEnemy[nCntEnemy].nType = 0; //�G�̎�ނ�������

		g_aEnemy[nCntEnemy].nLife = 1;		   //�̗͂�������

		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	   //�ړ��ʂ�������

		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;  //���

		g_aEnemy[nCntEnemy].nCounterState = 0; //��ԊǗ��J�E���^�[

		g_aEnemy[nCntEnemy].bUse = false;  //�g�p���Ă��Ȃ���Ԃɂ���

		float g_fLengthEnemy = 0.0f;

		float g_fAngleEnemy = 0.0f;

		//g_GetCol = 1.0f;	//�ς��F���󂯎��ϐ�
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 10.0f, g_aEnemy[nCntEnemy].pos.y - 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 10.0f, g_aEnemy[nCntEnemy].pos.y - 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 10.0f, g_aEnemy[nCntEnemy].pos.y + 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 10.0f, g_aEnemy[nCntEnemy].pos.y + 10.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//========================
//�G�̏I������
//========================
void UninitEnemy(void)
{
	int nCntEnemy;

	//4���ڂ̃e�N�X�`���̔j��
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();
			g_pTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//=================================
//�G�̍X�V����
//=================================
void UpdateEnemy(void)
{
	int nCntEnemy = 0;
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g���Ă���ꍇ

				if (g_aEnemy[nCntEnemy].nType == 0)
				{
					//�G�̈ړ�����
					g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].move.x;

					//�ǂɓ��������璵�˕Ԃ鏈��
					if (g_aEnemy[nCntEnemy].pos.x <= 100 || g_aEnemy[nCntEnemy].pos.x >= 1200)
					{
						g_aEnemy[nCntEnemy].move.x *= -1;
					}

					if (g_aEnemy[nCntEnemy].pos.x <= 100)
					{
						//�e�N�X�`�����W�̐ݒ�
						pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
						pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
						pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
						pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
					}

					else if (g_aEnemy[nCntEnemy].pos.x >= 1200)
					{
						//�e�N�X�`�����W�̐ݒ�
						pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + 0.5f);
						pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + 0.5f);
						pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f + 0.5f);
						pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f + 0.5f);
					}
					
				}

				if (g_aEnemy[nCntEnemy].nType == 1)
				{
					//�G�̈ړ�����
					g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].move.x;

					//�ǂɓ��������璵�˕Ԃ鏈��
					if (g_aEnemy[nCntEnemy].pos.x <= 500 || g_aEnemy[nCntEnemy].pos.x >= 800)
					{
						g_aEnemy[nCntEnemy].move.x *= -1;
					}

					if (g_aEnemy[nCntEnemy].pos.x <= 500)
					{
						//�e�N�X�`�����W�̐ݒ�
						pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
						pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
						pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
						pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
					}

					else if (g_aEnemy[nCntEnemy].pos.x >= 800)
					{
						//�e�N�X�`�����W�̐ݒ�
						pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + 0.5f);
						pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + 0.5f);
						pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f + 0.5f);
						pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f + 0.5f);
					}
				}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y - 20.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 20.0f, g_aEnemy[nCntEnemy].pos.y - 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 20.0f, g_aEnemy[nCntEnemy].pos.y + 20.0f, 0.0f);

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:

				break;

			case ENEMYSTATE_DAMEGE:

				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				}
				break;
			}
		}

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//==========================
//�G�̕`�揈��
//==========================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	g_EnemyCount = 0;

	for (nCnt = 0; nCnt < NUM_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCnt].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2); //�v���~�e�B�u�̎��

			g_EnemyCount++;         //�G�J�E���g
		}

		else
		{

		}
	}

}
//====================
//�G�̐ݒ菈��
//====================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy = 0;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//�G���g�p����Ă��Ȃ�
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(X_DATA, Y_DATA, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y - 20.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 20.0f, g_aEnemy[nCntEnemy].pos.y - 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 20.0f, g_aEnemy[nCntEnemy].pos.y + 20.0f, 0.0f);

			g_aEnemy[nCntEnemy].bUse = true;

			switch (g_aEnemy[nCntEnemy].nType)
			{
			case 0:
				g_aEnemy[nCntEnemy].nLife = TRY_LIFE;

				break;

			case 1:
				g_aEnemy[nCntEnemy].nLife = TRY_LIFE;

				break;
			}
			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

}
//=================
//�G�̎擾
//=================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0]; //�G�̏��̐擪�A�h���X��n��
}
//====================
//�G�̐���Ԃ�
//===================
int ENEMY(void)
{
	return g_EnemyCount;
}
//==========================
//�G�̃q�b�g����
//==========================
void HitEnemy(int nCntEnemy, int nDamage)
{
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();
	LPDIRECT3DDEVICE9 pDevice;
	/*g_GetCol = ChangeEffect();*/

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	pVtx += nCntEnemy * 4;

	/*SetParticle(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, (g_aEnemy[nCntEnemy].pos.y + 50.0f), g_aEnemy[nCntEnemy].pos.z),
		D3DXVECTOR3(g_aEnemy[nCntEnemy].move.x, g_aEnemy[nCntEnemy].move.y + MOVE_PARTICLE, g_aEnemy[nCntEnemy].move.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		10.0f,
		PARTICLE_DAMAGE,
		PARTICLE_USELIFE);*/

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{//�G�̗̑͂�0�ɂȂ�����
		//�����̐ݒ�

 		g_aEnemy[nCntEnemy].bUse = false;

		for (int nCount = 0; nCount < NUM_ENEMY; nCount++, pEnemy++)
		{//�G���g�p����Ă���

			if (pPlayer->pos.x - 20.0f >= (pEnemy->pos.x - 20.0f) - ((pPlayer->pos.x - (pPlayer->pos.x - 20.0f)) * 2)
				&& pPlayer->pos.x + 20.0f <= (pEnemy->pos.x + 20.0f) + ((pPlayer->pos.x - (pPlayer->pos.x - 20.0f)) * 2)
				&& pPlayer->pos.y - 20.0f >= (pEnemy->pos.y - 20.0f) - ((pPlayer->pos.y - (pPlayer->pos.y - 20.0f)) * 2)
				&& pPlayer->pos.y + 20.0f <= (pEnemy->pos.y + 20.0f) + ((pPlayer->pos.y - (pPlayer->pos.y - 20.0f)) * 2))
			{//�v���C���[�ƓG����������	

			}
		}

		g_EnemyCount--;  //�G�̑��������炷
	}

	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;

		g_aEnemy[nCntEnemy].nCounterState = 5;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

}
