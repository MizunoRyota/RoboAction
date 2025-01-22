#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Pallet.h"
#include"Player.h"
#include"Enemy.h"
#include"HitChecker.h"
#include"EnemyAttackRangeChecker.h"

Enemy::Enemy()
	:position(VGet(0.0f, 0.0f, 10.0f))
	, angleVector(VGet(0, 0, 0))
	, shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
	, shadowToppos(VGet(0.0f, 0.0f, 0.0f))
	, currentState(State::TireIdol)
	, returnRange(15.0f)
	, chaseCount(0)
	, animBlendRate(0.0f)
	, prevPlayAnim(-1)
	, ShadowRad(1.7f)
	, tireTimer(0)
	, prevPlayTime(0)
	, isAttack(false)
	,isChasing (false)
	,isCharge(true)
	, islimitRange(false)
	,isTurn(false)
	, tire(false)
	, playTime(0)
	, attackTimer(0)
	,TireHandle(0)
{
	//�����Ȃ�
}

Enemy::~Enemy()
{
	MV1DeleteModel(EnemyHandle);
}

void Enemy::Load()
{
	// ���f���̓ǂݍ���
	EnemyHandle = MV1LoadModel("data/model/Enemy/newEnemy.mv1");

	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	TireHandle = LoadEffekseerEffect("data/effekseer/EfkFile/EnemyTire.efkefc", 1.5f);

	SetScalePlayingEffekseer3DEffect(TireHandle, EffektScale, EffektScale, EffektScale);

	// 3D���f���̃X�P�[������
	MV1SetScale(EnemyHandle, VGet(Scale, Scale, Scale));
	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(EnemyHandle, position);

}

void Enemy::InitializeAttack()
{
	isAttack = false;
}

void Enemy::ChangeTire()
{
	if (isAttack == true)
	{
		tire = true;
	}
	else
	{
		tire = false;
	}
}

void Enemy::ChangeChasing()
{
	isChasing = true;
}

void Enemy::TireTimer()
{
	if (tire == true)
	{
		// ����̌Ăяo�����ɊJ�n������ݒ�
		if (tireTimer == 0)
		{
			tireTimer = GetNowCount();  // �~���b�P�ʂŌ��ݎ������擾
		}

		// �o�ߎ��Ԃ�3000�~���b(3�b)�ȏ�o�߂�����t���O��؂�ւ���
		if (GetNowCount() - tireTimer >= 5000)
		{
			tire = false;
			isCharge = true;
			tireTimer = 0;
		}
	}
}

void Enemy::AttackTimer()
{
	if (isAttack == true)
	{
		// ����̌Ăяo�����ɊJ�n������ݒ�
		if (attackTimer == 0)
		{
			attackTimer = GetNowCount();  // �~���b�P�ʂŌ��ݎ������擾
		}
		// �o�ߎ��Ԃ�3000�~���b(3�b)�ȏ�o�߂�����t���O��؂�ւ���
		if (GetNowCount() - attackTimer >= 15000)
		{
			attackTimer = 0;
			ChangeTire();
			isAttack = false;
		}
	}
}

void Enemy::LimitRange()
{
	////���S����v���C���[�̋����𑪂�

	float r = VSize(VSub(position, VGet(0, 0, 0)));

	////���̋����ɒB�����炻��ȏア���Ȃ��悤�ɂ���

	if (r > returnRange || r < -returnRange)
	{

		//���S���W����v���C���[���W�̋���
		VECTOR distance = VSub(VGet(0, 0, 0), position);

		//���K��
		distance = VNorm(distance);

		//�߂��ʂ��v�Z�A���Z����
		VECTOR returnPosition = VScale(distance, (r - returnRange));

		position = VAdd(position, returnPosition);

		islimitRange = true;
		chaseCount++;
	}
	else
	{
		islimitRange = false;
	}
}

