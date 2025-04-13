#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Enemy.h"
#include"Player.h"
#include"OnAttackedEnemyHit.h"
#include"EnergyBall.h"
#include"Sound.h"
Energy::Energy()
	:position(VGet(0.0f, -4.0f, 0.0f))
    , shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
    , shadowToppos(VGet(0.0f, 0.0f, 0.0f))
    , isBallSporn(false)
	, limitRange(15.0f)
	, isBlowAway(false)
	, isDrop(false)
    , ShadowRad(0.75f)
	, moveSpeed(0.4f)
	, dropTime(0)
    , time(0)
{}

Energy::~Energy()
{
}

void Energy::Load()
{
	// エフェクトリソースを読み込む。
	EnergyBallHandle = LoadEffekseerEffect("data/effekseer/EfkFile/EnergyBall.efkefc", 1.0f);
    ExplosionHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Explosion.efkefc", 1.5f);
	SetScalePlayingEffekseer3DEffect(EnergyBallHandle, EffektScale, EffektScale, EffektScale);
	SetScalePlayingEffekseer3DEffect(ExplosionHandle, EffektScale, EffektScale, EffektScale);
}

void Energy::LimitRange()
{
    ////中心からプレイヤーの距離を測る

    float r = VSize(VSub(position, VGet(0, 0, 0)));

    ////一定の距離に達したらそれ以上いけないようにする

    if (r > limitRange || r < -limitRange)
    {
        printfDx("limitRange%f\n", r);

        //中心座標からプレイヤー座標の距離

        VECTOR distance = VSub(VGet(0, 0, 0), position);

        //正規化

        distance = VNorm(distance);

        //戻す量を計算、加算する

        VECTOR returnPosition = VScale(distance, (r - limitRange));

        position = VAdd(position, returnPosition);

		position = VGet(0, -4.0f,0);
		isBlowAway = false;
        isLimitRange = true;
		isBallSporn = false;
		isDrop = false;
    }
    else
    {
        isLimitRange = false;
    }
}

void Energy::BallSporn(const Enemy& enemy)
{
    if (enemy.GetChaseCount() == 2 )
    {
		isDrop = true;
    }
}

void Energy::DropTimer(const Enemy& enemy)
{
	if (isDrop&&!isBallSporn)
	{
        // 初回の呼び出し時に開始時刻を設定
        if (dropTime == 0)
        {
            dropTime = GetNowCount();  // ミリ秒単位で現在時刻を取得
        }
        // 経過時間が3000ミリ秒(3秒)以上経過したらフラグを切り替える
        if (GetNowCount() - dropTime >= 1000)
        {
            dropTime = 0;
			position = VAdd(enemy.GetPos(),VGet(0.0f,6.0f,0.0f));
			isDrop = false;
			isBallSporn = true;
        }
	}
    else
    {
        if (position.y>=1.0f&&!isBlowAway)
        {
			position.y -= 0.1f;
        }
    }
}

void Energy::Update(const Enemy& enemy, const Player& player, const OnAttackedEnemy& onAttacked)
{
    BallSporn(enemy);
	DropTimer(enemy);
	ChangeBlowAway(player, onAttacked);
	BlowAway(player, onAttacked);
    LimitRange();
    UpdateEffect();
    UpdateShadow();
}

void Energy::ChangeBlowAway(const Player& player, const OnAttackedEnemy& onAttacked)
{
	if (onAttacked.GetisBallHit())
	{
		isBlowAway = true;
	}
}

void Energy::BlowAway(const Player& player, const OnAttackedEnemy& onAttacked)
{
    if (isBlowAway)
    {
        AngleVec = VNorm(AngleVec);
        AngleVec = VScale(AngleVec, moveSpeed);
        position = VAdd(position, AngleVec);
        if (position.y<=3) {
            position.y += 0.05f;
        }
    }
    else
    {
        AngleVec = VAdd(player.GetDirection(), VGet(0.0f, 0.0f, 0.0f));
    }
}

void Energy::UpdateEffect()
{
    if (isBallSporn)
    {
        // DXライブラリのカメラとEffekseerのカメラを同期する。
        Effekseer_Sync3DSetting();

        // 定期的にエフェクトを再生する
        // エフェクトを再生する。
        if (time % 60 == 0)
        {
            StopEffekseer3DEffect(playingEffectHandle);
            playingEffectHandle = PlayEffekseer3DEffect(EnergyBallHandle);
        }

        SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);
        // 時間を経過させる。
        time++;
    }
    else
    {
		StopEffekseer3DEffect(playingEffectHandle);
    }
}

void Energy::UpdateShadow()
{
    shadowToppos = VGet(position.x, -0.01, position.z);
    shadowBottompos = VGet(position.x, 0, position.z);
}

void Energy::DrawShadow()
{
    DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
}

void Energy::Draw()
{
    if (isBallSporn)
    {
        DrawShadow();
    }
}