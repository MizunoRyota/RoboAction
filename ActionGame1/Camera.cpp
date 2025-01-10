#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Player.h"
#include"Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
    :Zoom  (0)
    ,Hight  (0)
    ,shakeTime(0)
    ,isDamage(true)
    ,TargetHight(1.3f)
    ,position  (VGet(0, 0, 0))
    ,OriginalOffset(VGet(0, 1.50f, -5.0f))
{
    //���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
    SetCameraNearFar(0.10f, 1000.0f);
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
    Hight = 1.5f;
    Zoom = -4.0f;
    position = VGet(0, Hight, Zoom);
}

void Camera::Update(const Player& player)
{

    // TODO:z����ŁA�v���C���[�����苗�����ꂽ��ԂŃv���C���[����Ɍ�������悤�ʒu����
    // �J�����Ɉʒu�𔽉f.
    targetposition = VAdd(player.GetPos(), VGet(-0.0f, TargetHight, 0.0f));
    if (isDamage)
    {
        ShakeCamera(shakeIntensity, shakeDuration,player);
    }
    else
    {
        position = VAdd(player.GetPos(), VGet(-0.0f, Hight, Zoom));
    }
    // �J�����Ɉʒu�𔽉f.
    SetCameraPositionAndTarget_UpVecY(position, targetposition);

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
        position=VGet(OriginalOffset.x + Offset.x, OriginalOffset.y + Offset.y, OriginalOffset.z + Offset.z);

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