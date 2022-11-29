//============================
//
//���C���֐�(main.cpp)
//Author:���� �F�M
//
//============================ 

#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include"fade.h"
#include"sound.h"
#include "key.h"
#include "gameover.h"
#include "enemy.h"
#include "ranking.h"
#include "tutorial.h"

//�}�N����`
#define CLASS_NAME    "WindowClass"        //�E�C���h�E�N���X�̖��O
#define WINDOW_NAME   "ESCAPE" //�E�C���h�E�̖��O�i�L���v�V�����ɕ\���j

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void); 
void DrawEnemyCnt(void);

//�O���[�o���ϐ��錾
LPDIRECT3D9				g_pD3D = NULL;				//Direct3D�̃I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;		//Direct3D�f�o�C�X�̃|�C���^
LPD3DXFONT				g_pFont = NULL;             //�t�H���g�ւ̃|�C���^
int						g_nCountFPS = 0;            //FPS�J�E���^
int						g_nCntKey = 0;              //���J�E���^
bool					g_bDispDebug = false;		//�f�o�b�O�\����ON/OFF
MODE					g_mode = MODE_TITLE;			//���݂̃��[�h

//============================
//���C���֐�
//============================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�C���h�E�N���X�̍\���̂�錾
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),           //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,                   //�E�C���h�E�̃X�^�C��
		WindowProc,                  //�E�C���h�E�v���V�[�W��
		0,                           //�O�ɂ���i�ʏ�͒ʗp���Ȃ�)
		0,							//0�ɂ���i�ʏ�͒ʗp���Ȃ��j
		hInstance,					//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),  //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),  //�N���C�A���g�̈�̔w�i�F
		NULL,						//���j���[�o�[
		CLASS_NAME,                 //�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),
	};

	HWND hWnd;				//�E�C���h�E�n���h��(���ʎq)

	MSG msg;				//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0, 0, SCREEN_WINDTH, SCREEN_HEIGHT };

	RegisterClassEx(&wcex);			//�E�C���h�E�N���X�̓o�^

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h���쐬
	hWnd = CreateWindowEx(0,	//�g���E�C���h�E�X�^�C��
		CLASS_NAME,			//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,			//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,  //�E�C���h�E�X�^�C��
		CW_USEDEFAULT,      //�E�C���h�E�̍���X���W
		CW_USEDEFAULT,      //�E�C���h�E�̍���Y���W
		(rect.right - rect.left),     //�E�C���h�E�̕�
		(rect.bottom - rect.top),     //�E�C���h�E�̍���
		NULL,                 //�e�E�C���h�E�̃n���h��
		NULL,					//���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,			//�C���X�^���X�n���h��
		NULL);				    //�E�C���h�E�쐬�f�[�^

	DWORD dwCurrentTime;		//���ݎ���
	DWORD dwExecLastTime;       //�Ō�ɏ�����������
	DWORD dwFrameCount;			//�t���[���J�E���g
	DWORD dwFPSLASTTIME;        //�Ō��FPS���v����������

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ

		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;  //����������
	dwExecLastTime = timeGetTime();		//���ݎ������擾(�ۑ�)
	dwFrameCount = 0;  //����������
	dwFPSLASTTIME = timeGetTime();      //FPS���ݐ��l���擾(�ۑ�)

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);       //�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);				  //�N���C�A���g�̈���X�V

//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���

				break;

			}

			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg); //���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);  //�E�C���h�E�v���[�W���փ��b�Z�[�W�𑗏o
			}
		}

		else
		{//DirectX�̏���

			dwCurrentTime = timeGetTime();   //���ݎ������擾

			if ((dwCurrentTime - dwFPSLASTTIME) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLASTTIME);

				dwFPSLASTTIME = dwCurrentTime;   //FPS�𑪒肵��������ۑ�

				dwFrameCount = 0;   //�t���[���J�E���g���N���A

			}

			if (dwCurrentTime - dwExecLastTime >= (1000 / 60))
			{//60����1�b�o��

			dwExecLastTime = dwCurrentTime;  //�����J�n�̎���[���ݎ���]��ۑ�

			 //�X�V����						 
			Update();  

			//�`�揈��
			Draw();

			dwFrameCount++;         //�t���[���J�E���g�����Z

			}

		}

	}

	//�I������
	Uninit();

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;

}

