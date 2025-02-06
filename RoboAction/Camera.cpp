#include"DxLib.h"
#include"Camera.h"
#include"Input.h"
#include"Enemy.h"
#include"Player.h"
#include"HitChecker.h"
#include"EnemyAttackRangeChecker.h"
/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
    :OriginalOffset(VGet(0, 0, 0))
    ,position  (VGet(0, 0, 0))
    , AngleVec(VGet(0, 0, 0))
    ,isShake(false)
    ,isDamage(true)
    ,shakeTime(0)
{
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.10f, 500.0f);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
    // 処理なし.
}

void Camera::Load()
{
    position = VGet(0, Hight, Zoom);
    isShake=false;
    isDamage=true;
    shakeTime = 0;
}

void Camera::Update(const Player& player,const Input& input, const Enemy& enemy, const EnemyAttackRangeChecker& attackRange)
{

    //// 「←」ボタンが押されていたら水平角度をマイナスする
    //if (rightInput->IsInputAnalogKey(Input::AnalogLeft))
    //{
    //    angleHorizontal += AngleSpeed;

    //    // －１８０度以下になったら角度値が大きくなりすぎないように３６０度を足す
    //    if (angleHorizontal > DX_PI_F)
    //    {
    //        angleHorizontal -= DX_TWO_PI_F;
    //    }
    //}

    //// 「→」ボタンが押されていたら水平角度をプラスする
    //if (rightInput->IsInputAnalogKey(Input::AnalogRight))
    //{
    //    angleHorizontal -= AngleSpeed;

    //    // １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
    //    if (angleHorizontal < -DX_PI_F)
    //    {
    //        angleHorizontal += DX_TWO_PI_F;
    //    }
    //}

    //// 「↑」ボタンが押されていたら垂直角度をマイナスする
    //if (rightInput->IsInputAnalogKey(Input::AnalogUp))
    //{
    //    angleVertical += AngleSpeed;

    //    //// ある一定角度以下にはならないようにする
    //    if (angleVertical > DX_PI_F * 0.5f - 0.6f)
    //    {
    //        angleVertical = DX_PI_F * 0.5f - 0.6f;
    //    }
    //}

    //// 「↓」ボタンが押されていたら垂直角度をプラスする
    //if (rightInput->IsInputAnalogKey(Input::AnalogDown))
    //{
    //    angleVertical -= AngleSpeed;

    //    //// ある一定角度以上にはならないようにする
    //    if (angleVertical < -DX_PI_F * 0.5f + 0.6f)
    //    {
    //        angleVertical = -DX_PI_F * 0.5f + 0.6f;
    //    }
    //}

    if (!attackRange.GetisShortWithin())
    {

        if (enemy.GetIsExplosion()/*||player.GetisOnAttack()*/)
        {
            isShake = true;
        }
        // z軸上で、プレイヤーから一定距離離れた状態でプレイヤーを常に見続けるよう位置調整
        // カメラに位置を反映.
        if (isShake)
        {
            ShakeCamera(shakeIntensity, shakeDuration, player);
        }
        else
        {
            AngleVec = VSub(player.GetPos(), enemy.GetPos());
            AngleVec = VNorm(AngleVec);
            AngleVec = VScale(AngleVec, Distance);
            position = VAdd(player.GetPos(), AngleVec);
            position.y = Hight;
        }

        targetposition = VAdd(enemy.GetPos(), VGet(-0.0f, TargetHight, 0.0f));

        //FixCameraPosition();

        // カメラに位置を反映.
        SetCameraPositionAndTarget_UpVecY(position, targetposition);
    }

}

void Camera::ReadyUpdate(const Player& player)
{
    position = VGet(-1.0f, 0.5f, -3.0f);
    targetposition = VAdd(player.GetPos(), VGet(-1.0f, 0.3f, 0.0f));
    //FixCameraPosition();
    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(position, targetposition);
}
void Camera::GameTitle(const Player& player) 
{
    position = VGet(-1.0f, 0.5f, -3.0f);
    targetposition = VAdd(player.GetPos(), VGet(-1.0f, 0.3f, 0.0f));
    //FixCameraPosition();
    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(position, targetposition);
}

void Camera::GameEnd(const Enemy& enemy)
{
	position = VGet(-1.0f, 2.3f, -3.6f);
	targetposition = VAdd(enemy.GetPos(), VGet(-0.30f, 3.3f, 0.0f));

	//FixCameraPosition();
	// カメラに位置を反映.
	SetCameraPositionAndTarget_UpVecY(position, targetposition);
}

void Camera::GameClear(const Enemy& enemy)
{
	position = VGet(-1.0f, 4.3f, -3.0f);
	targetposition = VAdd(enemy.GetPos(), VGet(-0.30f, 3.3f, 0.0f));
	//FixCameraPosition();
	// カメラに位置を反映.
	SetCameraPositionAndTarget_UpVecY(position, targetposition);
}

void Camera::FixCameraPosition()
{
    // 水平方向の回転はＹ軸回転
    auto rotY = MGetRotY(angleHorizontal);

    // 垂直方向の回転はＺ軸回転 )
    auto rotZ = MGetRotZ(angleVertical);

    // カメラからプレイヤーまでの初期距離をセット
    float cameraPlayerLength = Zoom;

    // カメラの座標を算出
    // Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
    // 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
    // 注視点の座標を足したものがカメラの座標
    position = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), targetposition);

    //if (position.y<=0)
    //{
    //    position.y = 0.50f;
    //}

}

void Camera::ShakeCamera(float intensity, float duration,const Player& player)
{
    if (shakeTime < duration)
    {

        // ランダムな揺れを生成
        Offset.x = (rand() % 5 - 1) * intensity / 100.0f;
        Offset.y = (rand() % 5 - 1) * intensity / 100.0f;
        Offset.z = (rand() % 5 - 1) * intensity / 100.0f;

        // カメラ位置を更新
        position=VGet(position.x + Offset.x, position.y + Offset.y, position.z + Offset.z);

        // 時間を進める
        shakeTime += 0.20f;

    }
    else
    {
        // 揺れが終了したら元の位置に戻す
        position = VAdd(player.GetPos(), VGet(-0.0f, Hight, Zoom));
        shakeTime = 0.0f;
        isDamage = false;
        isShake = false;
    }
}