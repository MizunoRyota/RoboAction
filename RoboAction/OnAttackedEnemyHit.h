#pragma once

class Energy;
class Player;
class Enemy;

class OnAttackedEnemy
{
public:
	OnAttackedEnemy();
	~OnAttackedEnemy();
	void Update(const Energy& ball, const Enemy& enemy, const Player& player);
	bool CheckOnAttackHit(const Energy& ball, const Enemy& enemy);
	bool CheckOnBallHit(const Player& player,const Energy& ball);
	const bool& GetisOnAttack() const { return isOnAttack; }
	const bool& GetisBallHit() const { return isBallHit; }
	const VECTOR& GetAttackAngle() const { return attackAngle; }
	void Draw();
private:

	static constexpr  float PlayerHight = 0.3f;		//プレイヤーの高さ
	static constexpr  float EnemyHight = 3.5f;		//プレイヤーの高さ


	VECTOR AngleVec;
	bool isOnAttack;

	//エネルギーボールの当たり判定変数
	VECTOR energyCircle;				//プレイヤーの当たり判定のポジション
	float  energyRadius;				//プレイヤーの当たり判定の半径
	float energyHight;					//プレイヤーの高さ
	//Enemyの当たり判定
	VECTOR enemyCircle;					//Enemyの当たり判定のポジション
	float enemyRadius;					//Enemyの当たり判定の半径

	//プレイヤーの攻撃範囲
	VECTOR PlayerAttackPosition;			//プレイヤーの当たり判定のポジション
	float  playerAttackRadius;				//プレイヤーの当たり判定の半径
	VECTOR attackAngle;
	float attackDistance;
	VECTOR keepBallAttackDistance;
	float ballAttackDistance;
	float attackBallLength;
	bool isBallHit;

	float Distance;						//距離
	VECTOR keepDistance;				//距離を保持する変数
	float Length;						//プレイヤーの円とEnemyの円の半径の合計
};

