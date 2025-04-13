#pragma once

class EnemyAttackRangeChecker;
class OnAttackedEnemy;
class Player;
class Sound;	
class Enemy
{
public:

	enum class State :int
	{
		Idol = 0,
		Charge = 1,
		TireIdol = 2,
		Run = 3,
		Trun = 4,
		OnAttack = 5,
		Explosion = 6,
		Die = 7,
		JumpAttack = 8,
	};
	enum class AnimKind : int
	{
		Idol = 0,
		Charge = 1,
		TireIdol = 2,
		Run = 3,
		Trun = 4,
		OnAttack = 5,
		Explosion = 6,
		Die = 7,
		JumpAttack = 8,
	};

	Enemy();
	~Enemy();
	void Load();									//初期化
	void Initialize();								//初期化
	void InitializeAttack();						//初期化
	void PlayExplosion();
	void PlayOnenemy();
	void ChangeTire();								//疲れる
	void TireTimer();								//疲れる時間		
	void Update(const Player& player, const EnemyAttackRangeChecker& attackRange, const OnAttackedEnemy& onAttacked, const Sound& sound);			//更新
	State UpdateEnemyState(const EnemyAttackRangeChecker& attackRange, const OnAttackedEnemy& onAttacked);						//
	void RushAttack(const Player& player, const EnemyAttackRangeChecker& attackRange);											//
	void DecreaseHp(const OnAttackedEnemy& onAttacked);			//Hpの減少
	void UpdateAnimationState(State prevState);					//
	void UpdateAngle(const Player& player);						//向きの更新
	void UpdateAnimation();										//
	void UpdateShadow();										//影の更新
	void UpdateEffect(const OnAttackedEnemy& onAttacked);		//エフェクトの更新
	void MoveOnAttack(const OnAttackedEnemy& onAttacked);		//攻撃を受けた時の移動
	void LimitRange(const OnAttackedEnemy& onAttacked);			//範囲制限
	void ChangeMotion(AnimKind  motionNum);						//モーション変更
	void ChangeChasing();										//追いかける
	void AttackTimer();											//攻撃時間
	void DrawTexture();											//テクスチャの描画
	void DrawShadow();											//影の描画
	void Draw();												//影の表示
	void DrawGameOver();										//ゲームオーバーの表示
	void UpdateGameClear();										//ゲームクリア更新
	void UpdateGameOver();										//ゲームオーバーの更新	
	// モデルハンドルの取得.
	const bool& GetIsExplosion() const { return isExplosion; }
	const int& GetChaseCount() const { return chaseCount; }
	const VECTOR& GetAngle() const { return angleVector; }
	const bool& GetIsAttack() const { return isAttack; }
	const VECTOR& GetPos() const { return position; }
	const int& GetHp() const { return hp; }
	const float& GetFloatAngle() const { return angle; }

private:
	//アニメーションに関するメンバ静的定数
	static constexpr float playAnimSpeed = 0.5f;	//アニメーションを進める速度
	static constexpr float AnimBlendSpeed = 0.1f;	// アニメーションのブレンド率変化速度
	static constexpr float AngleSpeed = 0.6f;		// 角度変化速度
	static constexpr float Scale = 0.04f;			//大きさ
	static constexpr float OnMoveSpeed = 1.5;		// 移動速度
	static constexpr float ChargeAnimSpeed = 0.35;	

	//Enemy自身に関するメンバ変数
	VECTOR angleVector;				//方向
	VECTOR position;				//ポジション
	int EnemyHandle;				//モデルハンドル
	float angle;					//角度
	int hp;							//体力
	float MoveSpeed;				// 移動速度
	//2/14追加
	bool isOnAttack;
	//Enemyの攻撃に関するメンバ変数
	bool isShortAttack;		//
	bool isDecreaseHp;		//
	bool islimitRange;		//
	bool isExplosion;		//
	bool isChasing;		//
	bool onAttack;		//
	bool isAttack;		//
	bool isCharge;		//
	bool isTurn;		//
	bool tire;		//
	float attackTimer;		//
	float returnRange;		//
	float tireTimer;		//
	int chaseCount;			//
	//アニメーションに関するメンバ変数
	State currentState;				//現在のアニメーションの状態
	float playTime;					//アニメーションの時間の合計
	float AnimTime;					//アニメーションを進める変数
	int AttachIndex;				//アニメーションを付与される変数
	int PlayAnim;					//現在のアニメーションアタッチ番号

	float animBlendRate;			//過去と現在のアニメーションのブレンド率
	float prevPlayTime;				//前のアニメーションの時間の合計
	int prevPlayAnim;				//前のアニメーションアタッチ番号

	//Enemyーの影
	VECTOR shadowToppos;		//影の頂点
	VECTOR shadowBottompos;		//影の底辺
	float ShadowRad;			//影の半径

	//エフェクトに関するメンバ変数
	static constexpr float EffektScale = 10.0f;		//大きさ

	int playingEffectHandle = -1;	// 再生中のエフェクトのハンドルを初期化する。
	int ExplosionHandle;			//疲れハンドル
	int BoostDashHandleFhase1;		//
	int BoostDashHandleFhase2;		//
	int BoostDashHandleFhase3;		//
	int BoostDashHandleFhase4;		//
	int BoostDashHandleFhase5;		//

	int TireHandle;					//
	int ChargeHandle;				//	
	int time;						//時間を初期化する(定期的にエフェクトを再生するため)

	//HP
	int HpGauge;					//
	float HpGaugeWidth;				//
	int EnptyHpGauge;				//

	int ExplosionSEHandle;			//
	int OnenemyHandle;				//

};

