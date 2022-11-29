//============================
//
//������(key.cpp)
//Author:���� �F�M
//
//============================
#include "key.h"
#include "sound.h"
#include "fade.h"
#include "life.h"
#include "player.h"

//�}�N����`
#define NUM_PLACE (3)		//���̐�
#define KEY_DATA (10.0f)      //���̃T�C�Y
#define KEY_GET  (30.0f)  //���̓����蔻��

typedef enum
{
	KEYTYPE_RED = 0,
	KEYTYPE_BLUE,
	KEYTYPE_GREEN,
	KEYTYPE_MAX
}KEYTYPE;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureKey[KEYTYPE_MAX] = {};  //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffKey = NULL; //���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posKey[NUM_PLACE];  //���̈ʒu
KEYSTATE g_Key[NUM_PLACE];
int nKey = 3;

//�e�N�X�`���t�@�C����
const char *c_apFilenameKey[KEYTYPE_MAX] =
{
	"data/TEXTURE/keyred.png",
	"data/TEXTURE/keyblue.png",
	"data/TEXTURE/keygreen.png",
};

//=============================
//  ���̏�����
//=============================
void InitKey(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntKey;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		D3DXCreateTextureFromFile(pDevice,
			c_apFilenameKey[nCntKey],
			&g_apTextureKey[nCntKey]);
	}

	g_posKey[0] = D3DXVECTOR3(100.0f , 590.0f, 0.0f);  //�ʒu��������
	g_posKey[1] = D3DXVECTOR3(1200.0f , 370.0f, 0.0f);  //�ʒu��������
	g_posKey[2] = D3DXVECTOR3(1200.0f , 70.0f, 0.0f);  //�ʒu��������

	nKey = 3;

	//���̏���������
	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		g_Key[nCntKey].bUse = true;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * KEYTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffKey,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posKey[nCntKey].x - KEY_DATA, g_posKey[nCntKey].y - KEY_DATA, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posKey[nCntKey].x + KEY_DATA, g_posKey[nCntKey].y - KEY_DATA, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posKey[nCntKey].x - KEY_DATA, g_posKey[nCntKey].y + KEY_DATA, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posKey[nCntKey].x + KEY_DATA, g_posKey[nCntKey].y + KEY_DATA, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffKey->Unlock();
}

//=====================
//���̏I������
//=====================
void UninitKey(void)
{
	int nCntkey;

	//�e�N�X�`���̔j��
	for (nCntkey = 0; nCntkey < KEYTYPE_MAX; nCntkey++)
	{
		if (g_apTextureKey[nCntkey] != NULL)
		{
			g_apTextureKey[nCntkey]->Release();
			g_apTextureKey[nCntkey] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffKey != NULL)
	{
		g_pVtxBuffKey->Release();
		g_pVtxBuffKey = NULL;
	}
}

//==========================
//���̍X�V����
//=========================
void UpdateKey(void)
{
	FADE pFade;
	pFade = GetFade();
	LPDIRECT3DDEVICE9 pDevice;
	int nCntKey;
	Player *pPlayer = GetPlayer();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffKey->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{//�����g�p����Ă�����
			if (g_posKey[nCntKey].x + KEY_DATA + KEY_GET >= pPlayer->pos.x
				&& g_posKey[nCntKey].x - KEY_DATA - KEY_GET<= pPlayer->pos.x
				&& g_posKey[nCntKey].y + KEY_DATA + KEY_GET >= pPlayer->pos.y
				&& g_posKey[nCntKey].y - KEY_DATA - KEY_GET <= pPlayer->pos.y)
			{//�v���C���[�ƌ��̓����蔻��
				nKey--;

				g_Key[nCntKey].bUse = false;

				PlaySound(SOUND_LABEL_KEY);

			}
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffKey->Unlock();

}

//======================
//���̕`�揈��
//======================
void DrawKey(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntKey = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffKey, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntKey = 0; nCntKey < KEYTYPE_MAX; nCntKey++)
	{
		if (g_Key[nCntKey].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureKey[nCntKey]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntKey * 4, 2);
		}
	}
}

//==========================
//���̏���n������
//==========================
int GetKey(void)
{
	return nKey;
}