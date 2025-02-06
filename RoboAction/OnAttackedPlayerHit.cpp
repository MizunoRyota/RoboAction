#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Enemy.h"
#include"OnAttackedPlayerHit.h"
#include"Player.h"

OnAttackedPlayer::OnAttackedPlayer()
    :playerRadius(1.00f)
	, Distance(10)
	, keepDistance(VGet(0, 0, 0))
    , playerCircle(VGet(0, 0, 0))
    //Enemy�̔���
    , enemyRadius(2.0f)
    , enemyCircle(VGet(0, 0, 0))
    //�������Ă��邩
    , Length(0)
    , isOnAttack(false)
{
}

OnAttackedPlayer::~OnAttackedPlayer()
{
}

void OnAttackedPlayer::Update(const Player& player, const Enemy& enemy)
{
    //�v���C���[�̋�
    playerCircle = VAdd(player.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //Enemy�̋�
    enemyCircle = VAdd(enemy.GetPos(), VGet(0.0f, PlayerHight, 0.0f));

    CheckBeAttackHit(player, enemy);

}

bool OnAttackedPlayer::CheckBeAttackHit(const Player& player, const Enemy& enemy)
{
    if (enemy.GetIsAttack())
    {
        //�v���C���[��Enemy�̋����̍��v���l��
        keepDistance = VSub(playerCircle, enemyCircle);
        //�v���C���[��Enemy�̔��a�̍��v
        Length = playerRadius + enemyRadius;
        //�x�N�g����2��
        Distance = VSquareSize(keepDistance);
        //Length���Distance���������Ȃ����Ƃ��Ԃ�
        if (Distance <= (Length * Length))
        {
            return isOnAttack = true;
        }
    }
    if (!Distance <= (Length * Length))
    {
        return isOnAttack = false;
    }
}