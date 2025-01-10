#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Skydome.h"
#include"Stage.h"
#include"Input.h"
#include"Camera.h"
#include"Enemy.h"
#include"HitChecker.h"
#include"EnemyAttackRangeChecker.h"
#include"Player.h"

enum STATE
{
	STATE_INIT,
	STATE_TITLE,		// �^�C�g��.
	STATE_READY,        //����
	STATE_COUNTDOWN,	//�Q�[�����n�܂�܂ł̃J�E���g
	STATE_GAME,			// �Q�[����.
	STATE_END,			//����Ă�����
	STATE_GAMEOVER,		// �Q�[���I�[�o�[.
};

const int HITCHECK_NUM = 2;

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(1600, 900, 32);
	ChangeWindowMode(TRUE);

	// DX���C�u����������������B
	if (DxLib_Init() == -1) return -1;

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effkseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// DirectX9���g�p����悤�ɂ���B(DirectX11����)
// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	SetDrawScreen(DX_SCREEN_BACK);	// ����ʂ�`��Ώۂɂ���
	SetUseZBufferFlag(TRUE);		// �y�o�b�t�@���g�p����
	SetWriteZBufferFlag(TRUE);		// �y�o�b�t�@�ւ̏������݂��s��
	SetUseBackCulling(TRUE);		// �o�b�N�J�����O���s��

	// 1�b�Ԃɏ�������t���[������ݒ�(60FPS)
	const int TARGET_FPS = 60;
	const int FRAME_TIME = 1000 / TARGET_FPS;  // 1�t���[��������̗��z�I�Ȏ��� (�~���b)

	// ********** �t�H���g�̃��[�h **********
	LPCSTR font_path = "Data/Font/LightNovelPOPv2.otf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	//// �t�H���g�̕ύX
	ChangeFont("���m�xPOP v2", DX_CHARSET_DEFAULT);

	// �C���X�^���X����
	Skydome* dome = new Skydome();
	Stage* stage = new Stage();
	Input* input = new Input();
	Camera* camera = new Camera();
    Enemy* enemy = new Enemy();
	Player* player = new Player();
	HitChecker *hitchecker[HITCHECK_NUM];
	hitchecker[0] = new HitChecker();
	hitchecker[1] = new EnemyAttackRangeChecker();

	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	LONGLONG frameTime = 0;

	int gameStatus = STATE_INIT;	//���݂̃Q�[�����̏��
	bool debugPauseFlag = false;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �t���[���J�n���̎��Ԃ��擾
		int startTime = GetNowCount();
		// �ڂ��񂨂�����
		if (CheckHitKey(KEY_INPUT_P))
		{
			debugPauseFlag = true;
		}
		while (debugPauseFlag)
		{
			WaitTimer(2);
			// �ڂ��񂨂�����
			if (CheckHitKey(KEY_INPUT_O))
			{
				debugPauseFlag = false;
			}
		}

		if (debugPauseFlag == false)
		{
			//�S�Ă̏�����
			if (gameStatus == STATE_INIT)
			{
				stage->Load();
				enemy->Load();
				player->Load();
				camera->Load();

				//�Q�[����ԕω�
				gameStatus = STATE_TITLE;
			}

			//�^�C�g�����
			if (gameStatus == STATE_TITLE)
			{

				ClearDrawScreen();

				//�`��
				SetFontSize(40);
				DrawFormatString(0, 0, Pallet::AliceBlue.GetHandle(), "title");

				// �Q�[����ԕω�
				if (CheckHitKey(KEY_INPUT_RETURN))
				{
					gameStatus = STATE_READY;
				}

			}
			//�`���[�g���A�����
			if (gameStatus == STATE_READY)
			{

				//�`��

				// �Q�[����ԕω�
				gameStatus = STATE_COUNTDOWN;
			}
			//�Q�[�����n�܂�܂ł̃J�E���g�_�E��
			if (gameStatus == STATE_COUNTDOWN)
			{
				gameStatus = STATE_GAME;
			}
			//�Q�[����
			if (gameStatus == STATE_GAME)
			{

				//�Q�[���V�[���̐���
				stage->Update();
				//�p�b�h�̐���
				input->Update();
				//�����蔻�萧��
				for (int i = 0; i < HITCHECK_NUM; i++)
				{
					hitchecker[i]->Update(*player, *enemy);
				}
				// �v���C���[����
				//EnemyAttackRangeChecker test;
				//const auto enemyattackRangeHitChecker = static_cast<const EnemyAttackRangeChecker*>(hitchecker[1]);
				enemy->Update(*player, *static_cast<const EnemyAttackRangeChecker*>(hitchecker[1]));

				player->Update(*input);
				// �J�����̐���
				camera->Update(*player);
				// �X�J�C�h�[������
				dome->SkydomeUpdate();

				// ��ʂ�����������
				ClearDrawScreen();

				// �`��
				dome->SkydomeDraw();
				stage->Draw();
				enemy->Draw();
				player->Draw();
				for (int i = 0; i < HITCHECK_NUM; i++)
				{
					hitchecker[i]->DrawCircle();
				}
			}
			//�Q�[���I�[�o�[���o
			if (gameStatus == STATE_END)
			{

				// ��ʂ�����������
				ClearDrawScreen();

			}

			//�Q�[�����U���g
			if (gameStatus == STATE_GAMEOVER)
			{
				// ��ʂ�����������
				ClearDrawScreen();
				//�`��

				// �Q�[����ԕω�
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_INIT;
				}
			}
		}

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		// �t���[���I�����̎��Ԃ��擾
		int endTime = GetNowCount();

		// �t���[���������Ԃ��v�Z
		int elapsedTime = endTime - startTime;

		// �����������I������ꍇ�A�c�莞�ԑҋ@����
		if (elapsedTime < FRAME_TIME)
		{
			// �c�莞�ԑҋ@
			WaitTimer(FRAME_TIME - elapsedTime);
		}
	}

	// Effekseer���I������B
	Effkseer_End();
	// ��n��
	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}