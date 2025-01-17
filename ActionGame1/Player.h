#pragma once

class Input;

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
	void Update(const Input& input, bool beattackply);  //更新
	State UpdateMoveParameterWithPad(const Input& input, VECTOR& moveVec);//パッドの入力更新
	void UpdateAngle();
	bool BeAttacked(bool isBeattack);
	void LimitRange();
	void Move(VECTOR& moveVec);
	void Draw();	//描画
	void UpdateEffect();	//エフェクトの更新
	void UpdateShadow();	//プレイヤーの影の更新
	void DrawShadow();		//プレイヤーの影の描画
	void DrawEffect();		//エフェクトの描画
	// モデルハンドルの取得.
	const VECTOR& GetPos() const { return position; }
	const bool& GetIsBeAttack() const { return isBeAttack; }

private:
	// 静的定数.
	//プレイヤー自身に関するメンバ静的定数
	static constexpr float Scale = 0.006f;		//大きさ
	//アニメーションに関するメンバ静的定数
	static constexpr float playAnimSpeed = 1.5f;		//アニメーションを進める速度
	static constexpr float playAttackAnimSpeed = 2.0f;		//アニメーションを進める速度

	static constexpr float AnimBlendSpeed = 0.1f;	// アニメーションのブレンド率変化速度
	static constexpr float	AngleSpeed = 0.6f;		// 角度変化速度
	static constexpr float	MoveSpeed = 0.50f;		// 移動速度

	//プレイヤー自身に関するメンバ変数
	VECTOR	velocity;					// 移動力.
	VECTOR position;					// ポジション.
	VECTOR Dir;							// 回転方向.
	VECTOR targetMoveDirection;			// モデルが向くべき方向のベクトル
	int PlayerHandle;					// プレイヤーのモデルハンドル
	bool isAttack;
	bool isBeAttack;
	bool isLimitRange;
	float returnRange;					//最大移動距離
	float angle;				
	//プレイヤーの攻撃に関するメンバ変数
	bool isFirstAttack;
	bool isSecondAttack;
	bool isThirdAttack;

	//アニメーションに関するメンバ変数
	State currentState;				//現在のアニメーションの状態
	//AttackAnimKind currentAttack;	//現在の攻撃アニメーションの状態
	float playTime;					//アニメーションの時間の合計
	int PlayAnim;					//現在のアニメーションアタッチ番号
	int AttachIndex;				//アニメーションを付与される変数
	float AnimTime;					//アニメーションを進める変数
	int prevPlayAnim;				//前のアニメーションアタッチ番号
	float prevPlayTime;				//前のアニメーションの時間の合計
	float animBlendRate;			//過去と現在のアニメーションのブレンド率

	//プレイヤーの影
	VECTOR shadowToppos;			//影の頂点
	VECTOR shadowBottompos;			//影の底辺
	float ShadowRad;				//影の半径

	void ChangeMotion(AnimKind  motionNum);					//モーション変更
	void UpdateAnimation(State prevState);									//Playerのアニメーション更新
	void UpdateAnimationState(State prevState);
	void UpdateAttackState(State prevState);
	void ResetMotion(State prevState);
	void UpdateAttack();
	 
	//エフェクトに関するメンバ変数

	static constexpr float EffektScale = 10.0f;		//大きさ

	int AttackHandle;
	int SecondAttackHandle;
	int ThirdAttackHandle;
	// エフェクトの表示する位置を設定する。

	// 時間を初期化する(定期的にエフェクトを再生するため)
	int time;

	// 再生中のエフェクトのハンドルを初期化する。
	int playingEffectHandle = -1;
};