#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Effect.h"

Effect::Effect()
{}

Effect::~Effect()
{}


void Effect::Update()
{
	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();
}

void Effect::Draw()
{
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
}