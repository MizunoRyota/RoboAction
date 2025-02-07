#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"math.h"
#include"Sound.h"
#include"Camera.h"
#include"Pallet.h"
#include"Player.h"
#include"Input.h"
#include"OnAttackedPlayerHit.h"
Player::Player()
    :position(VGet(0.0f, 0.0f, 0.0f))
    , shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
    , shadowToppos(VGet(0.0f, 0.0f, 0.0f))
    , targetMoveDirection(VGet(0, 0, 0))
    , currentState(State::Stand)
    , returnRange(15.0f)
    , PlayerHandle(-1)
    , angle(0.0f)
    , isAttack(false)
    , isInvincible(0)
    , isOnAttack(false)
    , isFirstAttack(false)
    , isSecondAttack(false)
    , isThirdAttack(false)
	, isDecreaseHp(false)
    ,isMoveStick(false)
    , ShadowRad(0.3f)
    , playTime(0)
    , prevPlayAnim(-1)
	, HpGaugeWidth(450)
    , prevPlayTime(0)
    , PlayAnim(-1)
    , time(0)
    , alpha(0)
    , invincible(0)
    , animBlendRate(1.0f)
    , AttackHandle(0)
    , SecondAttackHandle(0)
    , ThirdAttackHandle(0)
	, HpGauge(0)
	, EnptyHpGuage(0)
	, AttachIndex(0)
	, AnimTime(0)
	, hp(3)
    , OnPlayerHandle(0)
    , SlashHandle(0)
{
    // 処理なし
}

Player::~Player()
{
    // 処理なし
}

void Player::Load()
{
    // モデルの読み込み
    PlayerHandle = MV1LoadModel("data/model/Player/Player.mv1");
    //
    HpGauge = LoadGraph("data/Ui/Texture/PlayerHp1.png");
    EnptyHpGuage = LoadGraph("data/Ui/Texture/EnptyPlayerHp2.png");

    OnPlayerHandle = LoadSoundMem("data/sound/Onplayer.mp3");
    SlashHandle = LoadSoundMem("data/sound/Slash.mp3");

    // エフェクトリソースを読み込む。
    AttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Attack1.efkefc", 1.0f);
    SecondAttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/PlayerSecondAttack.efkefc", 0.750f);
    ThirdAttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/PlayerThirdAttack.efkefc", 0.750f);

    SetScalePlayingEffekseer3DEffect(AttackHandle, EffektScale, EffektScale, EffektScale);
    SetScalePlayingEffekseer3DEffect(SecondAttackHandle, EffektScale, EffektScale, EffektScale);
    SetScalePlayingEffekseer3DEffect(ThirdAttackHandle, EffektScale, EffektScale, EffektScale);

    //値の初期化
    position = VGet(0.0f, 0.0f, 0.0f);
	shadowBottompos = VGet(0.0f, 0.0f, 0.0f);
	shadowToppos = VGet(0.0f, 0.0f, 0.0f);
	targetMoveDirection = VGet(0, 0, 0);
	currentState = State::Stand;
	returnRange = 15.0f;
	angle = 0.0f;
	isAttack = false;
	isInvincible = 0;
	isOnAttack = false;
	isFirstAttack = false;
	isSecondAttack = false;
	isThirdAttack = false;
	isDecreaseHp = false;
    isMoveStick = false;
	playTime = 0;
	prevPlayAnim = -1;
	time = 0;
	alpha = 0;
	invincible = 0;
    // アニメーションのブレンド率を初期化
    animBlendRate = 1.0f;
	PlayAnim = -1;
	HpGaugeWidth = 450;
	hp = 3;


    // 3Dモデルのスケール決定
    MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
    //モーションの変更
    ChangeMotion(AnimKind::Idol);

    // 再生時間の初期化
    playTime = 0.0f;

    // ３ＤモデルのY軸の回転値を９０度にセットする
    MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 0.0f, 0.0f));
}

