#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include <cmath>
#include"Sound.h"
#include"Pallet.h"
#include"Enemy.h"
#include"Gimmick.h"

Gimmick::Gimmick(VECTOR Setposition)
    :position(Setposition)
    , Resetposition(Setposition)
    , shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
    , shadowToppos(VGet(0.0f, 0.0f, 0.0f))
    , GimmickHandle(0)
    , ShadowRad(0.75f)
    , dropTime(0)
    , time(1)
    , moveSpeed(0.4f)
    , isGimmickSporn(false)
    , endDropTime(10.0f)
    , isOrigin(false)
    , moveTime(0)
    , GimmickModelHandle(0)
    , modelPosition(VGet(0.0f, 0.0f, 0.0f))
    , returnEnemyPos(false)
    ,angle(0)
{
	GimmickModelHandle = MV1LoadModel("data/model/Gimmick/Gimmick.mv1");
    GimmickHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Smoke.efkefc", 1.2f);
    SetScalePlayingEffekseer3DEffect(GimmickHandle, EffektScale, EffektScale, EffektScale);
    // 3D���f���̃X�P�[������
    MV1SetScale(GimmickModelHandle, VGet(ModelScale, ModelScale, ModelScale));
    // �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
    MV1SetRotationXYZ(GimmickModelHandle, VGet(29.8f + DX_PI_F, 0.0f, 0.0f));
}

Gimmick::~Gimmick()
{
}

void Gimmick::Load()
{
    //position = VGet(0.0f, 0.0f, 0.0f);
}

void Gimmick::Update(const Enemy& enemy)
{
    DropTimer(enemy);
    UpdateMove(enemy);
    // �G�t�F�N�g�̍X�V
    UpdateEffect(enemy);
    UpdateShadow();
    if (!isGimmickSporn)
    {
        // �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
        ReturnGimmickPos(enemy);
        UpdateAngle(enemy);
    }
    else
    {
        // �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
        MV1SetRotationXYZ(GimmickModelHandle, VGet(29.8f + DX_PI_F, 0.0f, 0.0f));
    }
}

void Gimmick::ReturnGimmickPos(const Enemy& enemy)
{
    position = VGet(enemy.GetPos().x,enemy.GetPos().y-5.5f,enemy.GetPos().z);
}

void Gimmick::UpdateAngle(const Enemy& enemy)
{
    // atan2 ���g�p���Ċp�x���擾
    angle = enemy.GetFloatAngle();
    MV1SetRotationXYZ(GimmickModelHandle, VGet(29.0f + DX_PI_F, angle + DX_PI_F, 0.0f));
}

void Gimmick::UpdateMove(const Enemy& enemy)
{
    UpdateMoveCircle(enemy);
    MoveOriginPosition(enemy);
    MoveResetPosition(enemy);
    modelPosition = VGet(position.x, position.y + 10.0f, position.z);
    MV1SetPosition(GimmickModelHandle, modelPosition);
}

void Gimmick::DropTimer(const Enemy& enemy)
{
    if (enemy.GetIsAttack()&&!isGimmickSporn&&enemy.GetHp()<5)
    {
        // ����̌Ăяo�����ɊJ�n������ݒ�
        if (dropTime == 0)
        {
            dropTime = GetNowCount();  // �~���b�P�ʂŌ��ݎ������擾
        }
        // �o�ߎ��Ԃ�200�~���b(3�b)�ȏ�o�߂�����t���O��؂�ւ���
        if (GetNowCount() - dropTime >= endDropTime)
        {
			isGimmickSporn = true;
        }
    }
}

void Gimmick::MoveOriginPosition(const Enemy& enemy)
{
    ////���S����v���C���[�̋����𑪂�

    float r = VSize(VSub(position, VGet(0, 0, 0)));

    ////���̋����ɒB�����炻��ȏア���Ȃ��悤�ɂ���
    if (enemy.GetHp() == 3  && isGimmickSporn && !isOrigin)
    {
		position = Resetposition;
    }

    if (enemy.GetHp() <= 2 && isGimmickSporn && !isOrigin)
    {
        if (r > returnRange || r < -returnRange)
        {

            //���S���W����v���C���[���W�̋���

            VECTOR distance = VSub(VGet(0, 0, 0), position);

            //���K��

            distance = VNorm(distance);

            //�߂��ʂ��v�Z�A���Z����

            VECTOR returnPosition = VScale(distance, 0.1f);

            position = VAdd(position, returnPosition);

        }
        if (position.x >= 0 && position.x <= 0.05)
        {
            isOrigin = true;
        }
    }
}

void Gimmick::MoveResetPosition(const Enemy& enemy)
{
    if (isOrigin && isGimmickSporn)
    {

        //���S���W����v���C���[���W�̋���

        VECTOR distance = VSub(Resetposition, position);

        //���K��

        distance = VNorm(distance);

        //�߂��ʂ��v�Z�A���Z����

        VECTOR returnPosition = VScale(distance, 0.1f);

        position = VAdd(position, returnPosition);
        if (position.x == Resetposition.x && position.z == Resetposition.z)
        {
            isOrigin = false;
        }
    }

}

void Gimmick::UpdateMoveCircle(const Enemy& enemy)
{
    if (enemy.GetHp() == 4 && isGimmickSporn && !isOrigin)
    {
        // ���Ԃ��g���Ċp�x���v�Z
        float moveAngle = moveTime * AngleSpeed;

        // �V�����ʒu���v�Z
        position.x = Radius * cos(moveAngle);
        position.z = Radius * sin(moveAngle);
        position.y = 0.0f; // y���W�͌Œ�

        // ���Ԃ�i�߂�
        moveTime++;
    }
}

void Gimmick::UpdateEffect(const Enemy& enemy)
{
    if (isGimmickSporn&& enemy.GetHp() < 5)
    {
        // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
        Effekseer_Sync3DSetting();

        // ����I�ɃG�t�F�N�g���Đ�����
        // �G�t�F�N�g���Đ�����B
        if (time % 60 == 0)
        {
            StopEffekseer3DEffect(playingEffectHandle);
            playingEffectHandle = PlayEffekseer3DEffect(GimmickHandle);
			isGimmickSporn = false;
        }

        SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y+0.0f, position.z);
        // ���Ԃ��o�߂�����B
        time++;
    }
    else
    {
        StopEffekseer3DEffect(playingEffectHandle);
    }
}

void Gimmick::UpdateShadow()
{
    shadowToppos = VGet(position.x, -0.01f, position.z);
    shadowBottompos = VGet(position.x, 0.0f, position.z);
}

void Gimmick::Draw()
{
    if (isGimmickSporn)
    {
        DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
    }
    if (!returnEnemyPos)
    {
		MV1DrawModel(GimmickModelHandle);
    }
}