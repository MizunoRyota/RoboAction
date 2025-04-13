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
    //プレイヤーの球
    playerCircle = VAdd(player.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //Enemyの球
    enemyCircle = VAdd(gimmick.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //当たっているかのチェック
    isHit = CheckHit(player, gimmick);
}

bool OnGimmick::CheckHit(const Player& player, const Gimmick& gimmick)
{
    if (gimmick.GetIsGimmickSporn())
    {
        //プレイヤーとEnemyの距離の合計を獲得
        keepDistance = VSub(player.GetPos(), gimmick.GetPos());
        //プレイヤーとEnemyの半径の合計
        Length = playerRadius + gimmickRadius;
        //ベクトルを2乗
        Distance = VSquareSize(keepDistance);
        //LengthよりDistanceちいさくなったとき返す
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