void Player::Initialize()
{
    // モデルの読み込み
    PlayerHandle = MV1LoadModel("data/model/Player/Player.mv1");
    //
    HpGauge = LoadGraph("data/Ui/Texture/PlayerHp1.png");
    EnptyHpGuage = LoadGraph("data/Ui/Texture/EnptyPlayerHp1.png");
    // エフェクトリソースを読み込む。
    AttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Attack1.efkefc", 1.0f);
    SecondAttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/PlayerSecondAttack.efkefc", 0.750f);
    ThirdAttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/PlayerThirdAttack.efkefc", 0.750f);

    //SetScalePlayingEffekseer3DEffect(AttackHandle, EffektScale, EffektScale, EffektScale);
    //SetScalePlayingEffekseer3DEffect(SecondAttackHandle, EffektScale, EffektScale, EffektScale);
    //SetScalePlayingEffekseer3DEffect(ThirdAttackHandle, EffektScale, EffektScale, EffektScale);

    //値の初期化
    position = VGet(0.0f, 0.0f, 0.0f);

    // アニメーションのブレンド率を初期化
    animBlendRate = 1.0f;

    // 3Dモデルのスケール決定
    MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));

    //currentState = State::Stand;

    ////モーションの変更
    //hangeMotion(AnimKind::Idol);

    // 再生時間の初期化
    playTime = 0.0f;

    // ３ＤモデルのY軸の回転値を９０度にセットする
    MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 0.0f, 0.0f));
    // 3Dモデルのスケール決定
    MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
    //値の初期化
    position = VGet(0.0f, 0.0f, 0.0f);
    shadowBottompos = VGet(0.0f, 0.0f, 0.0f);
    shadowToppos = VGet(0.0f, 0.0f, 0.0f);
    isOnAttack = false;
    isAttack = false;
    isDecreaseHp = false;
    isInvincible = 0;
    returnRange = 15.0f;
    angle = 0.0f;
    isFirstAttack = false;
    isSecondAttack = false;
    isThirdAttack = false;
    hp = 3;
    HpGaugeWidth = 450;
    time = 0;
    alpha = 0;
    invincible = 0;
    prevPlayAnim = -1;
    playTime = 0;
    PlayAnim = -1;
    animBlendRate = 1.0f;
    HpGaugeWidth = 450;
}

void Player::PlayOnplayer()
{
    PlaySoundMem(OnPlayerHandle, DX_PLAYTYPE_BACK, true);           //kettei
}

void Player::PlaySlash()
{
    if (!isAttack && !isMoveStick)
    {
        PlaySoundMem(SlashHandle, DX_PLAYTYPE_BACK, true);           //kettei
    }
}

bool Player::BeAttacked(const OnAttackedPlayer& onattacked)
{
    if (onattacked.GetisOnAttack() && !isDecreaseHp)
    {
		PlayOnplayer();
        isOnAttack = true;
        isDecreaseHp = true;
        hp--;
    }
    else
    {
        isOnAttack = false;
    }
    return 0;
}

void Player::DecreaseHp()
{
    if (hp==2&&HpGaugeWidth>=325)
    {
		HpGaugeWidth -= 2;
	}
    else if (hp == 1 && HpGaugeWidth >= 225)
    {
        HpGaugeWidth -= 2;
    }
	else if (hp == 0 && HpGaugeWidth >= 100)
	{
		HpGaugeWidth -= 2;
	}
}

void Player::InvincibleTimer()
{
    if (isOnAttack|| isInvincible != 0)
    {
        // 初回の呼び出し時に開始時刻を設定
        if (isInvincible == 0)
        {
            isInvincible = GetNowCount();  // ミリ秒単位で現在時刻を取得
        }

        // 経過時間が3000ミリ秒(3秒)以上経過したらフラグを切り替える
        if (GetNowCount() - isInvincible >= 2000)
        {
            isInvincible = 0;
            isDecreaseHp = false;
        }
        else
        {
            // 初回の呼び出し時に開始時刻を設定
            if (invincible == 0)
            {
                invincible = GetNowCount();  // ミリ秒単位で現在時刻を取得
            }

            // 経過時間が3000ミリ秒(3秒)以上経過したらフラグを切り替える
            if (GetNowCount() - invincible >= 300)
            {
                invincible = 0;
            }
            else
            {
                if (alpha == 0.0f)
                {
                    alpha = 1.0f;
                }
                else
                {
                    alpha = 0.0f;
                }
            }
        }
    }
    else
    {
        alpha = 1.0f;
    }
}

