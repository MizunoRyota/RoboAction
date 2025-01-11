#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Enemy.h"
#include"BeAttackedPlayerHit.h"
#include"Player.h"

BeAttackedPlayer::BeAttackedPlayer()
    :playerRadius(1.00f)
    , playerCircle(VGet(0, 0, 0))
    //Enemy�̔���
    , enemyRadius(2.0f)
    , enemyCircle(VGet(0, 0, 0))
    //�������Ă��邩
    , Length(0)
    , IsBeAttack(false)
{
}

BeAttackedPlayer::~BeAttackedPlayer()
{
}

void BeAttackedPlayer::Update(const Player& player, const Enemy& enemy)
{
    //�v���C���[�̋�
    playerCircle = VAdd(player.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //Enemy�̋�
    enemyCircle = VAdd(enemy.GetPos(), VGet(0.0f, PlayerHight, 0.0f));

    if (CheckBeAttackHit(player, enemy))
    {
        IsBeAttack = true;
    }
    else
    {
        IsBeAttack = false;
    }
}

bool BeAttackedPlayer::CheckBeAttackHit(const Player& player, const Enemy& enemy)
{
    if (enemy.GetIsAttack())
    {
        //�v���C���[��Enemy�̋����̍��v���l��
        keepDistance = VSub(player.GetPos(), enemy.GetPos());
        //�v���C���[��Enemy�̔��a�̍��v
        Length = playerRadius + enemyRadius;
        //�x�N�g����2��
        Distance = VSquareSize(keepDistance);
        //Length���Distance���������Ȃ����Ƃ��Ԃ�
        return Distance <= (Length * Length);
    }
}