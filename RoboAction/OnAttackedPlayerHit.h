#pragma once

class OnAttackedPlayer
{
public:
	OnAttackedPlayer();
	~OnAttackedPlayer();
	void Update(const Player& player, const Enemy& enemy);
	bool CheckBeAttackHit(const Player& player, const Enemy& enemy);
	const bool& GetisOnAttack() const { return isOnAttack; }

private:
	static constexpr  float PlayerHight = 0.3f;		//プレイヤーの高さ
	bool isOnAttack;

	//プレイヤーの当たり判定変数
	VECTOR playerCircle;				//プレイヤーの当たり判定のポジション
	float playerRadius;					//プレイヤーの当たり判定の半径

	//Enemyの当たり判定
	VECTOR enemyCircle;					//Enemyの当たり判定のポジション
	float enemyRadius;					//Enemyの当たり判定の半径

	VECTOR keepDistance;				//距離を保持する変数
	float Distance;						//距離
	float Length;						//プレイヤーの円とEnemyの円の半径の合計
};

