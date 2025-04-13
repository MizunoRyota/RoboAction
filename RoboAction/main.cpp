#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"GameManager.h"
#include"Effect.h"
#include"Sound.h"
#include"Pallet.h"
#include"Skydome.h"
#include"Stage.h"
#include"EnergyBall.h"
#include"Input.h"
#include"Camera.h"
#include"Enemy.h"
#include"HitChecker.h"
#include"EnemyAttackRangeChecker.h"
#include"Player.h"
#include"UI.h"
#include"OnAttackedPlayerHit.h"
#include"OnAttackedEnemyHit.h"
#include"OnGimmick.h"
#include"Gimmick.h"

enum STATE
{
	STATE_LOAD,			//���[�h.
	STATE_INIT,			//������.
	STATE_TITLE,		//�^�C�g��.
	STATE_READY,        //����
	STATE_TUTORIAL,     //����
	STATE_LESSON,		//�Q�[�����n�܂�܂ł̃J�E���g
	STATE_GAME,			//�Q�[����.
	STATE_READYGAMEOVER,//����Ă�����
	STATE_READYCLEAR,	//�N���A���
	STATE_GAMEOVER,		//�Q�[���I�[�o�[.
	STATE_CLEAR,		//�Q�[���N���A.
};

const int HITCHECK_NUM = 2;

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(1600, 900, 32);
	ChangeWindowMode(FALSE);

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
	const int GimmickNum = 4;
	// ********** �t�H���g�̃��[�h **********
	LPCSTR font_path = "Data/Font/LightNovelPOPv2.otf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	//// �t�H���g�̕ύX
	ChangeFont("���m�xPOP v2", DX_CHARSET_DEFAULT);

	// �C���X�^���X����
	GameManager* gameManager = new GameManager();
	Sound* sound = new Sound();
	Effect* effect = new Effect();
	Skydome* dome = new Skydome();
	Stage* stage = new Stage();
    Energy* energy = new Energy();
	Input* input = new Input();
	Camera* camera = new Camera();
	Enemy* enemy = new Enemy();
	Player* player = new Player();
	UI* ui = new UI();
	HitChecker* hitchecker[HITCHECK_NUM];
	hitchecker[0] = new HitChecker();
	hitchecker[1] = new EnemyAttackRangeChecker();
	OnAttackedPlayer* onattackply = new OnAttackedPlayer();
	OnAttackedEnemy* onattackedenemy = new OnAttackedEnemy();
	OnGimmick* ongimmick[GimmickNum];
	ongimmick[0] = new OnGimmick();
	ongimmick[1] = new OnGimmick();
	ongimmick[2] = new OnGimmick();
	ongimmick[3] = new OnGimmick();

	Gimmick* gimmick[GimmickNum];
	gimmick[0] = new Gimmick(VGet(-6.0f, 1.0f, -6.0f));
	gimmick[1] = new Gimmick(VGet(6.0f, 1.0f, -6.0f));
	gimmick[2] = new Gimmick(VGet(-6.0f, 1.0f, 6.0f));
	gimmick[3] = new Gimmick(VGet(6.0f, 1.0f, 6.0f));

	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	LONGLONG frameTime = 0;

	int gameStatus = STATE_LOAD;	//���݂̃Q�[�����̏��
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
			if (gameStatus == STATE_LOAD)
			{
				//effect->StopDraw();
				sound->Delete();
				stage->Load();
				sound->Load();
				enemy->Load();
				for (int i = 0; i < GimmickNum; i++)
				{
					gimmick[i]->Load();
				}
				energy->Load();
				player->Load();
				camera->Load();
				ui->Load();
				sound->StopGameClear();
				sound->StopGameOver();
				sound->StopTutorial();

				//�Q�[����ԕω�
				gameStatus = STATE_TITLE;
			}

			//�^�C�g�����
			if (gameStatus == STATE_TITLE)
			{
				sound->StopTutorial();
				//sound->PlayTitle();
				input->Update();
				stage->Update();
				dome->SkydomeUpdate();
				player->UpdateTitle();
				ui->UpdateTitle(*input);
				camera->GameTitle(*player);
				ClearDrawScreen();

				dome->SkydomeDraw();
				stage->Draw();
				player->Draw();
				ui->DrawTitle();

				// �Q�[����ԕω�
				if ((input->GetNowFrameInput() & PAD_INPUT_C) != 0 && ui->GetisIsChosePlay() || CheckHitKey(KEY_INPUT_SPACE))
				{
					sound->PlayDecide();
					gameStatus = STATE_READY;
				}
				else if ((input->GetNowFrameInput() & PAD_INPUT_C) != 0 && ui->GetisIsHowToPlay() || CheckHitKey(KEY_INPUT_SPACE))
				{
					sound->PlayDecide();
					gameStatus = STATE_TUTORIAL;
				}
			}
			//�`���[�g���A�����
			if (gameStatus == STATE_READY)
			{

				gameManager->FadeOutToWhite(2000);
				//�`��

				// �Q�[����ԕω�
				gameStatus = STATE_LESSON;
			}
			//�`���[�g���A�����
			if (gameStatus == STATE_TUTORIAL)
			{
				sound->StopTitle();
				//sound->PlayTutorial();
				input->Update();
				stage->Update();
				dome->SkydomeUpdate();
				camera->ReadyUpdate(*player);
				player->UpdateTutorial(*input, *onattackply, *camera);

				ClearDrawScreen();
				//�`��
				dome->SkydomeDraw();
				stage->Draw();
				player->Draw();
				ui->DrawTutorial();
				// �Q�[����ԕω�
				if ((input->GetNowFrameInput() & PAD_INPUT_A) != 0 || CheckHitKey(KEY_INPUT_SPACE) && ui->GetisIsChosePlay())
				{
					sound->PlayDecide();
					gameStatus = STATE_LOAD;
				}
			}
			//�Q�[�����n�܂�܂ł̃J�E���g�_�E��
			if (gameStatus == STATE_LESSON)
			{
				input->Update();
				camera->Update(*player, *input, *enemy, *static_cast<const EnemyAttackRangeChecker*>(hitchecker[1]));
				ClearDrawScreen();
				//�`��
				dome->SkydomeDraw();
				stage->Draw();
				player->Draw();
				enemy->Draw();
				ui->DrawLesson();
				if ((input->GetNowFrameInput() & PAD_INPUT_C) != 0 || CheckHitKey(KEY_INPUT_SPACE))
				{
					sound->PlayDecide();
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_GAME;
				}
			}

			//�Q�[����
			if (gameStatus == STATE_GAME)
			{
				sound->StopTitle();
				//sound->PlayGame();
				// �X�J�C�h�[������
				dome->SkydomeUpdate();
				//�Q�[���V�[���̐���
				stage->Update();
				//�p�b�h�̐���
				input->Update();
				//EnemyAttackRangeChecker test;
				//const auto enemyattackRangeHitChecker = static_cast<const EnemyAttackRangeChecker*>(hitchecker[1]);
				//�����蔻�萧��
				for (int i = 0; i < GimmickNum; i++)
				{
					ongimmick[i]->Update(*player, *gimmick[i]);
				}
				for (int i = 0; i < HITCHECK_NUM; i++)
				{
					hitchecker[i]->Update(*player, *enemy);
				}
				onattackply->Update(*player, *enemy);
				onattackedenemy->Update(*energy, *enemy, *player);
				enemy->Update(*player, *static_cast<const EnemyAttackRangeChecker*>(hitchecker[1]), *onattackedenemy, *sound);
				for (int i = 0; i < GimmickNum; i++)
				{
					gimmick[i]->Update(*enemy);
					player->Update(*input, *onattackply, *ongimmick[i], *camera, *sound);
				}

				// �v���C���[����


				energy->Update(*enemy, *player, *onattackedenemy);
				// �J�����̐���
				camera->Update(*player, *input, *enemy, *static_cast<const EnemyAttackRangeChecker*>(hitchecker[1]));

				effect->Update();

				// ��ʂ�����������
				ClearDrawScreen();

				// �`��
				dome->SkydomeDraw();
				stage->Draw();
				energy->Draw();
				player->Draw();
				enemy->Draw();
				effect->Draw();
				onattackedenemy->Draw();
				for (int i = 0; i < HITCHECK_NUM; i++)
				{
					hitchecker[i]->DrawCircle();
					ongimmick[i]->DrawCircle();
				}
				player->DrawTexture();
				enemy->DrawTexture();
				ui->DrawGame(*input);
				for (int i = 0; i < GimmickNum; i++)
				{
					gimmick[i]->Draw();
				}
				if (player->GetHp() == 0)
				{
					gameStatus = STATE_READYGAMEOVER;
				}
				else if (enemy->GetHp() == 0)
				{
					gameStatus = STATE_READYCLEAR;
				}
			}

			//�Q�[���I�[�o�[���o
			if (gameStatus == STATE_READYGAMEOVER)
			{
				sound->StopGame();
				sound->PlayGameOver();
				gameManager->FadeOutToWhite(2000);
				enemy->ChangeMotion(Enemy::AnimKind::JumpAttack);
				camera->GameTitle(*player);

				// ��ʂ�����������
				ClearDrawScreen();

				dome->SkydomeDraw();
				stage->Draw();

				if (gameManager->GetisWhiteOut())
				{
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_GAMEOVER;
				}
			}

			if (gameStatus == STATE_READYCLEAR)
			{
				sound->StopGame();
				sound->PlayGameClear();
				gameManager->FadeOutToWhite(2000);
				stage->Update();
				enemy->ChangeMotion(Enemy::AnimKind::Die);
				enemy->UpdateShadow();
				dome->SkydomeUpdate();
				camera->GameEnd(*enemy);

				ClearDrawScreen();

				dome->SkydomeDraw();
				stage->Draw();
				player->Draw();
				ui->DrawTitle();
				// ��ʂ�����������
				ClearDrawScreen();
				if (gameManager->GetisWhiteOut())
				{
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_CLEAR;
				}
			}

			//�Q�[�����U���g
			if (gameStatus == STATE_GAMEOVER)
			{
				input->Update();
				stage->Update();
				dome->SkydomeUpdate();
				enemy->UpdateGameOver();
				camera->GameEnd(*enemy);
				ClearDrawScreen();

				dome->SkydomeDraw();
				stage->Draw();
				enemy->DrawGameOver();
				ui->DrawGameOver();
				// �Q�[����ԕω�
				if ((input->GetNowFrameInput() & PAD_INPUT_C) != 0 || CheckHitKey(KEY_INPUT_SPACE))
				{
					sound->PlayDecide();
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_LOAD;
				}
			}
			//�Q�[�����U���g
			if (gameStatus == STATE_CLEAR)
			{
				input->Update();
				stage->Update();
				dome->SkydomeUpdate();
				enemy->UpdateGameClear();
				camera->GameClear(*enemy);

				ClearDrawScreen();

				dome->SkydomeDraw();
				stage->Draw();
				enemy->Draw();
				ui->DrawGameClear();
				// �Q�[����ԕω�
				if ((input->GetNowFrameInput() & PAD_INPUT_C) != 0 || CheckHitKey(KEY_INPUT_SPACE))
				{
					sound->PlayDecide();
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_LOAD;
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