//======================
//�E�C���h�E�v���[�W��
//======================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;  //�A��

	switch (uMsg)
	{
	case WM_DESTROY:   //�E�C���h�E�j���̃��b�Z�[�W

					   //WM_QUIT�Ƀ��b�Z�[�W�𑗂�
		PostQuitMessage(0);

		break;

	case WM_KEYDOWN:  //�L�[�������̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE:  //[ESC]�L�[�������ꂽ

			nID = MessageBox(hWnd, "�I�����܂���", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{

				//�E�C���h�E��j������
				DestroyWindow(hWnd);

			}

			else
			{
				return 0;   //0��Ԃ��Ȃ��ƏI�����Ă��܂�
			}

			break;
		}
		break;

	case WM_CLOSE:  //����{�^���������̃��b�Z�[�W

		nID = MessageBox(hWnd, "�I�����܂���", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{

			//�E�C���h�E��j������
			DestroyWindow(hWnd);

		}

		else
		{
			return 0;   //0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}

		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);  //����̏�����Ԃ�
}

//=============
//����������
//=============
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;            //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	 //�v���[���e�[�V�����p�����[�^

	 //Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));    //�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WINDTH;  //�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;  //�Q�[����ʃT�C�Y(����
	d3dpp.BackBufferFormat = d3ddm.Format;  //�o�b�N�΂ӂ��̌`��
	d3dpp.BackBufferCount = 1;				//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   //�_�u���o�b�t�@�̐؂�ւ�(�f���M���̓���)
	d3dpp.EnableAutoDepthStencil = TRUE;    //�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;			//�f�v�X�o�b�t�@��16bit���g��
	d3dpp.Windowed = bWindow;							//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;  //���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;  //�C���^�[�o��

															   //Direct3D�f�o�C�X�̍쐬
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{

			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);


	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	//�T�E���h�̏���������
	InitSound(hWnd);

	////���[�h�̐ݒ�
	//SetMode(g_mode);

	//�f�o�b�O�\���p�t�H���g�̍쐬
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�Q�[���p�b�h�̏���������
	InitGamepad();

	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	return S_OK;
}

//======================
//�I������
//======================
void Uninit(void)
{
	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�Q�[���p�b�h�̏I������
	UninitGamepad();

	//�^�C�g���̏I������
	UninitTitle();

	//�`���[�g���A���̏I������
	UninitTutorial();

	//�Q�[���̏I������
	UninitGame();

	//���U���g�̏I������
	UninitResult();

	//�Q�[���I�[�o�[�̏I������
	UninitGameover();

	//�����L���O�̏I������
	UninitRanking();

	//�t�F�[�h�̏I������
	UninitFade();

	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();

		g_pFont = NULL;
	}

	//�T�E���h�̒�~
	StopSound();

	//�T�E���h�̏I������
	UninitSound();

	//�e��I�u�W�F�N�g�̏I������
	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;

	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
//==========================
//�X�V����
//==========================
void Update(void)
{
	//�L�[�{�[�h�̍X�V
	UpdateKeyboard();

	//�Q�[���p�b�h�̍X�V
	UpdateGamepad();

	switch (g_mode)
	{
	case MODE_TITLE:
			UpdateTitle();
		break;

	case MODE_TUTORIAL:
		UpdateTutorial();
		break;

	case MODE_GAME:
		UpdateGame();
		break;

	case MODE_RESULT:
		UpdateResult();
		break;

	case MODE_GAMEOVER:
		UpdateGameover();
		break;

	case MODE_RANKING:
		UpdateRanking();
		break;
	}

	//�t�F�[�h�̍X�V
	UpdateFade();
}

//======================
//�`�揈��
//======================
void Draw(void)
{//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)

	g_pD3DDevice->Clear(0,NULL,(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

//�`��J�n
   if (SUCCEEDED(g_pD3DDevice->BeginScene()))
   {//�`�揈�������������ꍇ
	//�e��I�u�W�F�N�g�̕`�揈��

	   switch (g_mode)
	   {
	   case MODE_TITLE:
		   DrawTitle();
		   break;

	   case MODE_TUTORIAL:
			   DrawTutorial();
			   break;

	   case MODE_GAME:
		   DrawGame();
		   break;

	   case MODE_RESULT:
		   DrawResult();
		   break;

	   case MODE_GAMEOVER:
		   DrawGameover();
		   break;

	   case MODE_RANKING:
		   DrawRanking();
		   break;
	   }

	   //�t�F�[�h�̕`�揈��
	   DrawFade();

	//�`��I��
	g_pD3DDevice->EndScene();

   }

   //�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
   g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//======================
//�f�o�C�X�̎擾
//======================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//======================
//FPS�̕\��
//======================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WINDTH,SCREEN_HEIGHT };

	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//======================
//����\��
//======================
void DrawEnemyCnt(void)
{
	RECT rect = { 0,20,SCREEN_WINDTH,SCREEN_HEIGHT };

	char aStr[256];
	int Enemy = ENEMY();
	int g_nCntKey = GetKey();

	//������ɑ��
	wsprintf(&aStr[0], "\n\n[���̐�] : %d\n\n[�G�̐�] : %d \n\n[�L�[�{�[�h]\n\n���ړ� : A\n�E�ړ� : D\n�W�����v : J\n\n�U�� : SPACE\n\n[�Q�[���p�b�h]\n\n�ړ� : �X�e�B�b�N\n�W�����v : B\n\n�U�� : A",g_nCntKey, Enemy);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255 , 255, 255, 255));

}

//====================
//���[�h�̐ݒ菈��
//====================
void SetMode(MODE mode)
{
	//�I������
	switch (mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_TUTORIAL:
		UninitTutorial();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	case MODE_GAMEOVER:
		UninitGameover();
		break;

	case MODE_RANKING:
		UninitRanking();
		break;
	}

	//����������
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_TUTORIAL:
		InitTutorial();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;

	case MODE_GAMEOVER:
		InitGameover();
		break;

	case MODE_RANKING:
		InitRanking();
		break;
	}

	g_mode = mode; //���[�h���擾����
}

//=================
//���[�h�̎擾
//=================
MODE GetMode(void)
{
	return g_mode;
}