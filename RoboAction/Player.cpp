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
    // �����Ȃ�
}

Player::~Player()
{
    // �����Ȃ�
}

void Player::Load()
{
    // ���f���̓ǂݍ���
    PlayerHandle = MV1LoadModel("data/model/Player/Player.mv1");
    //
    HpGauge = LoadGraph("data/Ui/Texture/PlayerHp1.png");
    EnptyHpGuage = LoadGraph("data/Ui/Texture/EnptyPlayerHp2.png");

    OnPlayerHandle = LoadSoundMem("data/sound/Onplayer.mp3");
    SlashHandle = LoadSoundMem("data/sound/Slash.mp3");

    // �G�t�F�N�g���\�[�X��ǂݍ��ށB
    AttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Attack1.efkefc", 1.0f);
    SecondAttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/PlayerSecondAttack.efkefc", 0.750f);
    ThirdAttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/PlayerThirdAttack.efkefc", 0.750f);

    SetScalePlayingEffekseer3DEffect(AttackHandle, EffektScale, EffektScale, EffektScale);
    SetScalePlayingEffekseer3DEffect(SecondAttackHandle, EffektScale, EffektScale, EffektScale);
    SetScalePlayingEffekseer3DEffect(ThirdAttackHandle, EffektScale, EffektScale, EffektScale);

    //�l�̏�����
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
    // �A�j���[�V�����̃u�����h����������
    animBlendRate = 1.0f;
	PlayAnim = -1;
	HpGaugeWidth = 450;
	hp = 3;


    // 3D���f���̃X�P�[������
    MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
    //���[�V�����̕ύX
    ChangeMotion(AnimKind::Idol);

    // �Đ����Ԃ̏�����
    playTime = 0.0f;

    // �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
    MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 0.0f, 0.0f));
}

void Player::Initialize()
{
    // ���f���̓ǂݍ���
    PlayerHandle = MV1LoadModel("data/model/Player/Player.mv1");
    //
    HpGauge = LoadGraph("data/Ui/Texture/PlayerHp1.png");
    EnptyHpGuage = LoadGraph("data/Ui/Texture/EnptyPlayerHp1.png");
    // �G�t�F�N�g���\�[�X��ǂݍ��ށB
    AttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Attack1.efkefc", 1.0f);
    SecondAttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/PlayerSecondAttack.efkefc", 0.750f);
    ThirdAttackHandle = LoadEffekseerEffect("data/effekseer/EfkFile/PlayerThirdAttack.efkefc", 0.750f);

    //SetScalePlayingEffekseer3DEffect(AttackHandle, EffektScale, EffektScale, EffektScale);
    //SetScalePlayingEffekseer3DEffect(SecondAttackHandle, EffektScale, EffektScale, EffektScale);
    //SetScalePlayingEffekseer3DEffect(ThirdAttackHandle, EffektScale, EffektScale, EffektScale);

    //�l�̏�����
    position = VGet(0.0f, 0.0f, 0.0f);

    // �A�j���[�V�����̃u�����h����������
    animBlendRate = 1.0f;

    // 3D���f���̃X�P�[������
    MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));

    //currentState = State::Stand;

    ////���[�V�����̕ύX
    //hangeMotion(AnimKind::Idol);

    // �Đ����Ԃ̏�����
    playTime = 0.0f;

    // �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
    MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 0.0f, 0.0f));
    // 3D���f���̃X�P�[������
    MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
    //�l�̏�����
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
        // ����̌Ăяo�����ɊJ�n������ݒ�
        if (isInvincible == 0)
        {
            isInvincible = GetNowCount();  // �~���b�P�ʂŌ��ݎ������擾
        }

        // �o�ߎ��Ԃ�3000�~���b(3�b)�ȏ�o�߂�����t���O��؂�ւ���
        if (GetNowCount() - isInvincible >= 2000)
        {
            isInvincible = 0;
            isDecreaseHp = false;
        }
        else
        {
            // ����̌Ăяo�����ɊJ�n������ݒ�
            if (invincible == 0)
            {
                invincible = GetNowCount();  // �~���b�P�ʂŌ��ݎ������擾
            }

            // �o�ߎ��Ԃ�3000�~���b(3�b)�ȏ�o�߂�����t���O��؂�ւ���
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
        // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
        Effekseer_Sync3DSetting();

 
            StopEffekseer3DEffect(playingEffectHandle);
            // ����I�ɃG�t�F�N�g���Đ�����
                // �G�t�F�N�g���Đ�����B
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
        

        // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
        UpdateEffekseer3D();

        SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y + 0.2f, position.z);
        SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0.0f, angle + DX_PI_F, 0.0);
        // ���Ԃ��o�߂�����B
        time++;
    }
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update(const Input& input, const OnAttackedPlayer& onattacked, const Camera& camera,const Sound& sound)
{

    // �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
    VECTOR moveVec;			// ���̃t���[���̈ړ��x�N�g��
    VECTOR	upMoveVec;		// �����{�^���u���v����͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
    VECTOR	leftMoveVec;	// �����{�^���u���v����͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
    State prevState = currentState;
    // �Q�[����ԕω�

    BeAttacked(onattacked);
    DecreaseHp();
    currentState = UpdateMoveParameterWithPad(input, moveVec, camera, leftMoveVec, upMoveVec);

    //// �ڂ��񂨂�����
    //clsDx();
    //printfDx("xpos%f\n", position.x);
    //printfDx("ypos%f\n", position.y);
    //printfDx("zpos%f\n", position.z);
    //printfDx("currentState%d\n", currentState);
    //printfDx("prevState%d\n", prevState);
    //printfDx("isAttack%d\n", isAttack);
    //printfDx("isOnAttack%d\n", isOnAttack);
    //printfDx("hp%d\n", hp);

    // �A�j���[�V�����X�e�[�g�̍X�V
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

    //�v���C���[�������p�x�̍X�V
    UpdateAngle();

    //�|�W�V�����̍X�V
    Move(moveVec);

    //�e�̍X�V
    UpdateShadow();

    //�A�j���[�V��������
    UpdateAnimation(prevState);
    InvincibleTimer();
    MV1SetOpacityRate(PlayerHandle, alpha);
}

