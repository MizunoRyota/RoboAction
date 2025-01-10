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
    //プレイヤーとEnemyの距離の合計を獲得
    keepDistance = VSub(player.GetPos(), enemy.GetPos());
    //プレイヤーとEnemyの半径の合計
    Length = playerRadius + enemyRadius;
    //ベクトルを2乗
    Distance = VSquareSize(keepDistance);
    //LengthよりDistanceちいさくなったとき返す
    return Distance <= (Length * Length);
}