void Player::UpdateEffect()
{
    if (isAttack)
    {
        // DXライブラリのカメラとEffekseerのカメラを同期する。
        Effekseer_Sync3DSetting();

 
            StopEffekseer3DEffect(playingEffectHandle);
            // 定期的にエフェクトを再生する
                // エフェクトを再生する。
            if (isFirstAttack && !isSecondAttack && !isThirdAttack)
            {
                playingEffectHandle = PlayEffekseer3DEffect(AttackHandle);
            }
            else if (isFirstAttack && isSecondAttack && !isThirdAttack)
            {
                playingEffectHandle = PlayEffekseer3DEffect(SecondAttackHandle);
            }
            else if (isFirstAttack && isSecondAttack && isThirdAttack)
            {
                playingEffectHandle = PlayEffekseer3DEffect(ThirdAttackHandle);
            }
        

        // Effekseerにより再生中のエフェクトを更新する。
        UpdateEffekseer3D();

        SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y + 0.2f, position.z);
        SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0.0f, angle + DX_PI_F, 0.0);
        // 時間を経過させる。
        time++;
    }
}

/// <summary>
/// 更新
/// </summary>
void Player::Update(const Input& input, const OnAttackedPlayer& onattacked, const Camera& camera,const Sound& sound)
{

    // パッド入力によって移動パラメータを設定する
    VECTOR moveVec;			// このフレームの移動ベクトル
    VECTOR	upMoveVec;		// 方向ボタン「↑」を入力をしたときのプレイヤーの移動方向ベクトル
    VECTOR	leftMoveVec;	// 方向ボタン「←」を入力をしたときのプレイヤーの移動方向ベクトル
    State prevState = currentState;
    // ゲーム状態変化

    BeAttacked(onattacked);
    DecreaseHp();
    currentState = UpdateMoveParameterWithPad(input, moveVec, camera, leftMoveVec, upMoveVec);

    //// ぼたんおしたら
    //clsDx();
    //printfDx("xpos%f\n", position.x);
    //printfDx("ypos%f\n", position.y);
    //printfDx("zpos%f\n", position.z);
    //printfDx("currentState%d\n", currentState);
    //printfDx("prevState%d\n", prevState);
    //printfDx("isAttack%d\n", isAttack);
    //printfDx("isOnAttack%d\n", isOnAttack);
    //printfDx("hp%d\n", hp);

    // アニメーションステートの更新
    if (input.GetNowFrameInput() & PAD_INPUT_C || CheckHitKey(KEY_INPUT_SPACE))
    {
		PlaySlash();
        UpdateAttack();
        UpdateAttackState(prevState);
        UpdateEffect();
    }
    else
    {
        UpdateAnimationState(prevState);
    }
    if (CheckHitKey(KEY_INPUT_Y))
    {
		hp = 0;
    }
    LimitRange();

    //プレイヤーが向く角度の更新
    UpdateAngle();

    //ポジションの更新
    Move(moveVec);

    //影の更新
    UpdateShadow();

    //アニメーション処理
    UpdateAnimation(prevState);
    InvincibleTimer();
    MV1SetOpacityRate(PlayerHandle, alpha);
}

void Player::UpdateTutorial(const Input& input, const OnAttackedPlayer& onattacked, const Camera& camera)
{
        // パッド入力によって移動パラメータを設定する
    VECTOR moveVec;			// このフレームの移動ベクトル
    VECTOR	upMoveVec;		// 方向ボタン「↑」を入力をしたときのプレイヤーの移動方向ベクトル
    VECTOR	leftMoveVec;	// 方向ボタン「←」を入力をしたときのプレイヤーの移動方向ベクトル
    State prevState = currentState;
    // ゲーム状態変化
        //// ぼたんおしたら
    clsDx();
    printfDx("xpos%f\n", position.x);
    printfDx("ypos%f\n", position.y);
    printfDx("zpos%f\n", position.z);
    printfDx("currentState%d\n", currentState);
    printfDx("prevState%d\n", prevState);
    printfDx("isAttack%d\n", isAttack);
    printfDx("isOnAttack%d\n", isOnAttack);
    printfDx("isDecreaseHp%d\n", isDecreaseHp);

    currentState = UpdateMoveParameterWithPad(input, moveVec, camera, leftMoveVec, upMoveVec);

    // アニメーションステートの更新
    if (input.GetNowFrameInput() & PAD_INPUT_C || CheckHitKey(KEY_INPUT_SPACE))
    {
        UpdateAttack();
        UpdateAttackState(prevState);
        UpdateEffect();
    }
    else
    {
        UpdateAnimationState(prevState);
    }

    LimitRange();

    //プレイヤーが向く角度の更新
    UpdateAngle();

    //影の更新
    UpdateShadow();

    //アニメーション処理
    UpdateAnimation(prevState);
    InvincibleTimer();
    MV1SetOpacityRate(PlayerHandle, alpha);
    // プレイヤーのモデルの座標を更新する
    MV1SetPosition(PlayerHandle, position);
}