void Enemy::RushAttack(const Player& player, const EnemyAttackRangeChecker& attackRange)
{
	if (!tire && isAttack && !isCharge&&!islimitRange)
	{
		if (chaseCount>=4)
		{
			isChasing = false;
			chaseCount = 0;
		}

		// �v���C���[�ƓG�̈ʒu�x�N�g��
		VECTOR enemyPos = position;

		// �v���C���[�ƓG�̈ʒu�x�N�g���̍���
		VECTOR toTarget = VSub(player.GetPos(), enemyPos);

		// �x�N�g���̒����i�����j
		float distance = VSize(angleVector);

		// �ڕW�ɓ��B�����ꍇ�A�G�͂��̂܂ܐi�ݑ�����
		if (attackRange.GetisShortWithin())
		{
			isChasing = true;
		}

		// �ڕW�ɓ��B���Ă��Ȃ��ꍇ�݈̂ړ�
		if (!isChasing) {
			// �v���C���[�Ɍ������Đi�ޕ�����P�ʃx�N�g���ŋ��߂�
			VECTOR direction = VNorm(angleVector);

			// �G���i�ދ����i�ړ����x�Ɋ�Â��j
			VECTOR move = VScale(direction, MoveSpeed);

			// �G�̈ʒu���X�V
			position = VAdd(enemyPos, move);
		}
		else {
			// �ڕW�ɓ��B������͂��̂܂ܐi�ݑ�����
			// �����ōēx���������߂Ă��̕����ɐi�ݑ�����i�Ⴆ�Ε�����ێ����ēːi�j
			VECTOR move = VScale(angleVector, MoveSpeed / distance);  // ���݈ʒu����i�ޕ���
			position = VAdd(enemyPos, move);
		}
		//printfDx("%f\n", distance);
	}
}

void Enemy::UpdateEffect()
{
	effectPosition = VGet(position.x, position.y, position.z);
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();

	EnemyEffectHandle = PlayEffekseer3DEffect(TireHandle);
	// ����I�ɃG�t�F�N�g���Đ�����
	if (time % 60 == 0)
	{
		StopEffekseer3DEffect(EnemyEffectHandle);
		// �G�t�F�N�g���Đ�����B
	}

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();

	SetPosPlayingEffekseer3DEffect(EnemyEffectHandle, effectPosition.x, effectPosition.y, effectPosition.z);
	SetRotationPlayingEffekseer3DEffect(EnemyEffectHandle, 0.0f, angle + DX_PI_F, 0.0);
	// ���Ԃ��o�߂�����B
	time++;

}

void Enemy::Update(const Player& player, const EnemyAttackRangeChecker& attackRange)
{
	//���̏�Ԃ�O�̏�ԂɕύX
	State prevState = currentState;

	//���Ă����Ԃ̐������ԍX�V����
	TireTimer();
	UpdateEffect();

	if (CheckHitKey(KEY_INPUT_R))
	{
		clsDx();
		printfDx("xpos%f\n", position.x);
		printfDx("ypos%f\n", position.y);
		printfDx("zpos%f\n", position.z);
		printfDx("currentState%d\n", currentState);
		printfDx("prevState%d\n", prevState);
		printfDx("PlayAnim%d\n", PlayAnim);
		printfDx("isAttack%d\n", isAttack);
		printfDx("isTurn%d\n", isTurn);
		printfDx("limitRange%d\n", islimitRange);
		printfDx("ChaseCount%d\n", chaseCount);

		printfDx("isShortAttack%d\n", isShortAttack);
	}

	//���݂̃A�j���[�V�����̏�ԍX�V����
	currentState = UpdateEnemyState(attackRange);
	//�A�j���[�V�����̕ύX
	UpdateAnimationState(prevState);
	
	//�v���C���[�̕��������N
	UpdateAngle(player);

	RushAttack(player, attackRange);

	AttackTimer();

	LimitRange();

	//Enemy�̉e�̍X�V
	UpdateShadow();
	//�A�j���[�V�����X�V
	UpdateAnimation();
	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(EnemyHandle, position);
}

void Enemy::UpdateAngle(const Player& player)
{
	if (!isAttack || !isChasing||currentState==State::Trun )
	{
		float Angle;
		// �R�c���f���Q����R�c���f���P�Ɍ������x�N�g�����Z�o
		angleVector = VSub(player.GetPos(), position);

		// atan2 ���g�p���Ċp�x���擾
		Angle = atan2(angleVector.x, angleVector.z);

		// atan2 �Ŏ擾�����p�x�ɂR�c���f���𐳖ʂɌ������邽�߂̕␳�l( DX_PI_F )��
		// �������l���R�c���f���� Y����]�l�Ƃ��Đݒ�
		MV1SetRotationXYZ(EnemyHandle, VGet(0.0f, Angle + DX_PI_F, 0.0f));
	}
}

