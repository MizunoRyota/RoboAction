#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"math.h"
#include"Pallet.h"
#include"Player.h"
#include"Input.h"

Player::Player()
	:position(VGet(0.0f, 0.0f, 0.0f))
	, shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
	, shadowToppos(VGet(0.0f, 0.0f, 0.0f))
	, returnRange(20.0f)
	, PlayerHandle(-1)
	, angle(0.0f)
	,isAttack(false)
	,isFirstAttack(true)
	,isSecondAttack(true)
	,isThirdAttack(false)
	, currentState(State::Stand)
	//, currentAttack(AttackAnimKind::UnKown)
	, ShadowRad(0.3f)
	, playTime(0)
	, prevPlayAnim(-1)
	, prevPlayTime(0)
	, animBlendRate(0.0f)
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

	//�l�̏�����
	position = VGet(0.0f, 0.0f, 0.0f);

	// �A�j���[�V�����̃u�����h����������
	animBlendRate = 1.0f;

	// 3D���f���̃X�P�[������
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
	
	//���[�V�����̕ύX
	ChangeMotion(AnimKind::Idol);
	
	// �Đ����Ԃ̏�����
	playTime = 0.0f;
	
	// �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
}
/// <summary>
/// �X�V
/// </summary>
void Player::Update(const Input& input)
{

	// �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
	VECTOR moveVec;			// ���̃t���[���̈ړ��x�N�g��
	State prevState = currentState;
	//AttackAnimKind atttackAnim=currentAttack;
	// �Q�[����ԕω�

    currentState = UpdateMoveParameterWithPad(input, moveVec);

	// �ڂ��񂨂�����
	if (CheckHitKey(KEY_INPUT_G))
	{
		clsDx();
		printfDx("xpos%f\n", position.x);
		printfDx("ypos%f\n", position.y);
		printfDx("zpos%f\n", position.z);
		printfDx("currentState%d\n", currentState);
		printfDx("prevState%d\n",prevState);
		printfDx("PlayAnim%d\n", PlayAnim);
		printfDx("isAttack%d\n", isAttack);
		printfDx("isLimitRange%d\n", isLimitRange);

	}
	// �A�j���[�V�����X�e�[�g�̍X�V
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
 		UpdateAttack();
		UpdateAttackState(prevState);
		//currentAttack=UpdateAnimationAttack(atttackAnim);	//�v���C���[�̍s���A�j���[�V�����̍X�V
	}
	else
	{
		UpdateAnimationState(prevState);
	}

	LimitRange();

	//�v���C���[�������p�x�̍X�V
	UpdateAngle();

	//�|�W�V�����̍X�V
	Move(moveVec);

	//�e�̍X�V
	UpdateShadow();

	//�A�j���[�V��������
	UpdateAnimation();
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
		isLimitRange = true;
	}
	else
	{
		isLimitRange = false;
	}
}

void Player::UpdateAttack()
{
	if (!isFirstAttack)
	{
		currentState = State::FirstAttack;
	}
	else if (!isSecondAttack)
	{
		currentState = State::SecondAttack;
	}
	else if(isFirstAttack&& isSecondAttack)
	{
		currentState = State::LastAttack;
	}

}

//void Player::ChangeAttackMotion(AttackAnimKind prevAnimKind)
//{
//	// ����ւ����s���̂ŁA�P�O�̃��[�V���������L����������f�^�b�`����
//	if (prevPlayAnim != -1)
//	{
//		isAttack = false;
//		//�A�j���[�V�����̃f�^�b�`
//		MV1DetachAnim(PlayerHandle, prevPlayAnim);
//		prevPlayAnim = -1;
//	}
//	// ���܂ōĐ����̃��[�V�������������̂̏���Prev�Ɉړ�����
//	prevPlayAnim = PlayAnim;
//	prevPlayTime = playTime;
//
//	//�V�����A�^�b�`�ԍ���ۑ�
//	PlayAnim = MV1AttachAnim(PlayerHandle, static_cast<int>(prevAnimKind));
//
//	// �Đ����Ԃ̏�����
//	playTime = 0;
//
//	// �u�����h����Prev���L���ł͂Ȃ��ꍇ�͂P�D�O��( ���݃��[�V�������P�O�O���̏�� )�ɂ���
//	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;
//}

