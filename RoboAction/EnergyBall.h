#pragma once

class Enemy;
class Player;
class OnAttackedEnemy;
class Energy
{
public:
	Energy();
	~Energy();
    void Load();							//初期化
    void BallSporn(const Enemy& enemy);     //エネルギーボールの生成
    void DropTimer(const Enemy& enemy);     //
	void LimitRange();						//範囲制限
	void Update(const Enemy& enemy, const Player& player, const OnAttackedEnemy& onAttacked);		//更新
	void BlowAway(const Player& player, const OnAttackedEnemy& onAttacked);		//吹き飛ばし
	void ChangeBlowAway(const Player& player, const OnAttackedEnemy& onAttacked);	//ボールが当たったか
    void UpdateShadow();					//影の更新	
    void UpdateEffect();					//エフェクトの更新
    void DrawShadow();						//影の描画  
    void Draw();							//描画
    void UpdateExplosionEffect();			//爆発エフェクトの更新
	// モデルハンドルの取得.
	const VECTOR& GetPos() const { return position; }
	const bool& GetisLimitRange() const { return isLimitRange; }
	const bool& GetisIsBlowAway() const { return isBlowAway; }
private:
	static constexpr float EffektScale = 10.0f;		//大きさ
    VECTOR position;							    //ポジション.
	VECTOR AngleVec;							    //ベクトル
    int EnergyBallHandle;							//エネルギーボールモデルハンドル
    int ExplosionHandle;						    //爆発エフェクトハンドル
    float dropTime;                                 //
	float moveSpeed;                                //
	bool isBallSporn;                               //
	bool isDrop;								    //
	bool isBlowAway;						        //
	bool isLimitRange;								//
	float limitRange;								//
	// 時間を初期化する(定期的にエフェクトを再生するため)
	int time;
	// 再生中のエフェクトのハンドルを初期化する。
	int playingEffectHandle = -1;

    // エフェクトの影
	VECTOR shadowBottompos;				//影の底辺
	VECTOR shadowToppos;				//影の頂点
	float ShadowRad;					//影の半径
};