void Player::UpdateTutorial(const Input& input, const OnAttackedPlayer& onattacked, const Camera& camera)
{
        // �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
    VECTOR moveVec;			// ���̃t���[���̈ړ��x�N�g��
    VECTOR	upMoveVec;		// �����{�^���u���v����͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
    VECTOR	leftMoveVec;	// �����{�^���u���v����͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
    State prevState = currentState;
    // �Q�[����ԕω�
        //// �ڂ��񂨂�����
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

    // �A�j���[�V�����X�e�[�g�̍X�V
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

    //�v���C���[�������p�x�̍X�V
    UpdateAngle();

    //�e�̍X�V
    UpdateShadow();

    //�A�j���[�V��������
    UpdateAnimation(prevState);
    InvincibleTimer();
    MV1SetOpacityRate(PlayerHandle, alpha);
    // �v���C���[�̃��f���̍��W���X�V����
    MV1SetPosition(PlayerHandle, position);
}

void Player::UpdateTitle() 
{
    State prevState = currentState;

    UpdateAnimation(prevState);
}

void Player::LimitRange()
{
    ////���S����v���C���[�̋����𑪂�

    float r = VSize(VSub(position, VGet(0, 0, 0)));

    ////���̋����ɒB�����炻��ȏア���Ȃ��悤�ɂ���

    if (r > returnRange || r < -returnRange)
    {
        printfDx("returnRange%f\n", r);

        //���S���W����v���C���[���W�̋���

        VECTOR distance = VSub(VGet(0, 0, 0), position);

        //���K��

        distance = VNorm(distance);

        //�߂��ʂ��v�Z�A���Z����

        VECTOR returnPosition = VScale(distance, (r - returnRange));

        position = VAdd(position, returnPosition);
    }

}

