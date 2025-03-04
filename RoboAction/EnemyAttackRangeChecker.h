#pragma once

class EnemyAttackRangeChecker : public HitChecker
{
public:
	EnemyAttackRangeChecker();
	virtual~EnemyAttackRangeChecker();

	void Update(const Player& player, const Enemy& enemy)override;	// 更新
	bool CheckShortHit(const Player& player, const Enemy& enemy);
	bool CheckMiddleHit(const Player& player, const Enemy& enemy);
	bool CheckLongHit(const Player& player, const Enemy& enemy);

	void DrawCircle()override;
	// 範囲内に入っているかの取得.
	const bool& GetisShortWithin() const { return isShortWithin; }
	const bool& GetisMiddleWithin() const { return isMiddleWithin; }
	const bool& GetisLongWithin() const { return isLongWithin; }

private:
	bool isShortWithin;				//近距離判定
	bool isMiddleWithin;			//中距離判定
	bool isLongWithin;				//遠距離判定
	float AttackShrotRange;			//近距離範囲
	float AttackMiddleRange;		//中距離範囲
	float AttackLongRange;			//遠距離範囲
	float LengthRange;				//円と円の距離
	VECTOR keepDistance;			//距離を保持する変数
	float Distance;					//距離
	float Length;					//プレイヤーの円とEnemyの円の半径の合計
};