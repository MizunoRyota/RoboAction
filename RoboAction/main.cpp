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
	STATE_LOAD,			//ロード.
	STATE_INIT,			//初期化.
	STATE_TITLE,		//タイトル.
	STATE_READY,        //準備
	STATE_TUTORIAL,     //準備
	STATE_LESSON,		//ゲームが始まるまでのカウント
	STATE_GAME,			//ゲーム中.
	STATE_READYGAMEOVER,//やられている状態
	STATE_READYCLEAR,	//クリア状態
	STATE_GAMEOVER,		//ゲームオーバー.
	STATE_CLEAR,		//ゲームクリア.
};

const int HITCHECK_NUM = 2;

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 画面モードのセット
	SetGraphMode(1600, 900, 32);
	ChangeWindowMode(FALSE);

	// DXライブラリを初期化する。
	if (DxLib_Init() == -1) return -1;

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// DirectX9を使用するようにする。(DirectX11も可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面を描画対象にする
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う
	SetUseBackCulling(TRUE);		// バックカリングを行う

	// 1秒間に処理するフレーム数を設定(60FPS)
	const int TARGET_FPS = 60;
	const int FRAME_TIME = 1000 / TARGET_FPS;  // 1フレームあたりの理想的な時間 (ミリ秒)
	const int GimmickNum = 4;
	// ********** フォントのロード **********
	LPCSTR font_path = "Data/Font/LightNovelPOPv2.otf"; // 読み込むフォントファイルのパス
	//// フォントの変更
	ChangeFont("ラノベPOP v2", DX_CHARSET_DEFAULT);

	// インスタンス生成
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

	// エスケープキーが押されるかウインドウが閉じられるまでループ
	LONGLONG frameTime = 0;

	int gameStatus = STATE_LOAD;	//現在のゲーム中の状態
	bool debugPauseFlag = false;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		// フレーム開始時の時間を取得
		int startTime = GetNowCount();
		// ぼたんおしたら
		if (CheckHitKey(KEY_INPUT_P))
		{
			debugPauseFlag = true;
		}
		while (debugPauseFlag)
		{
			WaitTimer(2);
			// ぼたんおしたら
			if (CheckHitKey(KEY_INPUT_O))
			{
				debugPauseFlag = false;
			}
		}

		if (debugPauseFlag == false)
		{
			//全ての初期化
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

				//ゲーム状態変化
				gameStatus = STATE_TITLE;
			}

			//タイトル画面
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

				// ゲーム状態変化
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
			//チュートリアル画面
			if (gameStatus == STATE_READY)
			{

				gameManager->FadeOutToWhite(2000);
				//描画

				// ゲーム状態変化
				gameStatus = STATE_LESSON;
			}
			//チュートリアル画面
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
				//描画
				dome->SkydomeDraw();
				stage->Draw();
				player->Draw();
				ui->DrawTutorial();
				// ゲーム状態変化
				if ((input->GetNowFrameInput() & PAD_INPUT_A) != 0 || CheckHitKey(KEY_INPUT_SPACE) && ui->GetisIsChosePlay())
				{
					sound->PlayDecide();
					gameStatus = STATE_LOAD;
				}
			}
			//ゲームが始まるまでのカウントダウン
			if (gameStatus == STATE_LESSON)
			{
				input->Update();
				camera->Update(*player, *input, *enemy, *static_cast<const EnemyAttackRangeChecker*>(hitchecker[1]));
				ClearDrawScreen();
				//描画
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

			//ゲーム中
			if (gameStatus == STATE_GAME)
			{
				sound->StopTitle();
				//sound->PlayGame();
				// スカイドーム制御
				dome->SkydomeUpdate();
				//ゲームシーンの制御
				stage->Update();
				//パッドの制御
				input->Update();
				//EnemyAttackRangeChecker test;
				//const auto enemyattackRangeHitChecker = static_cast<const EnemyAttackRangeChecker*>(hitchecker[1]);
				//当たり判定制御
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

				// プレイヤー制御


				energy->Update(*enemy, *player, *onattackedenemy);
				// カメラの制御
				camera->Update(*player, *input, *enemy, *static_cast<const EnemyAttackRangeChecker*>(hitchecker[1]));

				effect->Update();

				// 画面を初期化する
				ClearDrawScreen();

				// 描画
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

			//ゲームオーバー演出
			if (gameStatus == STATE_READYGAMEOVER)
			{
				sound->StopGame();
				sound->PlayGameOver();
				gameManager->FadeOutToWhite(2000);
				enemy->ChangeMotion(Enemy::AnimKind::JumpAttack);
				camera->GameTitle(*player);

				// 画面を初期化する
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
				// 画面を初期化する
				ClearDrawScreen();
				if (gameManager->GetisWhiteOut())
				{
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_CLEAR;
				}
			}

			//ゲームリザルト
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
				// ゲーム状態変化
				if ((input->GetNowFrameInput() & PAD_INPUT_C) != 0 || CheckHitKey(KEY_INPUT_SPACE))
				{
					sound->PlayDecide();
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_LOAD;
				}
			}
			//ゲームリザルト
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
				// ゲーム状態変化
				if ((input->GetNowFrameInput() & PAD_INPUT_C) != 0 || CheckHitKey(KEY_INPUT_SPACE))
				{
					sound->PlayDecide();
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_LOAD;
				}
			}
		}

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		// フレーム終了時の時間を取得
		int endTime = GetNowCount();

		// フレーム処理時間を計算
		int elapsedTime = endTime - startTime;

		// 処理が早く終わった場合、残り時間待機する
		if (elapsedTime < FRAME_TIME)
		{
			// 残り時間待機
			WaitTimer(FRAME_TIME - elapsedTime);
		}
	}

	// Effekseerを終了する。
	Effkseer_End();
	// 後始末
	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}