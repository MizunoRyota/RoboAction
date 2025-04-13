#pragma once

class EnemyAttackRangeChecker;
class Player;
class Enemy;
class Input;
/// <summary>
/// カメラ
/// </summary>
class Camera
{
public:
	Camera();			// コンストラクタ.
	~Camera();			// デストラクタ.
	void Load();		//初期化

	void GameTitle(const Player& player);//ゲームタイトル
	void ReadyUpdate(const Player& player);//チュートリアル画面
	void Update(const Player& player,const Input& input, const Enemy& enemy, const EnemyAttackRangeChecker& attackRange);	// 更新.
	void FixCameraPosition();
	void ShakeCamera(float intensity, float duration, const Player& player);
	void GameEnd(const Enemy& enemy);//ゲームオーバー画面準備
	void GameClear(const Enemy& enemy);//ゲームクリア画面準備
	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	const VECTOR& GetTarget()	const { return targetposition; }

private:
	static constexpr float Zoom = -3.0f;			//z軸のカメラポジション
	static constexpr float Hight = 3.0f;			//y軸のカメラポジション
	static constexpr float TargetHight = 1.3;		//ターゲットの見る高さ
	static constexpr float AngleSpeed = 0.15f;		//向きが変わるスピード
	float            angleVertical;					// カメラの垂直角度
	float            angleHorizontal;				// カメラの水平角度

	// 揺れの強さと持続時間
	static constexpr float shakeIntensity = 5.0f;		//揺れの強さ
	static constexpr float shakeDuration = 10.0f;		//揺れの最大時間
	static constexpr float Distance = 5.0f;				//距離

	float shakeTime;			//揺れ時間
	bool isDamage;				//ダメージを受けているか
	bool isShake;				//揺れているか
	Input* rightInput;			//右スティック情報
	VECTOR Offset;				//
	VECTOR OriginalOffset;		//
	VECTOR AngleVec;			//向きベクトル
	VECTOR	position;			// ポジション.
	VECTOR targetposition;		//　カメラが注視するポジション
};