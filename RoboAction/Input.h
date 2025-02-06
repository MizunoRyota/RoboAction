#pragma once

/// <summary>
/// ����
/// </summary>
class Input
{
public:

	/// <summary>
	/// �A�i���O�L�[�̃X�e�[�g
	/// </summary>
	enum AnalogKeyState
	{
		AnalogRight = 1,    //�E
		AnalogLeft = 2,     //��
		AnalogUp = 3,       //��
		AnalogDown = 4,     //��
	};
	//�L�[�̎��
	enum KeyKinds
	{
		Move = 0,  //�ړ��L�[�̂ǂꂩ
		Left = 1,  //�E
		Right = 2,  //��
		Up = 3,  //��
		Down = 4,  //��
		Space = 5,  //�X�y�[�X
		LB = 6,  //����̎�O�̃{�^��
		LT = 7,  //����̉����̃{�^��
		RB = 8,  //�E��̎�O�̃{�^��
		RT = 9,  //�E�����̃{�^��
		X = 10,
		Y = 11,
		A = 12,
		B = 13,
		LeftStick = 14,  //���X�e�B�b�N��������
		None = 15,  //�g�p���Ȃ��L�[�������͉�����Ă��Ȃ�
	};
	Input();
	~Input();

	void	Update();
	bool IsInputAnalogKey(const AnalogKeyState analogKeyState);
	int GetNowFrameInput() const { return nowFrameInput; }
	int GetNowFrameNewInput() const { return nowFrameNewInput; }

private:

	static constexpr int AnalogKeyDeadZone = 200;     // �X�e�B�b�N��|���Ă������������Ȃ��̈�

	int		nowFrameInput;				// ���݂̃t���[���ŉ�����Ă���{�^��
	int		nowFrameNewInput;			// ���݂̃t���[���ŐV���ɉ����ꂽ�{�^��
	int     rightAnalogKeyX;       // �E�̃A�i���O�L�[�̉������̏��
	int     rightAnalogKeyY;       // �E�̃A�i���O�L�[�̏c�����̏��
};
