#include"DxLib.h"
#include"Pallet.h"
#include"Player.h"
#include"Enemy.h"
#include"HitChecker.h"

HitChecker::HitChecker()
//�v���C���[�̔���
    :playerRadius(1.00f)
    , playerCircle(VGet(0, 0, 0))
    //Enemy�̔���
    , enemyRadius(2.0f)
    , enemyCircle(VGet(0, 0, 0))
    //�������Ă��邩
    , isHit(false)
    , Length (0)
{
    //�����Ȃ�
}

HitChecker::~HitChecker()
{
}

void HitChecker::Update(const Player& player,const Enemy& enemy  )
{
    //�v���C���[�̋�
    playerCircle = VAdd(player.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //Enemy�̋�
    enemyCircle = VAdd(enemy.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //�������Ă��邩�̃`�F�b�N
    isHit = CheckHit(player, enemy);

}

bool HitChecker::CheckHit(const Player& player, const Enemy& enemy)
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

void HitChecker::DrawCircle()
{
    if (CheckHitKey(KEY_INPUT_F))
    {
        clsDx();
        printfDx("isHit%d\n", isHit);
        printfDx("Distance%f\n", Distance);
        printfDx("Length%f\n",Length),
        DrawSphere3D(playerCircle, playerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
        DrawSphere3D(enemyCircle, enemyRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    }
}

