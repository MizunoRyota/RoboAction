#include"DxLib.h"
#include"Camera.h"
#include"Input.h"
#include"Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
    : angleH(0)
    , angleV(0)
    ,shakeTime(0)
    ,isDamage(true)
    ,position  (VGet(0, 0, 0))
    ,OriginalOffset(VGet(0, 0, 0))
{
    //���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
    SetCameraNearFar(0.10f, 1200.0f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
    // �����Ȃ�.
}

void Camera::Load()
{
    position = VGet(0, Hight, Zoom);
}

void Camera::Update(const Player& player,const Input& input)
{
    if (CheckHitKey(KEY_INPUT_LSHIFT) || (input.GetNowFrameInput() & PAD_INPUT_C))
    {
        // �u���v�{�^����������Ă����琅���p�x���}�C�i�X����
        if (input.GetNowFrameInput() & PAD_INPUT_LEFT)
        {
            angleH -= camaeraSpeed;

            // �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
            if (angleH < -DX_PI_F)
            {
                angleH += DX_TWO_PI_F;
            }
        }

        // �u���v�{�^����������Ă����琅���p�x���v���X����
        if (input.GetNowFrameInput() & PAD_INPUT_RIGHT)
        {
            angleH += camaeraSpeed;

            // �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
            if (angleH > DX_PI_F)
            {
                angleH -= DX_TWO_PI_F;
            }
        }

        // �u���v�{�^����������Ă����琂���p�x���}�C�i�X����
        if (input.GetNowFrameInput() & PAD_INPUT_UP)
        {
            angleV -= camaeraSpeed;

            // ������p�x�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
            if (angleV < -DX_PI_F * 0.5f + 0.6f)
            {
                angleV = -DX_PI_F * 0.5f + 0.6f;
            }
        }

        // �u���v�{�^����������Ă����琂���p�x���v���X����
        if (input.GetNowFrameInput() & PAD_INPUT_DOWN)
        {
            angleV += camaeraSpeed;

            // ������p�x�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
            if (angleV > DX_PI_F * 0.5f - 0.6f)
            {
                angleV = DX_PI_F * 0.5f - 0.6f;
            }
        }
    }
    // z����ŁA�v���C���[�����苗�����ꂽ��ԂŃv���C���[����Ɍ�������悤�ʒu����
    // �J�����Ɉʒu�𔽉f.
    if (player.GetIsBeAttack())
    {
        ShakeCamera(shakeIntensity, shakeDuration,player);
    }
    else
    {
        position = VAdd(player.GetPos(), VGet(-0.0f, Hight, Zoom));
    }

    targetposition = VAdd(player.GetPos(), VGet(-0.0f, TargetHight, 0.0f));

    FixCameraPosition();

    // �J�����Ɉʒu�𔽉f.
    SetCameraPositionAndTarget_UpVecY(position, targetposition);

}

void Camera::FixCameraPosition()
{
    // ���������̉�]�͂x����]
    auto rotY = MGetRotY(angleH);

    // ���������̉�]�͂y����] )
    auto rotZ = MGetRotZ(angleV);

    // �J��������v���C���[�܂ł̏����������Z�b�g
    float cameraPlayerLength = Zoom;

    // �J�����̍��W���Z�o
    // �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
    // ����������]( �y����] )���������Ɛ���������]( �x����] )���čX��
    // �����_�̍��W�𑫂������̂��J�����̍��W
    position = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), targetposition);

    if (position.y<=0)
    {
        position.y = 0.50f;
    }

}

void Camera::ShakeCamera(float intensity, float duration,const Player& player)
{

    if (shakeTime < duration)
    {
        // �����_���ȗh��𐶐�
        Offset.x = (rand() % 3 - 1) * intensity / 100.0f;
        Offset.y = (rand() % 3 - 1) * intensity / 100.0f;
        Offset.z = (rand() % 3 - 1) * intensity / 100.0f;

        // �J�����ʒu���X�V
        position=VGet(position.x + Offset.x, position.y + Offset.y, position.z + Offset.z);

        // ���Ԃ�i�߂�
        shakeTime += 0.50f;
    }
    else
    {
        // �h�ꂪ�I�������猳�̈ʒu�ɖ߂�
        position = VAdd(player.GetPos(), VGet(-0.0f, Hight, Zoom));
        shakeTime = 0.0f;
        isDamage = false;
    }
}