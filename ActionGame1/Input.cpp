#include "DxLib.h"
#include "Input.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Input::Input()
	: nowFrameInput(0)
	, nowFrameNewInput(0)
{
	// �����Ȃ�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Input::~Input()
{
	// �����Ȃ�
}

/// <summary>
/// �X�V
/// </summary>
void Input::Update()
{
	// �ЂƂO�̃t���[���̓��͂�ϐ��ɂƂ��Ă���
	int Old = nowFrameInput;

	// ���݂̓��͏�Ԃ��擾
	nowFrameInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	clsDx();
	printfDx("%d", nowFrameInput);
	// ���̃t���[���ŐV���ɉ����ꂽ�{�^���̃r�b�g���������Ă���l�� nowFrameNewInput �ɑ������
	nowFrameNewInput = nowFrameInput & ~Old;
}

bool Input::IsInputAnalogKey(const AnalogKeyState analogKeyState)
{
    // �A�i���O�L�[�̏c���̓��͒l��p��
    int inputX = 0;
    int inputY = 0;

    // ���͂���Ă��邩
    bool isInput = false;

    // ���ꂼ��̓��͂��`�F�b�N
    GetJoypadAnalogInputRight(&inputX, &inputY, DX_INPUT_PAD1);

    // �ǂ̃A�i���O�L�[���`�F�b�N�������̂����݂Ă��ꂪ�|����Ă��邩������
    switch (analogKeyState)
    {
    case Right:
        if (inputX > AnalogKeyDeadZone)
        {
            isInput = true;
        }
        break;
    case Left:
        if (inputX < -AnalogKeyDeadZone)
        {
            isInput = true;
        }
        break;
    case Up:
        if (inputY < -AnalogKeyDeadZone)
        {
            isInput = true;
        }
        break;
    case Down:
        if (inputY > AnalogKeyDeadZone)
        {
            isInput = true;
        }
        break;
    default:
        break;
    }

    return isInput;
}