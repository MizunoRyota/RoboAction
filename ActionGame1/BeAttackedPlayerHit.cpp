#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Enemy.h"
#include"BeAttackedPlayerHit.h"
#include"Player.h"

BeAttackedPlayer::BeAttackedPlayer()
    :playerRadius(1.00f)
    , playerCircle(VGet(0, 0, 0))
    //Enemyの判定
    , enemyRadius(2.0f)
    , enemyCircle(VGet(0, 0, 0))
    //当たっているか
    , Length(0)
    , IsBeAttack(false)
{
}

BeAttackedPlayer::~BeAttackedPlayer()
{
}

void BeAttackedPlayer::Update(const Player& player, const Enemy& enemy)
{
    //プレイヤーの球
    playerCircle = VAdd(player.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //Enemyの球
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
        //プレイヤーとEnemyの距離の合計を獲得
        keepDistance = VSub(player.GetPos(), enemy.GetPos());
        //プレイヤーとEnemyの半径の合計
        Length = playerRadius + enemyRadius;
        //ベクトルを2乗
        Distance = VSquareSize(keepDistance);
        //LengthよりDistanceちいさくなったとき返す
        return Distance <= (Length * Length);
    }
}