void Player::UpdateAttack()
{
    // �G�t�F�N�g���Đ�����B
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
/// �A�j���[�V�����̕ύX
/// </summary>
/// <param name="motionNum"></param>
void Player::ChangeMotion(AnimKind motionNum)
{
    // ����ւ����s���̂ŁA�P�O�̃��[�V���������L����������f�^�b�`����
    if (prevPlayAnim != -1)
    {
        //�A�j���[�V�����̃f�^�b�`
        MV1DetachAnim(PlayerHandle, prevPlayAnim);
        prevPlayAnim = -1;
    }
    // ���܂ōĐ����̃��[�V�������������̂̏���Prev�Ɉړ�����
    prevPlayAnim = PlayAnim;
    prevPlayTime = playTime;

    //�V�����A�^�b�`�ԍ���ۑ�
    PlayAnim = MV1AttachAnim(PlayerHandle, static_cast<int>(motionNum));

    // �Đ����Ԃ̏�����
    playTime = 0;

    // �u�����h����Prev���L���ł͂Ȃ��ꍇ�͂P�D�O��( ���݃��[�V�������P�O�O���̏�� )�ɂ���
    animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;

}

/// <summary>
/// �A�j���[�V�����̍X�V����
/// </summary>
void Player::UpdateAnimation(State prevState)
{
    // �Đ����Ă���A�j���[�V�����̑�����
    float animTotalTime;

    // �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
    if (animBlendRate < 1.0f)
    {
        animBlendRate += AnimBlendSpeed;
        if (animBlendRate > 1.0f)
        {
            animBlendRate = 1.0f;
        }
    }

    //�Đ����Ă���A�j���[�V�����̏����P
    if (PlayAnim != -1)
    {
        // �A�j���[�V�����̑����Ԃ��擾
        animTotalTime = MV1GetAttachAnimTotalTime(PlayerHandle, PlayAnim);

        //�A�j���[�V������i�߂�
        if (isAttack)
        {
            playTime += AttackSpeed;
        }
        else
        {
            playTime += playAnimSpeed;
        }
        // �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
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

        // �ύX�����Đ����Ԃ����f���ɔ��f������
        MV1SetAttachAnimTime(PlayerHandle, PlayAnim, playTime);
        // �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
        MV1SetAttachAnimBlendRate(PlayerHandle, PlayAnim, animBlendRate);
    }
    // �Đ����Ă���A�j���[�V�����Q�̏���
    if (prevPlayAnim != -1)
    {
        // �A�j���[�V�����̑����Ԃ��擾
        animTotalTime = MV1GetAttachAnimTotalTime(PlayerHandle, prevPlayAnim);

        // �Đ����Ԃ�i�߂�
        prevPlayTime += playAnimSpeed;

        // �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
        if (prevPlayTime > animTotalTime)
        {
            prevPlayTime = static_cast<float>(fmod(prevPlayTime, animTotalTime));
        }

        // �ύX�����Đ����Ԃ����f���ɔ��f������
        MV1SetAttachAnimTime(PlayerHandle, prevPlayAnim, prevPlayTime);

        // �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
        MV1SetAttachAnimBlendRate(PlayerHandle, prevPlayAnim, 1.0f - animBlendRate);
    }
}

void Player::ResetMotion(State prevState)
{
    if (prevState == State::FirstAttack && currentState == State::FirstAttack || prevState == State::SecondAttack && currentState == State::SecondAttack || prevState == State::LastAttack && currentState == State::LastAttack && isAttack || prevState == State::TakeDamage && currentState == State::TakeDamage)
    {
        // �����~��A�j���[�V�������Đ�����
        ChangeMotion(AnimKind::Idol);
        currentState = State::Stand;
    }
}

/// <summary>
/// �e�̍X�V����
/// </summary>
void Player::UpdateShadow()
{
    shadowToppos = VGet(position.x, -0.002, position.z);
    shadowBottompos = VGet(position.x, position.y, position.z);
}

Player::State Player::UpdateMoveParameterWithPad(const Input& input, VECTOR& moveVec, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec)
{

    State nextState = currentState;

    // �v���C���[�̈ړ������̃x�N�g�����Z�o
// �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���̓J�����̎�����������x�����𔲂�������
    upMoveVec = VSub(camera.GetTarget(), camera.GetPosition());
    upMoveVec.y = 0.0f;

    // �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���͏���������Ƃ��̕����x�N�g���Ƃx���̃v���X�����̃x�N�g���ɐ����ȕ���
    leftMoveVec = VCross(upMoveVec, VGet(0.0f, 1.0f, 0.0f));

    // ��̃x�N�g���𐳋K��( �x�N�g���̒������P�D�O�ɂ��邱�� )
    upMoveVec = VNorm(upMoveVec);
    leftMoveVec = VNorm(leftMoveVec);

    // ���̃t���[���ł̈ړ��x�N�g����������
      moveVec = VGet(0.0f, 0.0f, 0.0f);

    // �ړ��������ǂ����̃t���O��������Ԃł́u�ړ����Ă��Ȃ��v��\��FALSE�ɂ���
    isMoveStick = false;

    if (!isAttack && currentState != State::TakeDamage && (input.GetNowFrameInput() & PAD_INPUT_D) == 0)
    {
        // �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�č������Ɉړ�����
        if (input.GetNowFrameInput() & PAD_INPUT_LEFT)
        {
            // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
            moveVec = VAdd(moveVec, leftMoveVec);

            // �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
            isMoveStick = true;

            //
            isAttack = false;
            isFirstAttack = false;
            isSecondAttack = false;
        }
        else if (input.GetNowFrameInput() & PAD_INPUT_RIGHT)
        {
            // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
            moveVec = VAdd(moveVec,VScale(leftMoveVec,-1.0f));

            // �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
            isMoveStick = true;

            //
            isAttack = false;
            isFirstAttack = false;
            isSecondAttack = false;
        }
        if (input.GetNowFrameInput() & PAD_INPUT_UP)
        {
            // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
            moveVec = VAdd(moveVec, upMoveVec);

            // �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
            isMoveStick = true;

            isAttack = false;
            isFirstAttack = false;
            isSecondAttack = false;
        }
        else if (input.GetNowFrameInput() & PAD_INPUT_DOWN)
        {
            // �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
            moveVec = VAdd(moveVec, VScale(upMoveVec,-1.0f));

            // �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
            isMoveStick = true;

            isAttack = false;
            isFirstAttack = false;
            isSecondAttack = false;
        }
    }
    // �ړ��{�^���������ꂽ���ǂ����ŏ����𕪊�
    if (isMoveStick)
    {

        // �������܂Łu�����~�܂�v��Ԃ�������
        if (currentState == State::Stand)
        {
            // ��Ԃ��u����v�ɂ���
            nextState = State::Run;
        }

        // �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
        targetMoveDirection = VNorm(moveVec);

        // �v���C���[�������ׂ������x�N�g�����v���C���[�̃X�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
        moveVec = VScale(targetMoveDirection, MoveSpeed);

    }
    else
    {
        // ���̃t���[���ňړ����Ă��Ȃ��āA����Ԃ��u����v��������
        if (currentState == State::Run)
        {
            // ��Ԃ��u�����~��v�ɂ���
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
/// �p�x�̍X�V����
/// </summary>
void Player::UpdateAngle()
{
    // �v���C���[�̈ړ������Ƀ��f���̕������߂Â���
    float targetAngle;			// �ڕW�p�x
    float difference;			// �ڕW�p�x�ƌ��݂̊p�x�Ƃ̍�

    // �ڕW�̕����x�N�g������p�x�l���Z�o����
    targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

    // �ڕW�̊p�x�ƌ��݂̊p�x�Ƃ̍�������o��
    // �ŏ��͒P���Ɉ����Z
    difference = targetAngle - angle;

    // ����������炠������̍����P�W�O�x�ȏ�ɂȂ邱�Ƃ͖����̂�
    // ���̒l���P�W�O�x�ȏ�ɂȂ��Ă�����C������
    if (difference < -DX_PI_F)
    {
        difference += DX_TWO_PI_F;
    }
    else if (difference > DX_PI_F)
    {
        difference -= DX_TWO_PI_F;
    }

    // �p�x�̍����O�ɋ߂Â���
    if (difference > 0.0f)
    {
        // �����v���X�̏ꍇ�͈���
        difference -= AngleSpeed;
        if (difference < 0.0f)
        {
            difference = 0.0f;
        }
    }
    else
    {
        // �����}�C�i�X�̏ꍇ�͑���
        difference += AngleSpeed;
        if (difference > 0.0f)
        {
            difference = 0.0f;
        }
    }

    // ���f���̊p�x���X�V
    angle = targetAngle - difference;
    MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// �A�j���[�V�����̍X�V����
/// </summary>
void Player::UpdateAnimationState(State prevState)
{
    // �����~�܂肩�瑖��ɕς������
    if (prevState == State::Stand && currentState == State::Run)
    {
        // ����A�j���[�V�������Đ�����
        ChangeMotion(AnimKind::Run);
    }
    // ���肩�痧���~�܂�ɕς������
    if (prevState == State::Run && currentState == State::Stand)
    {
        // �����~��A�j���[�V�������Đ�����
        ChangeMotion(AnimKind::Idol);
    }
    if (isOnAttack && currentState == State::TakeDamage)
    {
        // �_���[�W���[�V�������Đ�����
        ChangeMotion(AnimKind::TakeDamage);
    }
}

void Player::UpdateAttackState(State prevState)
{
    // �����~�܂肩�瑖��ɕς������
    if (prevState == State::Stand && currentState == State::FirstAttack && !isFirstAttack && !isAttack)
    {
        // ����A�j���[�V�������Đ�����
        ChangeMotion(AnimKind::FirstAttack);
        isFirstAttack = true;
        isAttack = true;
    }
    else if (prevState == State::Stand && currentState == State::SecondAttack && !isSecondAttack && isFirstAttack && !isAttack)
    {
        // ����A�j���[�V�������Đ�����
        ChangeMotion(AnimKind::SecondAttack);
        isSecondAttack = true;
        isAttack = true;
    }
    else if (prevState == State::Stand && currentState == State::LastAttack && isFirstAttack && isSecondAttack && !isAttack)
    {
        // ����A�j���[�V�������Đ�����
        ChangeMotion(AnimKind::LastAttack);
        isThirdAttack = true;
        isAttack = true;
    }
}

void Player::Move(VECTOR& moveVec)
{
    position = VAdd(position, moveVec);

    // �v���C���[�̃��f���̍��W���X�V����
    MV1SetPosition(PlayerHandle, position);
}

/// <summary>
/// �e�̕`��
/// </summary>
void Player::DrawShadow()
{
    DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
}

void Player::DrawTexture()
{
    // �e�N�X�`���̕`��
    DrawRectGraph(0, 0, 0, 0, 1600, 900, EnptyHpGuage, TRUE, FALSE);
    DrawRectGraph(0, 0, 0, 0, HpGaugeWidth, 900, HpGauge, TRUE, FALSE);
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
    //�`��
    DrawShadow();
    MV1DrawModel(PlayerHandle);
}
