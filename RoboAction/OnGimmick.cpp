#include"DxLib.h"
#include"Pallet.h"
#include"Player.h"
#include"Gimmick.h"
#include"OnGimmick.h"

OnGimmick::OnGimmick()
	:playerCircle(VGet(0, 0, 0))
	, enemyCircle(VGet(0, 0, 0))
	, keepDistance(VGet(0, 0, 0))
	, Distance(0)
	, Length(0)
	, isHit(false)
	, isOnGimmick(false)

{
}

OnGimmick::~OnGimmick()
{
}

void OnGimmick::Update(const Player& player, const Gimmick& gimmick)
{
    //�v���C���[�̋�
    playerCircle = VAdd(player.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //Enemy�̋�
    enemyCircle = VAdd(gimmick.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //�������Ă��邩�̃`�F�b�N
    isHit = CheckHit(player, gimmick);
}

bool OnGimmick::CheckHit(const Player& player, const Gimmick& gimmick)
{
    if (gimmick.GetIsGimmickSporn())
    {
        //�v���C���[��Enemy�̋����̍��v���l��
        keepDistance = VSub(player.GetPos(), gimmick.GetPos());
        //�v���C���[��Enemy�̔��a�̍��v
        Length = playerRadius + gimmickRadius;
        //�x�N�g����2��
        Distance = VSquareSize(keepDistance);
        //Length���Distance���������Ȃ����Ƃ��Ԃ�
        if (Distance <= (Length * Length))
        {
            return  isOnGimmick = true;
        }

        if (!Distance <= (Length * Length))
        {
            return isOnGimmick = false;
        }
    }
}

void OnGimmick::DrawCircle()
{
    if (CheckHitKey(KEY_INPUT_F))
    {
        clsDx();
        printfDx("isHit%d\n", isHit);
        printfDx("Distance%f\n", Distance);
        printfDx("Length%f\n", Length),
        DrawSphere3D(playerCircle, playerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
        DrawSphere3D(enemyCircle, gimmickRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    }
}