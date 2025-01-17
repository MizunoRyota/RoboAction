#include"DxLib.h"
#include"Camera.h"
#include"Input.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
    : angleH(0)
    , angleV(0)
    ,shakeTime(0)
    ,isDamage(true)
    ,position  (VGet(0, 0, 0))
    ,OriginalOffset(VGet(0, 0, 0))
{
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.10f, 1200.0f);
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
}

void Camera::Update(const Player& player,const Input& input)
{
    if (CheckHitKey(KEY_INPUT_LSHIFT) || (input.GetNowFrameInput() & PAD_INPUT_C))
    {
        // 「←」ボタンが押されていたら水平角度をマイナスする
        if (input.GetNowFrameInput() & PAD_INPUT_LEFT)
        {
            angleH -= camaeraSpeed;

            // －１８０度以下になったら角度値が大きくなりすぎないように３６０度を足す
            if (angleH < -DX_PI_F)
            {
                angleH += DX_TWO_PI_F;
            }
        }

        // 「→」ボタンが押されていたら水平角度をプラスする
        if (input.GetNowFrameInput() & PAD_INPUT_RIGHT)
        {
            angleH += camaeraSpeed;

            // １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
            if (angleH > DX_PI_F)
            {
                angleH -= DX_TWO_PI_F;
            }
        }

        // 「↑」ボタンが押されていたら垂直角度をマイナスする
        if (input.GetNowFrameInput() & PAD_INPUT_UP)
        {
            angleV -= camaeraSpeed;

            // ある一定角度以下にはならないようにする
            if (angleV < -DX_PI_F * 0.5f + 0.6f)
            {
                angleV = -DX_PI_F * 0.5f + 0.6f;
            }
        }

        // 「↓」ボタンが押されていたら垂直角度をプラスする
        if (input.GetNowFrameInput() & PAD_INPUT_DOWN)
        {
            angleV += camaeraSpeed;

            // ある一定角度以上にはならないようにする
            if (angleV > DX_PI_F * 0.5f - 0.6f)
            {
                angleV = DX_PI_F * 0.5f - 0.6f;
            }
        }
    }
    // z軸上で、プレイヤーから一定距離離れた状態でプレイヤーを常に見続けるよう位置調整
    // カメラに位置を反映.
    if (player.GetIsBeAttack())
    {
        ShakeCamera(shakeIntensity, shakeDuration,player);
    }
    else
    {
        position = VAdd(player.GetPos(), VGet(-0.0f, Hight, Zoom));
    }

    targetposition = VAdd(player.GetPos(), VGet(-0.0f, TargetHight, 0.0f));

    FixCameraPosition();

    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(position, targetposition);

}

void Camera::FixCameraPosition()
{
    // 水平方向の回転はＹ軸回転
    auto rotY = MGetRotY(angleH);

    // 垂直方向の回転はＺ軸回転 )
    auto rotZ = MGetRotZ(angleV);

    // カメラからプレイヤーまでの初期距離をセット
    float cameraPlayerLength = Zoom;

    // カメラの座標を算出
    // Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
    // 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
    // 注視点の座標を足したものがカメラの座標
    position = VAdd(VTransform(VTransform(VGet(-cameraPlayerLength, 0.0f, 0.0f), rotZ), rotY), targetposition);

    if (position.y<=0)
    {
        position.y = 0.50f;
    }

}

void Camera::ShakeCamera(float intensity, float duration,const Player& player)
{

    if (shakeTime < duration)
    {
        // ランダムな揺れを生成
        Offset.x = (rand() % 3 - 1) * intensity / 100.0f;
        Offset.y = (rand() % 3 - 1) * intensity / 100.0f;
        Offset.z = (rand() % 3 - 1) * intensity / 100.0f;

        // カメラ位置を更新
        position=VGet(position.x + Offset.x, position.y + Offset.y, position.z + Offset.z);

        // 時間を進める
        shakeTime += 0.50f;
    }
    else
    {
        // 揺れが終了したら元の位置に戻す
        position = VAdd(player.GetPos(), VGet(-0.0f, Hight, Zoom));
        shakeTime = 0.0f;
        isDamage = false;
    }
}