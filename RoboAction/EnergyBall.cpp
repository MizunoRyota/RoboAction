#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Enemy.h"
#include"Player.h"
#include"OnAttackedEnemyHit.h"
#include"EnergyBall.h"
#include"Sound.h"
Energy::Energy()
	:position(VGet(0.0f, -4.0f, 0.0f))
    , shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
    , shadowToppos(VGet(0.0f, 0.0f, 0.0f))
    , isBallSporn(false)
	, limitRange(15.0f)
	, isBlowAway(false)
	, isDrop(false)
    , ShadowRad(0.75f)
	, moveSpeed(0.4f)
	, dropTime(0)
    , time(0)
{}

Energy::~Energy()
{
}

void Energy::Load()
{
	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	EnergyBallHandle = LoadEffekseerEffect("data/effekseer/EfkFile/EnergyBall.efkefc", 1.0f);
    ExplosionHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Explosion.efkefc", 1.5f);
	SetScalePlayingEffekseer3DEffect(EnergyBallHandle, EffektScale, EffektScale, EffektScale);
	SetScalePlayingEffekseer3DEffect(ExplosionHandle, EffektScale, EffektScale, EffektScale);
}

void Energy::LimitRange()
{
    ////���S����v���C���[�̋����𑪂�

    float r = VSize(VSub(position, VGet(0, 0, 0)));

    ////���̋����ɒB�����炻��ȏア���Ȃ��悤�ɂ���

    if (r > limitRange || r < -limitRange)
    {
        printfDx("limitRange%f\n", r);

        //���S���W����v���C���[���W�̋���

        VECTOR distance = VSub(VGet(0, 0, 0), position);

        //���K��

        distance = VNorm(distance);

        //�߂��ʂ��v�Z�A���Z����

        VECTOR returnPosition = VScale(distance, (r - limitRange));

        position = VAdd(position, returnPosition);

		position = VGet(0, -4.0f,0);
		isBlowAway = false;
        isLimitRange = true;
		isBallSporn = false;
		isDrop = false;
    }
    else
    {
        isLimitRange = false;
    }
}

void Energy::BallSporn(const Enemy& enemy)
{
    if (enemy.GetChaseCount() == 2 )
    {
		isDrop = true;
    }
}

void Energy::DropTimer(const Enemy& enemy)
{
	if (isDrop&&!isBallSporn)
	{
        // ����̌Ăяo�����ɊJ�n������ݒ�
        if (dropTime == 0)
        {
            dropTime = GetNowCount();  // �~���b�P�ʂŌ��ݎ������擾
        }
        // �o�ߎ��Ԃ�3000�~���b(3�b)�ȏ�o�߂�����t���O��؂�ւ���
        if (GetNowCount() - dropTime >= 1000)
        {
            dropTime = 0;
			position = VAdd(enemy.GetPos(),VGet(0.0f,6.0f,0.0f));
			isDrop = false;
			isBallSporn = true;
        }
	}
    else
    {
        if (position.y>=1.0f&&!isBlowAway)
        {
			position.y -= 0.1f;
        }
    }
}

void Energy::Update(const Enemy& enemy, const Player& player, const OnAttackedEnemy& onAttacked)
{
    BallSporn(enemy);
	DropTimer(enemy);
	ChangeBlowAway(player, onAttacked);
	BlowAway(player, onAttacked);
    LimitRange();
    UpdateEffect();
    UpdateShadow();
}

void Energy::ChangeBlowAway(const Player& player, const OnAttackedEnemy& onAttacked)
{
	if (onAttacked.GetisBallHit())
	{
		isBlowAway = true;
	}
}

void Energy::BlowAway(const Player& player, const OnAttackedEnemy& onAttacked)
{
    if (isBlowAway)
    {
        AngleVec = VNorm(AngleVec);
        AngleVec = VScale(AngleVec, moveSpeed);
        position = VAdd(position, AngleVec);
        if (position.y<=3) {
            position.y += 0.05f;
        }
    }
    else
    {
        AngleVec = VAdd(player.GetDirection(), VGet(0.0f, 0.0f, 0.0f));
    }
}

void Energy::UpdateEffect()
{
    if (isBallSporn)
    {
        // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
        Effekseer_Sync3DSetting();

        // ����I�ɃG�t�F�N�g���Đ�����
        // �G�t�F�N�g���Đ�����B
        if (time % 60 == 0)
        {
            StopEffekseer3DEffect(playingEffectHandle);
            playingEffectHandle = PlayEffekseer3DEffect(EnergyBallHandle);
        }

        SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
        // ���Ԃ��o�߂�����B
        time++;
    }
    else
    {
		StopEffekseer3DEffect(playingEffectHandle);
    }
}

void Energy::UpdateShadow()
{
    shadowToppos = VGet(position.x, -0.01, position.z);
    shadowBottompos = VGet(position.x, 0, position.z);
}

void Energy::DrawShadow()
{
    DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
}

void Energy::Draw()
{
    if (isBallSporn)
    {
        DrawShadow();
    }
}