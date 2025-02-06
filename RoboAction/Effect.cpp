#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Effect.h"

Effect::Effect()
{}

Effect::~Effect()
{}


void Effect::Update()
{
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

void Effect::Draw()
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}