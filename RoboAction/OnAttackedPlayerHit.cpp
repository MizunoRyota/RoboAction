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
    //Enemyの判定
    , enemyRadius(2.0f)
    , enemyCircle(VGet(0, 0, 0))
    //当たっているか
    , Length(0)
    , isOnAttack(false)
{
}

OnAttackedPlayer::~OnAttackedPlayer()
{
}

void OnAttackedPlayer::Update(const Player& player, const Enemy& enemy)
{
    //プレイヤーの球
    playerCircle = VAdd(player.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
    //Enemyの球
    enemyCircle = VAdd(enemy.GetPos(), VGet(0.0f, PlayerHight, 0.0f));

    CheckBeAttackHit(player, enemy);

}

bool OnAttackedPlayer::CheckBeAttackHit(const Player& player, const Enemy& enemy)
{
    if (enemy.GetIsAttack())
    {
        //プレイヤーとEnemyの距離の合計を獲得
        keepDistance = VSub(playerCircle, enemyCircle);
        //プレイヤーとEnemyの半径の合計
        Length = playerRadius + enemyRadius;
        //ベクトルを2乗
        Distance = VSquareSize(keepDistance);
        //LengthよりDistanceちいさくなったとき返す
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