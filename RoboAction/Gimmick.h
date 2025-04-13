#pragma once
class Enemy;
class Gimmick
{
public:
	Gimmick(VECTOR Setposition);
	~Gimmick();
	void Load();						//読み込み
	void UpdateEffect(const Enemy& enemy);					//エフェクトの更新
	void Update(const Enemy& enemy);							//更新
	void UpdateMove(const Enemy& enemy);						//更新
	void UpdateMoveCircle(const Enemy& enemy);						//更新
	void DropTimer(const Enemy& enemy);
	void UpdateShadow();					//影の更新
	void Draw();						//描画
	const VECTOR& GetPos() const { return position; }
	const bool& GetIsGimmickSporn() const { return isGimmickSporn; }
	void MoveOriginPosition(const Enemy& enemy);
	void MoveResetPosition(const Enemy& enemy);
	void ReturnGimmickPos(const Enemy& enemy);
	void UpdateAngle(const Enemy& enemy);
private:

	int GimmickHandle;
	static constexpr float EffektScale = 10.0f;		//大きさ
	static constexpr float returnRange = 0.0f;		//大きさ
	static constexpr float ModelScale = 0.0025f;	//大きさ
	// 円運動のための定数
	static constexpr float Radius = 7.0f; // 円の半径
	static constexpr float AngleSpeed = 0.025f; // 角速度
	VECTOR position;							    //ポジション.
	VECTOR AngleVec;							    //ベクトル
	VECTOR Resetposition;							//リセットポジション
	float dropTime;                                 //
	float moveSpeed;                                //
	bool isLimitRange;								//
	bool isGimmickSporn;                            //
	float endDropTime;
	bool isOrigin;
	float moveTime;
	bool decreaseEnemyHp;
	// 時間を初期化する(定期的にエフェクトを再生するため)
	int time;
	// 再生中のエフェクトのハンドルを初期化する。
	int playingEffectHandle = -1;
	// エフェクトの影
	VECTOR shadowBottompos;				//影の底辺
	VECTOR shadowToppos;				//影の頂点
	float ShadowRad;					//影の半径
	int GimmickModelHandle;
	VECTOR modelPosition;
	bool returnEnemyPos;
	float angle;
};