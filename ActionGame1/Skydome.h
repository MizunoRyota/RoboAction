#pragma once

class Skydome
{
public:
	Skydome();
	~Skydome();
	void SkydomeUpdate();	//�Q�[�����̍X�V
	void SkydomeTitle();	//�Q�[���^�C�g���̍X�V
	void SkydomeDraw();		//�X�J�C�h�[���̕`��
private:
	int SkydomeHandle;		//���f���n���h��
	VECTOR pos;				//�|�W�V����
	VECTOR	dir;			// ��]����.
	int Key;
	// �ÓI�萔.
	static constexpr float Scale = 1.0f;		//�傫��

};