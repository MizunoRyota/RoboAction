#pragma once

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
	void GameTitle(const VECTOR& mappos);//ゲームタイトル
	void ReadyUpdate(const VECTOR& playerpos,const Enemy& enemy);//チュートリアル画面
	void Update(const Player& player,const Input& input, const Enemy& enemy);	// 更新.
	void FixCameraPosition();
	void ShakeCamera(float intensity, float duration, const Player& player);
	void GameEnd(const VECTOR& planepos);//ゲームオーバー画面準備

	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	const VECTOR& GetTarget()	const { return targetposition; }
private:
	static constexpr float Zoom = -3.0f;				//z軸のカメラポジション
	static constexpr float Hight = 1.5f;			//y軸のカメラポジション
	static constexpr float TargetHight = 1.3;		//ターゲットの見る高さ
	static constexpr float AngleSpeed = 0.15f;
	float            angleVertical;           // カメラの垂直角度
	float            angleHorizontal;         // カメラの水平角度

	// 揺れの強さと持続時間
	static constexpr float shakeIntensity = 5.0f;
	static constexpr float shakeDuration = 2.0f;
	static constexpr float Distance = 5.0f;		//距離

	float shakeTime;
	bool isDamage;
	Input* rightInput;
	VECTOR Offset;
	VECTOR OriginalOffset;
	VECTOR AngleVec;
	VECTOR	position;			// ポジション.
	VECTOR targetposition;		//　カメラが注視するポジション
};