#include"DxLib.h"
#include"Camera.h"
#include"Input.h"
#include"Enemy.h"
#include"Player.h"
#include"HitChecker.h"
#include"EnemyAttackRangeChecker.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
    :OriginalOffset(VGet(0, 0, 0))
    ,position  (VGet(0, 0, 0))
    , AngleVec(VGet(0, 0, 0))
    ,isShake(false)
    ,isDamage(true)
    ,shakeTime(0)
{
    //���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
    SetCameraNearFar(0.10f, 500.0f);
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
    isShake=false;
    isDamage=true;
    shakeTime = 0;
}

void Camera::Update(const Player& player,const Input& input, const Enemy& enemy, const EnemyAttackRangeChecker& attackRange)
{

    //// �u���v�{�^����������Ă����琅���p�x���}�C�i�X����
    //if (rightInput->IsInputAnalogKey(Input::AnalogLeft))
    //{
    //    angleHorizontal += AngleSpeed;

    //    // �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
    //    if (angleHorizontal > DX_PI_F)
    //    {
    //        angleHorizontal -= DX_TWO_PI_F;
    //    }
    //}

    //// �u���v�{�^����������Ă����琅���p�x���v���X����
    //if (rightInput->IsInputAnalogKey(Input::AnalogRight))
    //{
    //    angleHorizontal -= AngleSpeed;

    //    // �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
    //    if (angleHorizontal < -DX_PI_F)
    //    {
    //        angleHorizontal += DX_TWO_PI_F;
    //    }
    //}

    //// �u���v�{�^����������Ă����琂���p�x���}�C�i�X����
    //if (rightInput->IsInputAnalogKey(Input::AnalogUp))
    //{
    //    angleVertical += AngleSpeed;

    //    //// ������p�x�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
    //    if (angleVertical > DX_PI_F * 0.5f - 0.6f)
    //    {
    //        angleVertical = DX_PI_F * 0.5f - 0.6f;
    //    }
    //}

    //// �u���v�{�^����������Ă����琂���p�x���v���X����
    //if (rightInput->IsInputAnalogKey(Input::AnalogDown))
    //{
    //    angleVertical -= AngleSpeed;

    //    //// ������p�x�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
    //    if (angleVertical < -DX_PI_F * 0.5f + 0.6f)
    //    {
    //        angleVertical = -DX_PI_F * 0.5f + 0.6f;
    //    }
    //}

    if (!attackRange.GetisShortWithin())
    {

        if (enemy.GetIsExplosion()/*||player.GetisOnAttack()*/)
        {
            isShake = true;
        }
        // z����ŁA�v���C���[�����苗�����ꂽ��ԂŃv���C���[����Ɍ�������悤�ʒu����
        // �J�����Ɉʒu�𔽉f.
        if (isShake)
        {
            ShakeCamera(shakeIntensity, shakeDuration, player);
        }
        else
        {
            AngleVec = VSub(player.GetPos(), enemy.GetPos());
            AngleVec = VNorm(AngleVec);
            AngleVec = VScale(AngleVec, Distance);
            position = VAdd(player.GetPos(), AngleVec);
            position.y = Hight;
        }

        targetposition = VAdd(enemy.GetPos(), VGet(-0.0f, TargetHight, 0.0f));

        //FixCameraPosition();

        // �J�����Ɉʒu�𔽉f.
        SetCameraPositionAndTarget_UpVecY(position, targetposition);
    }

}

void Camera::ReadyUpdate(const Player& player)
{
    position = VGet(-1.0f, 0.5f, -3.0f);
    targetposition = VAdd(player.GetPos(), VGet(-1.0f, 0.3f, 0.0f));
    //FixCameraPosition();
    // �J�����Ɉʒu�𔽉f.
    SetCameraPositionAndTarget_UpVecY(position, targetposition);
}
void Camera::GameTitle(const Player& player) 
{
    position = VGet(-1.0f, 0.5f, -3.0f);
    targetposition = VAdd(player.GetPos(), VGet(-1.0f, 0.3f, 0.0f));
    //FixCameraPosition();
    // �J�����Ɉʒu�𔽉f.
    SetCameraPositionAndTarget_UpVecY(position, targetposition);
}

void Camera::GameEnd(const Enemy& enemy)
{
	position = VGet(-1.0f, 2.3f, -3.6f);
	targetposition = VAdd(enemy.GetPos(), VGet(-0.30f, 3.3f, 0.0f));

	//FixCameraPosition();
	// �J�����Ɉʒu�𔽉f.
	SetCameraPositionAndTarget_UpVecY(position, targetposition);
}

void Camera::GameClear(const Enemy& enemy)
{
	position = VGet(-1.0f, 4.3f, -3.0f);
	targetposition = VAdd(enemy.GetPos(), VGet(-0.30f, 3.3f, 0.0f));
	//FixCameraPosition();
	// �J�����Ɉʒu�𔽉f.
	SetCameraPositionAndTarget_UpVecY(position, targetposition);
}

void Camera::FixCameraPosition()
{
    // ���������̉�]�͂x����]
    auto rotY = MGetRotY(angleHorizontal);

    // ���������̉�]�͂y����] )
    auto rotZ = MGetRotZ(angleVertical);

    // �J��������v���C���[�܂ł̏����������Z�b�g
    float cameraPlayerLength = Zoom;

    // �J�����̍��W���Z�o
    // �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
    // ����������]( �y����] )���������Ɛ���������]( �x����] )���čX��
    // �����_�̍��W�𑫂������̂��J�����̍��W
    position = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), targetposition);

    //if (position.y<=0)
    //{
    //    position.y = 0.50f;
    //}

}

void Camera::ShakeCamera(float intensity, float duration,const Player& player)
{
    if (shakeTime < duration)
    {

        // �����_���ȗh��𐶐�
        Offset.x = (rand() % 5 - 1) * intensity / 100.0f;
        Offset.y = (rand() % 5 - 1) * intensity / 100.0f;
        Offset.z = (rand() % 5 - 1) * intensity / 100.0f;

        // �J�����ʒu���X�V
        position=VGet(position.x + Offset.x, position.y + Offset.y, position.z + Offset.z);

        // ���Ԃ�i�߂�
        shakeTime += 0.20f;

    }
    else
    {
        // �h�ꂪ�I�������猳�̈ʒu�ɖ߂�
        position = VAdd(player.GetPos(), VGet(-0.0f, Hight, Zoom));
        shakeTime = 0.0f;
        isDamage = false;
        isShake = false;
    }
}