void Player::UpdateTitle() 
{
    State prevState = currentState;

    UpdateAnimation(prevState);
}

void Player::LimitRange()
{
    ////中心からプレイヤーの距離を測る

    float r = VSize(VSub(position, VGet(0, 0, 0)));

    ////一定の距離に達したらそれ以上いけないようにする

    if (r > returnRange || r < -returnRange)
    {
        printfDx("returnRange%f\n", r);

        //中心座標からプレイヤー座標の距離

        VECTOR distance = VSub(VGet(0, 0, 0), position);

        //正規化

        distance = VNorm(distance);

        //戻す量を計算、加算する

        VECTOR returnPosition = VScale(distance, (r - returnRange));

        position = VAdd(position, returnPosition);
    }

}

void Player::UpdateAttack()
{
    // エフェクトを再生する。
    if (!isFirstAttack && !isSecondAttack && !isThirdAttack)
    {
        currentState = State::FirstAttack;
    }
    else if (isFirstAttack && !isSecondAttack && !isThirdAttack)
    {
        currentState = State::SecondAttack;
    }
    else if (isFirstAttack && isSecondAttack && !isThirdAttack)
    {
        currentState = State::LastAttack;
    }
}

/// <summary>
/// アニメーションの変更
/// </summary>
/// <param name="motionNum"></param>
void Player::ChangeMotion(AnimKind motionNum)
{
    // 入れ替えを行うので、１つ前のモーションがが有効だったらデタッチする
    if (prevPlayAnim != -1)
    {
        //アニメーションのデタッチ
        MV1DetachAnim(PlayerHandle, prevPlayAnim);
        prevPlayAnim = -1;
    }
    // 今まで再生中のモーションだったものの情報をPrevに移動する
    prevPlayAnim = PlayAnim;
    prevPlayTime = playTime;

    //新しいアタッチ番号を保存
    PlayAnim = MV1AttachAnim(PlayerHandle, static_cast<int>(motionNum));

    // 再生時間の初期化
    playTime = 0;

    // ブレンド率はPrevが有効ではない場合は１．０ｆ( 現在モーションが１００％の状態 )にする
    animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;

}

/// <summary>
/// アニメーションの更新処理
/// </summary>
void Player::UpdateAnimation(State prevState)
{
    // 再生しているアニメーションの総時間
    float animTotalTime;

    // ブレンド率が１以下の場合は１に近づける
    if (animBlendRate < 1.0f)
    {
        animBlendRate += AnimBlendSpeed;
        if (animBlendRate > 1.0f)
        {
            animBlendRate = 1.0f;
        }
    }

    //再生しているアニメーションの処理１
    if (PlayAnim != -1)
    {
        // アニメーションの総時間を取得
        animTotalTime = MV1GetAttachAnimTotalTime(PlayerHandle, PlayAnim);

        //アニメーションを進める
        if (isAttack)
        {
            playTime += AttackSpeed;
        }
        else
        {
            playTime += playAnimSpeed;
        }
        // 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
        if (playTime >= animTotalTime)
        {
            ResetMotion(prevState);
            if (isFirstAttack && isSecondAttack && isThirdAttack)
            {
                isFirstAttack = false;
                isSecondAttack = false;
                isThirdAttack = false;
            }
            isAttack = false;
            playTime = static_cast<float>(fmod(playTime, animTotalTime));
        }

        // 変更した再生時間をモデルに反映させる
        MV1SetAttachAnimTime(PlayerHandle, PlayAnim, playTime);
        // アニメーション１のモデルに対する反映率をセット
        MV1SetAttachAnimBlendRate(PlayerHandle, PlayAnim, animBlendRate);
    }
    // 再生しているアニメーション２の処理
    if (prevPlayAnim != -1)
    {
        // アニメーションの総時間を取得
        animTotalTime = MV1GetAttachAnimTotalTime(PlayerHandle, prevPlayAnim);

        // 再生時間を進める
        prevPlayTime += playAnimSpeed;

        // 再生時間が総時間に到達していたら再生時間をループさせる
        if (prevPlayTime > animTotalTime)
        {
            prevPlayTime = static_cast<float>(fmod(prevPlayTime, animTotalTime));
        }

        // 変更した再生時間をモデルに反映させる
        MV1SetAttachAnimTime(PlayerHandle, prevPlayAnim, prevPlayTime);

        // アニメーション２のモデルに対する反映率をセット
        MV1SetAttachAnimBlendRate(PlayerHandle, prevPlayAnim, 1.0f - animBlendRate);
    }
}

