#pragma once

class EnemyAttackRangeChecker;
class Player;

class Enemy
{
public:

	enum class State :int
	{
		Trun = 0,
		Charge = 1,
		JumpAttack = 2,
		SpinAttack = 3,
		Walk = 4,
		Run = 5,
		Idol = 6,
		Musscle = 7,
		TireIdol = 8,
		SmallDamage = 9,
		BigDamge = 10,
		Missile = 11,
		Blow = 12,
		Die = 13,
	};
	enum class AnimKind : int
	{
		Trun = 0,
		Charge = 1,
		JumpAttack = 2,
		SpinAttack = 3,
		Walk = 4,
		Run = 5,
		Idol=6,
		Musscle=7,
		TireIdol=8,
		SmallDamage=9,
		BigDamge=10,
		Missile=11,
		Blow=12,
		Die=13,
	};

	Enemy();
	~Enemy();
	void Load();									//初期化
	void InitializeAttack();
	void ChangeTire();
	void TireTimer();
	void Update(const Player& player, const EnemyAttackRangeChecker& attackRange);				//更新
	State UpdateEnemyState(const EnemyAttackRangeChecker& attackRange);						//
	void RushAttack(const Player& player, const EnemyAttackRangeChecker& attackRange);
	void UpdateShadow();							//影の更新
	void UpdateAngle(const Player& player);			//向きの更新
	void UpdateAnimationState(State prevState);		//
	void UpdateAnimation();							//
	void UpdateEffect();
	void ChangeChasing();
	void LimitRange();
	void AttackTimer();
	void ChangeMotion(AnimKind  motionNum);			//モーション変更
	void DrawShadow();								//影の描画
	void Draw();									//影の表示
	// モデルハンドルの取得.
	const VECTOR& GetPos() const { return position; }
	const bool& GetIsAttack() const { return isAttack; }

private:
	//アニメーションに関するメンバ静的定数
	static constexpr float playAnimSpeed = 0.7f;		//アニメーションを進める速度
	static constexpr float AnimBlendSpeed = 0.1f;	// アニメーションのブレンド率変化速度
	static constexpr float	MoveSpeed = 0.50f;		// 移動速度
	static constexpr float Scale = 0.04f;  //大きさ
	static constexpr float	AngleSpeed = 0.6f;		// 角度変化速度

	//Enemy自身に関するメンバ変数
	VECTOR position;
	VECTOR angleVector;
	float angle;
	int EnemyHandle;
	int hp;
	//Enemyの攻撃に関するメンバ変数
	bool isShortAttack;
	bool islimitRange;
	bool attackReady;
	bool isChasing;
	bool isAttack;
	bool isCharge;
	bool isTurn;
	bool tire;
	float attackTimer;
	float returnRange;
	float tireTimer;
	int chaseCount;
	//アニメーションに関するメンバ変数
	State currentState;				//現在のアニメーションの状態
	float playTime;					//アニメーションの時間の合計
	float AnimTime;					//アニメーションを進める変数
	int AttachIndex;					//アニメーションを付与される変数
	int PlayAnim;					//現在のアニメーションアタッチ番号

	float animBlendRate;				//過去と現在のアニメーションのブレンド率
	float prevPlayTime;				//前のアニメーションの時間の合計
	int prevPlayAnim;				//前のアニメーションアタッチ番号

	//Enemyーの影
	VECTOR shadowToppos;			//影の頂点
	VECTOR shadowBottompos;		//影の底辺
	float ShadowRad;				//影の半径

	//エフェクトに関するメンバ変数

	static constexpr float EffektScale = 10.0f;		//大きさ

	
	int TireHandle;

	// 何でもいいので画像を読み込む。
	int grBackgroundHandle;
	int grFrontHandle;
	// エフェクトの表示する位置を設定する。
	VECTOR effectPosition;
	// 時間を初期化する(定期的にエフェクトを再生するため)
	int time;

	// 再生中のエフェクトのハンドルを初期化する。
	int EnemyEffectHandle = -1;

};

