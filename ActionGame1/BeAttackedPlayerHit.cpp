#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Enemy.h"
#include"HitChecker.h"
#include"BeAttackedPlayerHit.h"
#include"Player.h"

BeAttackedPlayer::BeAttackedPlayer()
{
}

BeAttackedPlayer::~BeAttackedPlayer()
{
}

bool BeAttackedPlayer::CheckBeAttackHit(const Player& player, const Enemy& enemy)
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