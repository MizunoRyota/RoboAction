#pragma once
class Player;
class Gimmick;

class OnGimmick
{
public:
	OnGimmick();
	~OnGimmick();
	void Update(const Player& player, const Gimmick& gimmick);		// 更新
	bool CheckHit(const Player& player, const Gimmick& gimmick);	//当たり判定チェック
	void DrawCircle();
	const bool& GetisOnGimmick() const { return isOnGimmick; }

private:
	static constexpr  float PlayerHight = 0.8f;		//プレイヤーの高さ
	static constexpr  float playerRadius = 1.0f;		//プレイヤーの当たり判定の半径
	static constexpr  float gimmickRadius = 1.0f;		//Enemyの当たり判定の半径

	bool isHit;
	bool isOnGimmick;
	//プレイヤーの当たり判定変数
	VECTOR playerCircle;				//プレイヤーの当たり判定のポジション

	//Enemyの当たり判定
	VECTOR enemyCircle;					//Enemyの当たり判定のポジション

	VECTOR keepDistance;				//距離を保持する変数
	float Distance;						//距離
	float Length;						//プレイヤーの円とEnemyの円の半径の合計

};