Enemy::State Enemy::UpdateEnemyState(const EnemyAttackRangeChecker& attackRange)
{
	State nextState = currentState;
	//�����͈͓��ɂ��邩�U�����łȂ������Ă��Ȃ�
	if (!isAttack && !tire && isCharge)
	{
		// �������܂Łu�����~�܂�v��Ԃ�������
		if (currentState == State::TireIdol)
		{
			// ��Ԃ��u����v�ɂ���
			nextState = State::Charge;
		}
	}
	//�U�����̎��ɑҋ@��Ԃɂ���
	if (currentState == State::Charge && isCharge == false||currentState==State::Trun)
	{
		nextState = State::Run;
	}
	else if (currentState == State::Run && islimitRange)
	{
		nextState = State::Trun;
		//isTurn = true;
	}
	else if (tire&&!isAttack)
	{
		//��ԃt���O�����Ă���Ƃ���Ԃ�tireIdol�ɂ���
		nextState = State::TireIdol;
	}

	return nextState;

}

void Enemy::ChangeMotion(AnimKind motionNum)
{
	// ����ւ����s���̂ŁA�P�O�̃��[�V���������L����������f�^�b�`����
	if (prevPlayAnim != -1)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(EnemyHandle, prevPlayAnim);
		prevPlayAnim = -1;
	}
	// ���܂ōĐ����̃��[�V�������������̂̏���Prev�Ɉړ�����
	prevPlayAnim = PlayAnim;
	prevPlayTime = playTime;

	//�V�����A�^�b�`�ԍ���ۑ�
	PlayAnim = MV1AttachAnim(EnemyHandle, static_cast<int>(motionNum));

	// �Đ����Ԃ̏�����
	playTime = 0;

	// �u�����h����Prev���L���ł͂Ȃ��ꍇ�͂P�D�O��( ���݃��[�V�������P�O�O���̏�� )�ɂ���
	animBlendRate = prevPlayAnim == -1 ? 1.0f : 0.0f;
}

void Enemy::UpdateAnimation()
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
		animTotalTime = MV1GetAttachAnimTotalTime(EnemyHandle, PlayAnim);

		//�A�j���[�V������i�߂�
		playTime += playAnimSpeed;

		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
		if (playTime >= animTotalTime)
		{
			if (currentState == State::Charge)
			{
				isCharge = false;
			}
			if (isTurn)
			{
				isTurn = false;
			}
			playTime = static_cast<float>(fmod(playTime, animTotalTime));
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(EnemyHandle, PlayAnim, playTime);
		// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(EnemyHandle, PlayAnim, animBlendRate);
	}
	// �Đ����Ă���A�j���[�V�����Q�̏���
	if (prevPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		animTotalTime = MV1GetAttachAnimTotalTime(EnemyHandle, prevPlayAnim);

		// �Đ����Ԃ�i�߂�
		prevPlayTime += playAnimSpeed;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (prevPlayTime > animTotalTime)
		{
			prevPlayTime = static_cast<float>(fmod(prevPlayTime, animTotalTime));
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(EnemyHandle, prevPlayAnim, prevPlayTime);

		// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(EnemyHandle, prevPlayAnim, 1.0f - animBlendRate);
	}
}

/// <summary>
/// �A�j���[�V�����̍X�V����
/// </summary>
void Enemy::UpdateAnimationState(State prevState)
{
	//
	if (prevState == State::TireIdol && currentState == State::Charge)
	{
		ChangeMotion(AnimKind::Charge);
	}
	//
	if (prevState == State::Charge && currentState == State::Run||prevState==State::Trun&&currentState==State::Run&&!isTurn)
	{
		ChangeMotion(AnimKind::Run);
		isAttack = true;
	}
	if (currentState==State::Trun)
	{
		ChangeMotion(AnimKind::Trun);
	}
	//
	if (prevState == State::Run && currentState == State::TireIdol)
	{
		ChangeMotion(AnimKind::TireIdol);
	}
}

void Enemy::UpdateShadow()
{
	shadowToppos = VGet(position.x, -0.1f, position.z);
	shadowBottompos = VGet(position.x, position.y, position.z);
}

void Enemy::DrawShadow()
{
	DrawCone3D(shadowToppos, shadowBottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
}

void Enemy::Draw()
{

	DrawShadow();
	MV1DrawModel(EnemyHandle);
}