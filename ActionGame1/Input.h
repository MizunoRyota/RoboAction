#pragma once

/// <summary>
/// ����
/// </summary>
class Input
{
public:
	Input();
	~Input();

	void	Update();
	XINPUT_STATE input;

	int GetNowFrameInput() const { return nowFrameInput; }
	int GetNowFrameNewInput() const { return nowFrameNewInput; }

private:
	int		nowFrameInput;				// ���݂̃t���[���ŉ�����Ă���{�^��
	int		nowFrameNewInput;			// ���݂̃t���[���ŐV���ɉ����ꂽ�{�^��
};
