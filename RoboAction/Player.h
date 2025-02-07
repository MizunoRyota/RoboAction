#pragma once

class Input;
class Camera;
class OnAttackedPlayer;
class Sound;

class Player
{
public:
	// 状態
	enum class State : int
	{
		None = -1,				// なし
		Stand = 0,				// 不明
		FinishAttack = 1,		// とどめの一撃
		FirstAttack = 2,		// 最初の攻撃
		SecondAttack = 3,		// 2段目の攻撃
		LastAttack = 4,			// 最後の攻撃
		Squat = 5,				//しゃがむ
		Roll = 6,				//ローリング
		Idol = 7,				//立ち止まり
		Run = 8,				//走る
		TakeDamage = 9,			//ダメージを受ける
	};
	enum class AnimKind : int
	{
		None = -1,				// なし
		Stand = 0,				// 不明
		FinishAttack = 1,		// とどめの一撃
		FirstAttack = 2,		// 最初の攻撃
		SecondAttack = 3,		// 2段目の攻撃
		LastAttack = 4,			// 最後の攻撃
		Squat = 5,				//しゃがむ
		Roll = 6,				//ローリング
		Idol = 7,				//立ち止まり
		Run = 8,				//走る
		TakeDamage = 9,			//ダメージを受ける
	};

	Player();
	~Player();

	void Load();	//初期化
	void Initialize();	//初期化
	void PlayOnplayer();
	void PlaySlash();
	void Update(const Input& input, const OnAttackedPlayer& onattacked, const Camera& camera, const Sound& sound);  //更新
	void UpdateTitle();
	void UpdateTutorial(const Input& input, const OnAttackedPlayer& onattacked, const Camera& camera);		//ゲーム画面更新
	void UpdateGameOver();
	void UpdateGameClear();	
	State UpdateMoveParameterWithPad(const Input& input, VECTOR& moveVec, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec);//パッドの入力更新
	bool BeAttacked(const OnAttackedPlayer& onattacked);
	void Move(VECTOR& moveVec);
	void DecreaseHp();			//Hpの減少
	void UpdateEffect();		//エフェクトの更新
	void UpdateShadow();		//プレイヤーの影の更新
	void UpdateAngle();
	void LimitRange();
	void InvincibleTimer();
	void DrawTexture();											//テクスチャの描画
	void DrawShadow();		//プレイヤーの影の描画
	void Draw();				//描画
	// モデルハンドルの取得.
	const VECTOR& GetPos() const { return position; }
	const VECTOR& GetDirection() const { return targetMoveDirection; }
	const bool& GetisIsAttack() const { return isAttack; }
	const bool& GetisOnAttack() const { return isOnAttack; }
	const int& GetHp() const { return hp; }
private:
	// 静的定数.
	//プレイヤー自身に関するメンバ静的定数
	static constexpr float Scale = 0.006f;		//大きさ
	//アニメーションに関するメンバ静的定数
	static constexpr float playAttackAnimSpeed = 0.50f;		//アニメーションを進める速度
	static constexpr float AnimBlendSpeed = 0.1f;	// アニメーションのブレンド率変化速度
	static constexpr float playAnimSpeed = 0.75f;		//アニメーションを進める速度
	static constexpr float	AngleSpeed = 0.6f;		// 角度変化速度
	static constexpr float	MoveSpeed = 0.35f;		// 移動速度
	static constexpr float	AttackSpeed = 1.5f;		// 移動速度

	Sound* sound;

	//プレイヤー自身に関するメンバ変数
	VECTOR targetMoveDirection;			// モデルが向くべき方向のベクトル
	VECTOR position;					// ポジション.
	int PlayerHandle;					// プレイヤーのモデルハンドル
	int hp;								//体力
	bool isOnAttack;					// プレイヤーが攻撃を受けたかどうか	
	bool isAttack;						// プレイヤーが攻撃中かどうか
	bool isDecreaseHp;					// プレイヤーがHpを減少させたかどうか
	float isInvincible;					// プレイヤーが無敵状態かどうか
	float returnRange;					//最大移動距離
	float invincible;					//無敵時間
	float angle;						// 角度
	int alpha;							// 透明度
	//HP
	int HpGauge;
	float HpGaugeWidth;
	int EnptyHpGuage;
	//プレイヤーの攻撃に関するメンバ変数
	bool isFirstAttack; 
	bool isSecondAttack;
	bool isThirdAttack;
	bool isMoveStick;
	//アニメーションに関するメンバ変数
	State currentState;				//現在のアニメーションの状態
	//AttackAnimKind currentAttack;	//現在の攻撃アニメーションの状態
	float playTime;					//アニメーションの時間の合計
	int PlayAnim;					//現在のアニメーションアタッチ番号
	int AttachIndex;				//アニメーションを付与される変数
	float AnimTime;					//アニメーションを進める変数
	float prevPlayTime;				//前のアニメーションの時間の合計
	int prevPlayAnim;				//前のアニメーションアタッチ番号
	float animBlendRate;			//過去と現在のアニメーションのブレンド率

	//プレイヤーの影
	VECTOR shadowBottompos;			//影の底辺
	VECTOR shadowToppos;			//影の頂点
	float ShadowRad;				//影の半径

	void UpdateAnimationState(State prevState);				//アニメーションの状態更新処理
	void UpdateAttackState(State prevState);				//攻撃状態更新処理
	void UpdateAnimation(State prevState);					//Playerのアニメーション更新
	void ChangeMotion(AnimKind  motionNum);					//モーション変更
	void ResetMotion(State prevState);						//モーションリセット
	void UpdateAttack();									//攻撃更新
	 
	//エフェクトに関するメンバ変数

	static constexpr float EffektScale = 10.0f;		//大きさ

	int AttackHandle;					//エフェクトハンドル
	int SecondAttackHandle;				//エフェクトハンドル
	int ThirdAttackHandle;				//エフェクトハンドル
	// エフェクトの表示する位置を設定する。

	// 時間を初期化する(定期的にエフェクトを再生するため)
	int time;

	// 再生中のエフェクトのハンドルを初期化する。
	int playingEffectHandle = -1;

	int OnPlayerHandle;			//プレイヤーのモデルハンドル
	int SlashHandle;			//スラッシュエフェクトハンドル	

};