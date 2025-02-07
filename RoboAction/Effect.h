#pragma once

class Effect
{
public:
	Effect();
	~Effect();
	void Load();	//初期化
	void Update();

	void Draw();	//描画
	void StopDraw();
private:
	//int effectHandle;
	//// 何でもいいので画像を読み込む。
	//int grBackgroundHandle;
	//int grFrontHandle;
	//// エフェクトの表示する位置を設定する。
	//VECTOR effectPosition;
	//// 時間を初期化する(定期的にエフェクトを再生するため)
	//int time;

	//// フルスクリーン切り替え用フラグを設定する。(F1、F2でウインドウ、フルスクリーンを切り替えれるようにする。)
	//bool isFullScreen = false;

	//// 再生中のエフェクトのハンドルを初期化する。
	//int playingEffectHandle = -1;
};