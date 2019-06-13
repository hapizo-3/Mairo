#include "DxLib.h"

//�f�o�b�O���[�h
//#define _DEBUGMODE

//�t���[�����[�g�萔( 60 )
#define	_FRAMERATE_60	60

/*****      �t�H���g�T�C�Y�萔      *****/
#define _FONTSIZE_SS		10	//�t�H���gSS�T�C�Y
#define _FONTSIZE_S			20	//�t�H���gS�T�C�Y
#define _FONTSIZE_M			32	//�t�H���gM�T�C�Y
#define _FONTSIZE_L			48	//�t�H���gL�T�C�Y
#define _FONTSIZE_LL		64	//�t�H���gLL�T�C�Y

//�Q�[����ԕϐ�
static int GAMESTATE;

//�t���[�����[�g�n�ϐ�
static int RefreshRate;

/*****      �Q�[�����[�h�񋓑�      *****/
typedef enum GAME_MODE {
	GAME_TITLE,			//�^�C�g��
	GAME_HELP,			//�w���v
	GAME_LEVEL,			//��Փx
	GAME_INIT,			//������
	GAME_MAIN,			//���C��
	GAME_WIN,			//�������
	GAME_LOSE,			//�s�k�҉��
	GAME_END,			//�G���h����
	GAME_INPUTRANKING,	//�����L���O������
	GAME_RANKING,		//�����L���O���
	END = 99			//�G���h
};

/*****      �摜�\����      *****/
typedef struct PICTURE {
	int Picture;
};
PICTURE Pic;	//�摜�\���̐錾

/*****      �摜�\����      *****/
typedef struct SOUND {
	int Sound;
};
SOUND Sound;		//���y�\���̐錾

/*****      �t���[�����[�g�\����      *****/
typedef struct FRAMERATE_CONTROL {
	int mStartTime;
	int mCount;
	float mFps;
	int ReFreshRateState;
};
FRAMERATE_CONTROL FR_Control = { 0, 0, 0.0, 0 };	//�t���[�����[�g����\���̐錾

/*****      �L�[����\����      *****/
typedef struct OPERATE {
	//KeyInput
	int OldK;
	int NowK;
	int Kflg;
} OPERATE;

OPERATE opt;

/****************************************************/
/*****											*****/
/*****			  �֐��v���g�^�C�v�錾			*****/
/*****											*****/
/****************************************************/

//�t���[�����[�g����֐�
static bool FR_Update( );
static void FR_Draw( );
static void FR_Wait( );

void DrawTitle();
void GameInit();
void GameMain();
void DrawEnd();

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {

	GAMESTATE = GAME_TITLE;
	SetMainWindowText( "Aiueo" );

	ChangeWindowMode( TRUE );
	SetGraphMode( 640, 480, 32 );
	SetDrawScreen( DX_SCREEN_BACK );

	if ( DxLib_Init() == -1 )	return -1;

	while ( ProcessMessage() == 0 && ClearDrawScreen() == 0 && GAMESTATE != 99 ) {
	
		opt.OldK = opt.NowK;
		opt.NowK = GetJoypadInputState( DX_INPUT_KEY_PAD1 );
		opt.Kflg = opt.NowK & ~opt.OldK;



		switch( GAMESTATE ) {

			case GAME_TITLE:
			case GAME_INIT:
			case GAME_MAIN:
			case GAME_END:
				break;
		}
	
		FR_Update();
		#ifdef _DEBUGMODE
			FR_Draw();
		#endif
		ScreenFlip();
		FR_Wait();

	}
	
	DxLib_End();
	return 0;

}

/******�@�@�@�@�@�@�@�t���[��������֐�         ******/
static bool FR_Update( ) {
	if ( FR_Control.mCount == 0 ) {
		FR_Control.mStartTime = GetNowCount();
	}
	if ( FR_Control.mCount == RefreshRate ) {
		int t = GetNowCount();
		FR_Control.mFps = 1000.f / ( ( t - FR_Control.mStartTime ) / ( float )RefreshRate );
		FR_Control.mCount = 0;
		FR_Control.mStartTime = t;
	}
	FR_Control.mCount++;
	return true;
}

/******�@�@�@�@�@�@�@�t���[�����[�g�`��         ******/
static void FR_Draw( ) {
	
	SetFontSize( _FONTSIZE_S );
	DrawFormatString( 0, 0, 0xff0000, "%.1f", FR_Control.mFps );

}

/******�@�@�@�@�@�@�@ �����҂��֐�          ******/
static void FR_Wait( ) {
	int tookTime = GetNowCount() - FR_Control.mStartTime;
	int waitTime = FR_Control.mCount * 1000 / _FRAMERATE_60 - tookTime;

	if ( waitTime > 0 ) {
		Sleep( waitTime );
	}
}

void DrawTitle() {
	DrawFormatString( 0, 0, 0xffffff, "A" );
}