void Player::ResetMotion(State prevState)
{
    if (prevState == State::FirstAttack && currentState == State::FirstAttack || prevState == State::SecondAttack && currentState == State::SecondAttack || prevState == State::LastAttack && currentState == State::LastAttack && isAttack || prevState == State::TakeDamage && currentState == State::TakeDamage)
    {
        // 立ち止りアニメーションを再生する
        ChangeMotion(AnimKind::Idol);
        currentState = State::Stand;
    }
}

/// <summary>
/// 影の更新処理
/// </summary>
void Player::UpdateShadow()
{
    shadowToppos = VGet(position.x, -0.002, position.z);
    shadowBottompos = VGet(position.x, position.y, position.z);
}

Player::State Player::UpdateMoveParameterWithPad(const Input& input, VECTOR& moveVec, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec)
{

    State nextState = currentState;

    // プレイヤーの移動方向のベクトルを算出
// 方向ボタン「↑」を押したときのプレイヤーの移動ベクトルはカメラの視線方向からＹ成分を抜いたもの
    upMoveVec = VSub(camera.GetTarget(), camera.GetPosition());
    upMoveVec.y = 0.0f;

    // 方向ボタン「←」を押したときのプレイヤーの移動ベクトルは上を押したときの方向ベクトルとＹ軸のプラス方向のベクトルに垂直な方向
    leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));

    // 二つのベクトルを正規化( ベクトルの長さを１．０にすること )
    upMoveVec = VNorm(upMoveVec);
    leftMoveVec = VNorm(leftMoveVec);

    // このフレームでの移動ベクトルを初期化
      moveVec = VGet(0.0f, 0.0f, 0.0f);

    // 移動したかどうかのフラグを初期状態では「移動していない」を表すFALSEにする
    isMoveStick = false;

    if (!isAttack && currentState != State::TakeDamage && (input.GetNowFrameInput() & PAD_INPUT_D) == 0)
    {
        // 方向ボタン「←」が入力されたらカメラの見ている方向から見て左方向に移動する
        if (input.GetNowFrameInput() & PAD_INPUT_LEFT)
        {
            // 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
            moveVec = VAdd(moveVec, leftMoveVec);

            // 移動したかどうかのフラグを「移動した」にする
            isMoveStick = true;

            //
            isAttack = false;
            isFirstAttack = false;
            isSecondAttack = false;
        }
        else if (input.GetNowFrameInput() & PAD_INPUT_RIGHT)
        {
            // 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
            moveVec = VAdd(moveVec,VScale(leftMoveVec,-1.0f));

            // 移動したかどうかのフラグを「移動した」にする
            isMoveStick = true;

            //
            isAttack = false;
            isFirstAttack = false;
            isSecondAttack = false;
        }
        if (input.GetNowFrameInput() & PAD_INPUT_UP)
        {
            // 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
            moveVec = VAdd(moveVec, upMoveVec);

            // 移動したかどうかのフラグを「移動した」にする
            isMoveStick = true;

            isAttack = false;
            isFirstAttack = false;
            isSecondAttack = false;
        }
        else if (input.GetNowFrameInput() & PAD_INPUT_DOWN)
        {
            // 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
            moveVec = VAdd(moveVec, VScale(upMoveVec,-1.0f));

            // 移動したかどうかのフラグを「移動した」にする
            isMoveStick = true;

            isAttack = false;
            isFirstAttack = false;
            isSecondAttack = false;
        }
    }
    // 移動ボタンが押されたかどうかで処理を分岐
    if (isMoveStick)
    {

        // もし今まで「立ち止まり」状態だったら
        if (currentState == State::Stand)
        {
            // 状態を「走り」にする
            nextState = State::Run;
        }

        // 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
        targetMoveDirection = VNorm(moveVec);

        // プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
        moveVec = VScale(targetMoveDirection, MoveSpeed);

    }
    else
    {
        // このフレームで移動していなくて、且つ状態が「走り」だったら
        if (currentState == State::Run)
        {
            // 状態を「立ち止り」にする
            nextState = State::Stand;
        }
    }
    if (isOnAttack)
    {
        nextState = State::TakeDamage;
    }

    return nextState;

}

