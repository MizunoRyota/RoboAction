#pragma once

class Effect
{
public:
	Effect();
	~Effect();
	void Load();	//������
	void Update();

	void Draw();	//�`��
	void StopDraw();
private:
	//int effectHandle;
	//// ���ł������̂ŉ摜��ǂݍ��ށB
	//int grBackgroundHandle;
	//int grFrontHandle;
	//// �G�t�F�N�g�̕\������ʒu��ݒ肷��B
	//VECTOR effectPosition;
	//// ���Ԃ�����������(����I�ɃG�t�F�N�g���Đ����邽��)
	//int time;

	//// �t���X�N���[���؂�ւ��p�t���O��ݒ肷��B(F1�AF2�ŃE�C���h�E�A�t���X�N���[����؂�ւ����悤�ɂ���B)
	//bool isFullScreen = false;

	//// �Đ����̃G�t�F�N�g�̃n���h��������������B
	//int playingEffectHandle = -1;
};