//Player::AttackAnimKind Player::UpdateAnimationAttack(AttackAnimKind prevAnimKind)
//{	 
//	AttackAnimKind nextAttack=prevAnimKind;
//
//	// �����~�܂肩��U���ɕς������
//	if (prevAnimKind == AttackAnimKind::UnKown && currentState == State::Stand&&!isAttack)
//	{
//		// �����A�j���[�V�������Đ�����
//		ChangeAttackMotion(AttackAnimKind::FirstAttack);
//		nextAttack = AttackAnimKind::FirstAttack;
//		isAttack = true;
//	}
//	if (prevAnimKind == AttackAnimKind::FirstAttack && currentState == State::Stand&&!isAttack)
//	{
//		// 2���ڃA�j���[�V�������Đ�����
//		ChangeAttackMotion(AttackAnimKind::SecondAttack);
//		nextAttack = AttackAnimKind::SecondAttack;
//		isAttack = true;
//
//	}
//	if (prevAnimKind == AttackAnimKind::SecondAttack && currentState == State::Stand&&!isAttack)
//	{
//		// 3���ڃA�j���[�V�������Đ�����
//		ChangeAttackMotion(AttackAnimKind::LastAttack);
//		nextAttack = AttackAnimKind::UnKown;
//		isAttack = true;
//	}
//
//	return nextAttack;
//
//}

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
void Player::UpdateAnimation()
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
		animTotalTime= MV1GetAttachAnimTotalTime(PlayerHandle, PlayAnim);

		//�A�j���[�V������i�߂�
		playTime += playAnimSpeed;

		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
		if (playTime >= animTotalTime)
		{
			isAttack=false;
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

/// <summary>
/// �e�̍X�V����
/// </summary>
void Player::UpdateShadow()
{
	shadowToppos = VGet(position.x, -0.1, position.z);
	shadowBottompos = VGet(position.x, position.y, position.z);
}

Player::State Player::UpdateMoveParameterWithPad(const Input& input, VECTOR& moveVec)
{

	State nextState = currentState;

	// ���̃t���[���ł̈ړ��x�N�g����������
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	// �ړ��������ǂ����̃t���O��������Ԃł́u�ړ����Ă��Ȃ��v��\��FALSE�ɂ���
	bool isMoveStick = false;
	if (!isAttack)
	{
		// �����{�^���u���v�����͂��ꂽ��J�����̌��Ă���������猩�č������Ɉړ�����
		if (input.GetNowFrameInput() & PAD_INPUT_LEFT)
		{
			// �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
			moveVec = VAdd(moveVec, VGet(-1, 0, 0));

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
			moveVec = VAdd(moveVec, VGet(1, 0, 0));

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
			moveVec = VAdd(moveVec, VGet(0, 0, 1));

			// �ړ��������ǂ����̃t���O���u�ړ������v�ɂ���
			isMoveStick = true;

			isAttack = false;
			isFirstAttack = false;
			isSecondAttack = false;
		}
		else if (input.GetNowFrameInput() & PAD_INPUT_DOWN)
		{
			// �ړ��x�N�g���Ɂu���v�����͂��ꂽ���̈ړ��x�N�g�������Z����
			moveVec = VAdd(moveVec, VGet(0, 0, -1));

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
		else if (currentState == State::FirstAttack || currentState == State::SecondAttack || currentState == State::LastAttack && !isAttack)
		{
			// ��Ԃ��u�����~��v�ɂ���
			nextState = State::Stand;
		}
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
	else if (currentState == State::FirstAttack || currentState == State::SecondAttack || currentState == State::LastAttack && currentState == State::Stand && !isAttack)
	{
		// �����~��A�j���[�V�������Đ�����
		ChangeMotion(AnimKind::Idol);
	}
}

 void Player::UpdateAttackState(State prevState)
 {
	 // �����~�܂肩�瑖��ɕς������
	 if (prevState == State::Stand && currentState == State::FirstAttack&&!isFirstAttack&&!isAttack)
	 {
		 // ����A�j���[�V�������Đ�����
  		 ChangeMotion(AnimKind::FirstAttack);
		 isFirstAttack = true;
		 isAttack = true;
	 }
	 else if (prevState == State::Stand && currentState == State::SecondAttack && !isSecondAttack&&isFirstAttack && !isAttack)
	 {
		 // ����A�j���[�V�������Đ�����
		 ChangeMotion(AnimKind::SecondAttack);
		 isSecondAttack = true;
		 isAttack = true;
	 }
	 else if (prevState == State::Stand && currentState == State::LastAttack && isFirstAttack&&isSecondAttack && !isAttack)
	 {
		 // ����A�j���[�V�������Đ�����
		 ChangeMotion(AnimKind::LastAttack);
		 isFirstAttack = false;
		 isSecondAttack = false;
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

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	//�`��
	DrawShadow();
	MV1DrawModel(PlayerHandle);
}