/// <summary>
/// 角度の更新処理
/// </summary>
void Player::UpdateAngle()
{
    // プレイヤーの移動方向にモデルの方向を近づける
    float targetAngle;			// 目標角度
    float difference;			// 目標角度と現在の角度との差

    // 目標の方向ベクトルから角度値を算出する
    targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

    // 目標の角度と現在の角度との差を割り出す
    // 最初は単純に引き算
    difference = targetAngle - angle;

    // ある方向からある方向の差が１８０度以上になることは無いので
    // 差の値が１８０度以上になっていたら修正する
    if (difference < -DX_PI_F)
    {
        difference += DX_TWO_PI_F;
    }
    else if (difference > DX_PI_F)
    {
        difference -= DX_TWO_PI_F;
    }

    // 角度の差が０に近づける
    if (difference > 0.0f)
    {
        // 差がプラスの場合は引く
        difference -= AngleSpeed;
        if (difference < 0.0f)
        {
            difference = 0.0f;
        }
    }
    else
    {
        // 差がマイナスの場合は足す
        difference += AngleSpeed;
        if (difference > 0.0f)
        {
            difference = 0.0f;
        }
    }

    // モデルの角度を更新
    angle = targetAngle - difference;
    MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// アニメーションの更新処理
/// </summary>
void Player::UpdateAnimationState(State prevState)
{
    // 立ち止まりから走りに変わったら
    if (prevState == State::Stand && currentState == State::Run)
    {
        // 走りアニメーションを再生する
        ChangeMotion(AnimKind::Run);
    }
    // 走りから立ち止まりに変わったら
    if (prevState == State::Run && currentState == State::Stand)
    {
        // 立ち止りアニメーションを再生する
        ChangeMotion(AnimKind::Idol);
    }
    if (isOnAttack && currentState == State::TakeDamage)
    {
        // ダメージモーションを再生する
        ChangeMotion(AnimKind::TakeDamage);
    }
}

void Player::UpdateAttackState(State prevState)
{
    // 立ち止まりから走りに変わったら
    if (prevState == State::Stand && currentState == State::FirstAttack && !isFirstAttack && !isAttack)
    {
        // 走りアニメーションを再生する
        ChangeMotion(AnimKind::FirstAttack);
        isFirstAttack = true;
        isAttack = true;
    }
    else if (prevState == State::Stand && currentState == State::SecondAttack && !isSecondAttack && isFirstAttack && !isAttack)
    {
        // 走りアニメーションを再生する
        ChangeMotion(AnimKind::SecondAttack);
        isSecondAttack = true;
        isAttack = true;
    }
    else if (prevState == State::Stand && currentState == State::LastAttack && isFirstAttack && isSecondAttack && !isAttack)
    {
        // 走りアニメーションを再生する
        ChangeMotion(AnimKind::LastAttack);
        isThirdAttack = true;
        isAttack = true;
    }
}

void Player::Move(VECTOR& moveVec)
{
    position = VAdd(position, moveVec);

    // プレイヤーのモデルの座標を更新する
    MV1SetPosition(PlayerHandle, position);
}

/// <summary>
/// 影の描画
/// </summary>
void Player::DrawShadow()
{
    DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
}

void Player::DrawTexture()
{
    // テクスチャの描画
    DrawRectGraph(0, 0, 0, 0, 1600, 900, EnptyHpGuage, TRUE, FALSE);
    DrawRectGraph(0, 0, 0, 0, HpGaugeWidth, 900, HpGauge, TRUE, FALSE);
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
    //描画
    DrawShadow();
    MV1DrawModel(PlayerHandle);
}
