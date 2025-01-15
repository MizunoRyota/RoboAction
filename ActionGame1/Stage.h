#pragma once
class Stage
{
public:
	Stage();
	~Stage();

	void Load();	//初期化
	void Update();

	void Draw();	//描画

private:
	static constexpr float Scale = 0.01f;		//大きさ
	static constexpr float EffektScale = 10.0f;		//大きさ

	VECTOR position;	//ポジション.
	int StageHandle;	//3Dモデルハンドル
	int effectHandle;

	// エフェクトの表示する位置を設定する。
	VECTOR effectPosition;
	// 時間を初期化する(定期的にエフェクトを再生するため)
	int time ;

	// 再生中のエフェクトのハンドルを初期化する。
	int playingEffectHandle = -1;
};

