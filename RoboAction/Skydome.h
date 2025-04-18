#pragma once

class Skydome
{
public:
	Skydome();
	~Skydome();
	void SkydomeUpdate();	//ゲーム中の更新
	void SkydomeTitle();	//ゲームタイトルの更新
	void SkydomeDraw();		//スカイドームの描画
private:
	int SkydomeHandle;		//モデルハンドル
	VECTOR pos;				//ポジション
	VECTOR	dir;			// 回転方向.
	// 静的定数.
	static constexpr float Scale = 0.10f;		//大きさ

};