#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include <cmath>
#include"Sound.h"
#include"Pallet.h"
#include"Enemy.h"
#include"Gimmick.h"

Gimmick::Gimmick(VECTOR Setposition)
    :position(Setposition)
    , Resetposition(Setposition)
    , shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
    , shadowToppos(VGet(0.0f, 0.0f, 0.0f))
    , GimmickHandle(0)
    , ShadowRad(0.75f)
    , dropTime(0)
    , time(1)
    , moveSpeed(0.4f)
    , isGimmickSporn(false)
    , endDropTime(10.0f)
    , isOrigin(false)
    , moveTime(0)
    , GimmickModelHandle(0)
    , modelPosition(VGet(0.0f, 0.0f, 0.0f))
    , returnEnemyPos(false)
    ,angle(0)
{
	GimmickModelHandle = MV1LoadModel("data/model/Gimmick/Gimmick.mv1");
    GimmickHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Smoke.efkefc", 1.2f);
    SetScalePlayingEffekseer3DEffect(GimmickHandle, EffektScale, EffektScale, EffektScale);
    // 3Dモデルのスケール決定
    MV1SetScale(GimmickModelHandle, VGet(ModelScale, ModelScale, ModelScale));
    // ３ＤモデルのY軸の回転値を９０度にセットする
    MV1SetRotationXYZ(GimmickModelHandle, VGet(29.8f + DX_PI_F, 0.0f, 0.0f));
}

Gimmick::~Gimmick()
{
}

void Gimmick::Load()
{
    //position = VGet(0.0f, 0.0f, 0.0f);
}

void Gimmick::Update(const Enemy& enemy)
{
    DropTimer(enemy);
    UpdateMove(enemy);
    // エフェクトの更新
    UpdateEffect(enemy);
    UpdateShadow();
    if (!isGimmickSporn)
    {
        // ３ＤモデルのY軸の回転値を９０度にセットする
        ReturnGimmickPos(enemy);
        UpdateAngle(enemy);
    }
    else
    {
        // ３ＤモデルのY軸の回転値を９０度にセットする
        MV1SetRotationXYZ(GimmickModelHandle, VGet(29.8f + DX_PI_F, 0.0f, 0.0f));
    }
}

void Gimmick::ReturnGimmickPos(const Enemy& enemy)
{
    position = VGet(enemy.GetPos().x,enemy.GetPos().y-5.5f,enemy.GetPos().z);
}

void Gimmick::UpdateAngle(const Enemy& enemy)
{
    // atan2 を使用して角度を取得
    angle = enemy.GetFloatAngle();
    MV1SetRotationXYZ(GimmickModelHandle, VGet(29.0f + DX_PI_F, angle + DX_PI_F, 0.0f));
}

void Gimmick::UpdateMove(const Enemy& enemy)
{
    UpdateMoveCircle(enemy);
    MoveOriginPosition(enemy);
    MoveResetPosition(enemy);
    modelPosition = VGet(position.x, position.y + 10.0f, position.z);
    MV1SetPosition(GimmickModelHandle, modelPosition);
}

void Gimmick::DropTimer(const Enemy& enemy)
{
    if (enemy.GetIsAttack()&&!isGimmickSporn&&enemy.GetHp()<5)
    {
        // 初回の呼び出し時に開始時刻を設定
        if (dropTime == 0)
        {
            dropTime = GetNowCount();  // ミリ秒単位で現在時刻を取得
        }
        // 経過時間が200ミリ秒(3秒)以上経過したらフラグを切り替える
        if (GetNowCount() - dropTime >= endDropTime)
        {
			isGimmickSporn = true;
        }
    }
}

void Gimmick::MoveOriginPosition(const Enemy& enemy)
{
    ////中心からプレイヤーの距離を測る

    float r = VSize(VSub(position, VGet(0, 0, 0)));

    ////一定の距離に達したらそれ以上いけないようにする
    if (enemy.GetHp() == 3  && isGimmickSporn && !isOrigin)
    {
		position = Resetposition;
    }

    if (enemy.GetHp() <= 2 && isGimmickSporn && !isOrigin)
    {
        if (r > returnRange || r < -returnRange)
        {

            //中心座標からプレイヤー座標の距離

            VECTOR distance = VSub(VGet(0, 0, 0), position);

            //正規化

            distance = VNorm(distance);

            //戻す量を計算、加算する

            VECTOR returnPosition = VScale(distance, 0.1f);

            position = VAdd(position, returnPosition);

        }
        if (position.x >= 0 && position.x <= 0.05)
        {
            isOrigin = true;
        }
    }
}

void Gimmick::MoveResetPosition(const Enemy& enemy)
{
    if (isOrigin && isGimmickSporn)
    {

        //中心座標からプレイヤー座標の距離

        VECTOR distance = VSub(Resetposition, position);

        //正規化

        distance = VNorm(distance);

        //戻す量を計算、加算する

        VECTOR returnPosition = VScale(distance, 0.1f);

        position = VAdd(position, returnPosition);
        if (position.x == Resetposition.x && position.z == Resetposition.z)
        {
            isOrigin = false;
        }
    }

}

void Gimmick::UpdateMoveCircle(const Enemy& enemy)
{
    if (enemy.GetHp() == 4 && isGimmickSporn && !isOrigin)
    {
        // 時間を使って角度を計算
        float moveAngle = moveTime * AngleSpeed;

        // 新しい位置を計算
        position.x = Radius * cos(moveAngle);
        position.z = Radius * sin(moveAngle);
        position.y = 0.0f; // y座標は固定

        // 時間を進める
        moveTime++;
    }
}

void Gimmick::UpdateEffect(const Enemy& enemy)
{
    if (isGimmickSporn&& enemy.GetHp() < 5)
    {
        // DXライブラリのカメラとEffekseerのカメラを同期する。
        Effekseer_Sync3DSetting();

        // 定期的にエフェクトを再生する
        // エフェクトを再生する。
        if (time % 60 == 0)
        {
            StopEffekseer3DEffect(playingEffectHandle);
            playingEffectHandle = PlayEffekseer3DEffect(GimmickHandle);
			isGimmickSporn = false;
        }

        SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y+0.0f, position.z);
        // 時間を経過させる。
        time++;
    }
    else
    {
        StopEffekseer3DEffect(playingEffectHandle);
    }
}

void Gimmick::UpdateShadow()
{
    shadowToppos = VGet(position.x, -0.01f, position.z);
    shadowBottompos = VGet(position.x, 0.0f, position.z);
}

void Gimmick::Draw()
{
    if (isGimmickSporn)
    {
        DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
    }
    if (!returnEnemyPos)
    {
		MV1DrawModel(GimmickModelHandle);
    }
}