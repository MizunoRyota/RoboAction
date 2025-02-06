#include"DxLib.h"
#include"Pallet.h"
#include"Enemy.h"
#include"Player.h"
#include"EnergyBall.h"
#include"OnAttackedEnemyHit.h"

OnAttackedEnemy::OnAttackedEnemy()
	:energyCircle(VGet(0, 0, 0))
	, keepDistance(VGet(0, 0, 0))
	, enemyCircle(VGet(0, 0, 0))
	, energyRadius(1.5f)
	, energyHight(0.0f)
	, enemyRadius(2.0f)
	, PlayerAttackPosition(VGet(0, 0, 0))
	,attackAngle(VGet(0, 0, 0))
	, playerAttackRadius(0.5f)
	, ballAttackDistance(0.0f)
	, AngleVec(VGet(0, 0, 0))
	, attackDistance(1.0f)
	, isOnAttack(false)
	, isBallHit(false)
	, Distance(0)
	, Length(0)
{
}

OnAttackedEnemy::~OnAttackedEnemy()
{
}

void OnAttackedEnemy::Update(const Energy& ball, const Enemy& enemy,const Player& player)
{
	energyCircle = VAdd(ball.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
	enemyCircle = VAdd(enemy.GetPos(), VGet(0.0f, PlayerHight, 0.0f));
	attackAngle = VAdd(player.GetDirection(), VGet(0.0f, 0.0f, 0.0f));
	attackAngle = VScale(attackAngle, attackDistance);
	PlayerAttackPosition = VAdd(player.GetPos(), attackAngle);
	CheckOnBallHit(player, ball);
    CheckOnAttackHit(ball, enemy);
}

bool OnAttackedEnemy::CheckOnAttackHit(const Energy& ball, const Enemy& enemy)
{
	if (ball.GetisIsBlowAway())
	{
		//プレイヤーとEnemyの距離の合計を獲得
		keepDistance = VSub(ball.GetPos(), enemyCircle);
		//プレイヤーとEnemyの半径の合計
		Length = energyRadius + enemyRadius;
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

bool OnAttackedEnemy::CheckOnBallHit(const Player& player, const Energy& ball)
{
	if (player.GetisIsAttack())
	{

		keepBallAttackDistance = VSub(ball.GetPos(), PlayerAttackPosition);

		attackBallLength = playerAttackRadius + energyRadius;

		ballAttackDistance = VSquareSize(keepBallAttackDistance);

		if (ballAttackDistance <= (attackBallLength * attackBallLength))
		{
			return isBallHit = true;
		}

	}
	if (!ball.GetisLimitRange())
	{
		return isBallHit = false;
	}
}

void OnAttackedEnemy::Draw()
{
	//DrawSphere3D(energyCircle, energyRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
	//DrawSphere3D(enemyCircle, enemyRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
	//DrawSphere3D(PlayerAttackPosition, playerAttackRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
}