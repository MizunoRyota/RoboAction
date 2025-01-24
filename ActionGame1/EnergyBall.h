#pragma once

class Enemy;

class Energy
{
public:
	Energy();
	~Energy();
    void Load();								//初期化
    void BallSporn(const Enemy& enemy);         //エネルギーボールの生成
    void Update(const Enemy& enemy);			//更新
    void UpdateShadow();						//影の更新	
    void UpdateEffect();						//エフェクトの更新
    void DrawShadow();							//影の描画  
    void Draw();								//描画
    void UpdateExplosionEffect();				//爆発エフェクトの更新
private:
	static constexpr float EffektScale = 10.0f;		//大きさ
    VECTOR position;								//ポジション.
    int EnergyBallHandle;							//エネルギーボールモデルハンドル
    int ExplosionHandle;							//爆発エフェクトハンドル
	bool isBallSporn;
	// 時間を初期化する(定期的にエフェクトを再生するため)
	int time;
	// 再生中のエフェクトのハンドルを初期化する。
	int playingEffectHandle = -1;
    // エフェクトの影
	VECTOR shadowBottompos;				//影の底辺
	VECTOR shadowToppos;				//影の頂点
	float ShadowRad;					//影の半径
};

