#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Enemy.h"
#include"EnergyBall.h"

Energy::Energy()
	:position(VGet(0.0f, 0.0f, 0.0f))
    , isBallSporn(false)
    , ShadowRad(1.0f)
    , time(0)
    , shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
    , shadowToppos(VGet(0.0f, 0.0f, 0.0f))
{

}

Energy::~Energy()
{
}


void Energy::Load()
{
	// エフェクトリソースを読み込む。
	EnergyBallHandle = LoadEffekseerEffect("data/effekseer/EfkFile/EnergyBall.efkefc", 0.8f);
    ExplosionHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Explosion.efkefc", 1.5f);
	SetScalePlayingEffekseer3DEffect(EnergyBallHandle, EffektScale, EffektScale, EffektScale);
	SetScalePlayingEffekseer3DEffect(ExplosionHandle, EffektScale, EffektScale, EffektScale);
}


void Energy::BallSporn(const Enemy& enemy)
{
    if (enemy.GetChaseCount() == 4)
    {
        // エネルギーボールの座標を更新する
        if (!isBallSporn)
        {
            position = VAdd(enemy.GetPos(), VGet(0.0f, 0.6f, 0.0f));
            isBallSporn = true;
        }
    }
}

void Energy::Update(const Enemy& enemy)
{
    BallSporn(enemy);
    UpdateEffect();
    UpdateShadow();
}

void Energy::UpdateEffect()
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

void Energy::UpdateShadow()
{
    shadowToppos = VGet(position.x, -0.8, position.z);
    shadowBottompos = VGet(position.x, -0.6, position.z);
}
void Energy::DrawShadow()
{
    DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);

}
void Energy::Draw()
{
    //DrawShadow();
}