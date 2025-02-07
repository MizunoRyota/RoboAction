#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Sound.h"
#include"Pallet.h"
#include"Player.h"
#include"Enemy.h"
#include"HitChecker.h"
#include"EnemyAttackRangeChecker.h"
#include"OnAttackedEnemyHit.h"

Enemy::Enemy()
	: position(VGet(0.0f, 0.0f, 10.0f))
	, shadowBottompos(VGet(0.0f, 0.0f, 0.0f))
	, shadowToppos(VGet(0.0f, 0.0f, 0.0f))
	, currentState(State::TireIdol)
	, angleVector(VGet(0, 0, 0))
	, animBlendRate(0.0f)
	, returnRange(15.0f)
	, prevPlayAnim(-1)
	, ShadowRad(1.7f)
	, prevPlayTime(0)
	, attackTimer(0)
	, chaseCount(0)
	, ExplosionHandle(0)
	, BoostDashHandleFhase1(0)
	, BoostDashHandleFhase2(0)
	, BoostDashHandleFhase3(0)
	, BoostDashHandleFhase4(0)
	, BoostDashHandleFhase5(0)
	, TireHandle(0)
	, tireTimer(0)
	, HpGaugeWidth(1600)
	, playTime(0)
	, AttachIndex(0)	
	, EnemyHandle(0)
	, PlayAnim(-1)
	, AnimTime(0)
	, time(0)
	, hp(5)
	, MoveSpeed(0.25f)
	, ExplosionSEHandle(0)
	, OnenemyHandle(0)
	, isShortAttack(false)
	, isDecreaseHp(false)
	, islimitRange(false)
	, isExplosion(false)
	, isChasing(false)
	, onAttack(false)
	, isAttack(false)
	, isCharge(true)
	, isTurn(false)
	, tire(false)
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
	EnemyHandle = MV1LoadModel("data/model/Enemy/robo.mv1");
	//
	HpGauge = LoadGraph("data/Ui/Texture/EnemyHp2.png");
	EnptyHpGauge = LoadGraph("data/Ui/Texture/EnemyEnptyHp2.png");

	ExplosionSEHandle = LoadSoundMem("data/sound/Explosion.mp3");
	OnenemyHandle = LoadSoundMem("data/sound/Onenemy.mp3");
	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	ExplosionHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Explosion.efkefc", 5.0f);
	BoostDashHandleFhase1 = LoadEffekseerEffect("data/effekseer/EfkFile/BoostDashFhase1.efkefc", 1.0f);
	BoostDashHandleFhase2 = LoadEffekseerEffect("data/effekseer/EfkFile/BoostDashFhase2.efkefc", 1.0f);
	BoostDashHandleFhase3 = LoadEffekseerEffect("data/effekseer/EfkFile/BoostDashFhase3.efkefc", 1.0f);
	BoostDashHandleFhase4 = LoadEffekseerEffect("data/effekseer/EfkFile/BoostDashFhase4.efkefc", 1.0f);
	BoostDashHandleFhase5 = LoadEffekseerEffect("data/effekseer/EfkFile/BoostDashFhase5.efkefc", 1.0f);
	TireHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Tire.efkefc", 2.0f);

	//SetScalePlayingEffekseer3DEffect(playingEffectHandle, EffektScale, EffektScale, EffektScale);
	//SetScalePlayingEffekseer3DEffect(ExplosionHandle, EffektScale, EffektScale, EffektScale);
	position = VGet(0.0f, 0.0f, 10.0f);
	shadowBottompos = VGet(0.0f, 0.0f, 0.0f);
	shadowToppos = VGet(0.0f, 0.0f, 0.0f);
	hp = 5;
	isShortAttack = false;
	isDecreaseHp = false;
	islimitRange = false;
	isExplosion = false;
	isChasing = false;
	onAttack = false;
	isAttack = false;
	isCharge = true;
	isTurn = false;
	tire = false;
	attackTimer = 0;
	tireTimer = 0;
	chaseCount = 0;
	currentState = State::TireIdol;
	prevPlayAnim = -1;
	playTime = 0;
	AttachIndex = 0;
	PlayAnim = -1;
	AnimTime = 0;
	time = -1;
	HpGaugeWidth = 1600;

	// 3D���f���̃X�P�[������
	MV1SetScale(EnemyHandle, VGet(Scale, Scale, Scale));
	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(EnemyHandle, position);

}

void Enemy::Initialize()
{
	// ���f���̓ǂݍ���
	EnemyHandle = MV1LoadModel("data/model/Enemy/robo.mv1");
	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	ExplosionHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Explosion.efkefc", 5.0f);
	BoostDashHandleFhase1 = LoadEffekseerEffect("data/effekseer/EfkFile/BoostDashFhase1.efkefc", 1.0f);
	BoostDashHandleFhase2 = LoadEffekseerEffect("data/effekseer/EfkFile/BoostDashFhase2.efkefc", 1.0f);
	BoostDashHandleFhase3 = LoadEffekseerEffect("data/effekseer/EfkFile/BoostDashFhase3.efkefc", 1.0f);
	BoostDashHandleFhase4 = LoadEffekseerEffect("data/effekseer/EfkFile/BoostDashFhase4.efkefc", 1.0f);
	BoostDashHandleFhase5 = LoadEffekseerEffect("data/effekseer/EfkFile/BoostDashFhase5.efkefc", 1.0f);
	TireHandle = LoadEffekseerEffect("data/effekseer/EfkFile/Tire.efkefc", 2.0f);
	SetScalePlayingEffekseer3DEffect(playingEffectHandle, EffektScale, EffektScale, EffektScale);
	SetScalePlayingEffekseer3DEffect(ExplosionHandle, EffektScale, EffektScale, EffektScale);


	// 3D���f���̃X�P�[������
	MV1SetScale(EnemyHandle, VGet(Scale, Scale, Scale));
	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(EnemyHandle, position);
	hp = 5;
	position = VGet(0.0f, 0.0f, 10.0f);
	isShortAttack = false;
	isDecreaseHp = false;
	islimitRange = false;
	isExplosion = false;
	isChasing = false;
	onAttack = false;
	isAttack = false;
	isCharge = true;
	isTurn = false;
	tire = false;
	attackTimer = 0;
	tireTimer = 0;
	chaseCount = 0;
	currentState = State::TireIdol;
	prevPlayAnim = -1;
	playTime = 0;
	AttachIndex = 0;
	PlayAnim = -1;
	AnimTime = 0;
	time = 0;
	HpGaugeWidth = 1600;
}

void Enemy::InitializeAttack()
{
	isAttack = false;
}

void Enemy::PlayExplosion()
{
	PlaySoundMem(ExplosionSEHandle, DX_PLAYTYPE_BACK, true);       //kettei
}

void Enemy::PlayOnenemy()
{
	PlaySoundMem(OnenemyHandle, DX_PLAYTYPE_BACK, true);           //kettei
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
		if (GetNowCount() - attackTimer >= 8500)
		{
			attackTimer = 0;
			ChangeTire();
			isAttack = false;
		}
	}
}

void Enemy::LimitRange(const OnAttackedEnemy& onAttacked)
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
		if (onAttacked.GetisOnAttack())
		{
			currentState = State::Explosion;
			isExplosion = true;
		}
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
		if (attackRange.GetisMiddleWithin())
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
	}
}

void Enemy::DecreaseHp(const OnAttackedEnemy& onAttacked)
{
	if (onAttack && !isDecreaseHp && islimitRange)
	{
		isDecreaseHp = true;
		hp--;
	}
	else if (hp == 5)
	{
		MoveSpeed = 0.25f;
	}
	if (hp == 4 && HpGaugeWidth >= 1350)
	{
		MoveSpeed = 0.30f;
		HpGaugeWidth -= 2;
	}
	else if (hp == 3 && HpGaugeWidth >= 1250)
	{
		MoveSpeed = 0.35f;
		HpGaugeWidth -= 2;
	}
	else if (hp == 2 && HpGaugeWidth >= 1100)
	{
		MoveSpeed = 0.40f;
		HpGaugeWidth -= 2;
	}
	else if (hp == 1 && HpGaugeWidth >= 950)
	{
		MoveSpeed = 0.43f;
		HpGaugeWidth -= 2;
	}
	else if (hp == 0 && HpGaugeWidth >= 800)
	{
		MoveSpeed = 0.45f;
		HpGaugeWidth -= 2;
	}
}

void Enemy::UpdateEffect(const OnAttackedEnemy& onAttacked)
{
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
	if (onAttacked.GetisOnAttack() && islimitRange || isAttack || tire)
	{
		// ����I�ɃG�t�F�N�g���Đ�����
		// �G�t�F�N�g���Đ�����B
		if (time % 60 == 0)
		{

			StopEffekseer3DEffect(playingEffectHandle);
			if (isAttack)
			{
				if (hp == 5)
				{
					playingEffectHandle = PlayEffekseer3DEffect(BoostDashHandleFhase1);
				}
				else if (hp == 4)
				{
					playingEffectHandle = PlayEffekseer3DEffect(BoostDashHandleFhase2);
				}
				else if (hp == 3)
				{
					playingEffectHandle = PlayEffekseer3DEffect(BoostDashHandleFhase3);
				}
				else if (hp == 2)
				{
					playingEffectHandle = PlayEffekseer3DEffect(BoostDashHandleFhase4);
				}
				else if (hp == 1)
				{
					playingEffectHandle = PlayEffekseer3DEffect(BoostDashHandleFhase5);
				}
			}
			else if (onAttacked.GetisOnAttack() && islimitRange || isExplosion == true)
			{
				PlayExplosion();
				playingEffectHandle = PlayEffekseer3DEffect(ExplosionHandle);
				isExplosion = false;
			}
			else if (tire)
			{
				playingEffectHandle = PlayEffekseer3DEffect(TireHandle);
				SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0.0f, angle + DX_PI_F, 90.0f);
			}
		}
		SetRotationPlayingEffekseer3DEffect(playingEffectHandle, 0.0f, angle + DX_PI_F, 0.0);
		SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y + 3.0f, position.z);

		// ���Ԃ��o�߂�����B
		time++;
	}
	else
	{
		StopEffekseer3DEffect(playingEffectHandle);
		isExplosion = false;
		time = 0.0f;
	}
}

void Enemy::Update(const Player& player, const EnemyAttackRangeChecker& attackRange, const OnAttackedEnemy& onAttacked, const Sound& sound)
{
	//���̏�Ԃ�O�̏�ԂɕύX
	State prevState = currentState;

	//���Ă����Ԃ̐������ԍX�V����
	TireTimer();

	//if (CheckHitKey(KEY_INPUT_R))
	//{
		clsDx();
		printfDx("xpos%f\n", position.x);
		printfDx("ypos%f\n", position.y);
		printfDx("zpos%f\n", position.z);
		printfDx("hp%d\n", hp);
		printfDx("currentState%d\n", currentState);
		printfDx("prevState%d\n", prevState);
		printfDx("PlayAnim%d\n", PlayAnim);
		printfDx("isAttack%d\n", isAttack);
		printfDx("isTurn%d\n", isTurn);
		printfDx("limitRange%d\n", islimitRange);
		printfDx("ChaseCount%d\n", chaseCount);
		printfDx("isShortAttack%d\n", isShortAttack);
	//}
	if (CheckHitKey(KEY_INPUT_T))
	{
		hp = 0;
	}
	//���݂̃A�j���[�V�����̏�ԍX�V����
	currentState = UpdateEnemyState(attackRange,onAttacked);
	//�A�j���[�V�����̕ύX
	UpdateAnimationState(prevState);
	
	//�v���C���[�̕��������N
	UpdateAngle(player);
	RushAttack(player, attackRange);
	MoveOnAttack(onAttacked);
	AttackTimer();

	LimitRange(onAttacked);

	UpdateEffect(onAttacked);

	DecreaseHp(onAttacked);
	//Enemy�̉e�̍X�V
	UpdateShadow();
	//�A�j���[�V�����X�V
	UpdateAnimation();
	// �v���C���[�̃��f���̍��W���X�V����
	MV1SetPosition(EnemyHandle, position);
}

void Enemy::MoveOnAttack(const OnAttackedEnemy& onAttacked)
{
	if (onAttacked.GetisOnAttack() && currentState == State::TireIdol)
	{
		PlayOnenemy();
		onAttack = true;
		// �v���C���[�Ɍ������Đi�ޕ�����P�ʃx�N�g���ŋ��߂�
		VECTOR direction = VAdd(onAttacked.GetAttackAngle(), VGet(0, 0.0f, 0));
		direction = VNorm(direction);
		// �G���i�ދ����i�ړ����x�Ɋ�Â��j
		VECTOR move = VScale(direction, OnMoveSpeed);
		// �G�̈ʒu���X�V
		position = VAdd(position, move);
	}
	else
	{
		onAttack = false;
	}
}

void Enemy::UpdateAngle(const Player& player)
{
	if (!isAttack || !isChasing||currentState==State::Trun )
	{
		// �R�c���f���Q����R�c���f���P�Ɍ������x�N�g�����Z�o
		angleVector = VSub(player.GetPos(), position);

		// atan2 ���g�p���Ċp�x���擾
		angle = atan2(angleVector.x, angleVector.z);

		// atan2 �Ŏ擾�����p�x�ɂR�c���f���𐳖ʂɌ������邽�߂̕␳�l( DX_PI_F )��
		// �������l���R�c���f���� Y����]�l�Ƃ��Đݒ�
		MV1SetRotationXYZ(EnemyHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
	}
}

Enemy::State Enemy::UpdateEnemyState(const EnemyAttackRangeChecker& attackRange, const OnAttackedEnemy& onAttacked)
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
	if (currentState == State::Charge && isCharge == false || currentState == State::Trun)
	{
		nextState = State::Run;
	}
	else if (currentState == State::Run && islimitRange)
	{
		nextState = State::Trun;
		//isTurn = true;
	}
	else if (tire && !isAttack)
	{
		//��ԃt���O�����Ă���Ƃ���Ԃ�tireIdol�ɂ���
		nextState = State::TireIdol;
	}
	if (onAttacked.GetisOnAttack()&&currentState==State::TireIdol)
	{
		nextState = State::OnAttack;
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
				isDecreaseHp = false;
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
	if (prevState == State::Charge && currentState == State::Run || prevState == State::Trun && currentState == State::Run && !isTurn)
	{
		ChangeMotion(AnimKind::Run);
		isAttack = true;
	}
	if (currentState == State::Trun)
	{
		ChangeMotion(AnimKind::Trun);
	}
	//
	if (prevState == State::Run && currentState == State::TireIdol)
	{
		ChangeMotion(AnimKind::TireIdol);
	}
	if (prevState == State::Explosion)
	{
		ChangeMotion(AnimKind::Explosion);
	}
	if (prevState == State::TireIdol && currentState == State::OnAttack)
	{
		ChangeMotion(AnimKind::OnAttack);
	}
}

void Enemy::UpdateGameOver()
{
	position = VGet(0.0f, 0.0f, 10.0f);
	angleVector = VGet(0, 0, 0);
	State prevState = currentState;

	UpdateAnimation();
	MV1SetPosition(EnemyHandle, position);
	MV1SetRotationXYZ(EnemyHandle, VGet(0.0f, 0.0f, 0.0f));
}

void Enemy::UpdateGameClear()
{
	position = VGet(0.0f, 0.0f, 10.0f);
	angleVector = VGet(0, 0, 0);
	State prevState = currentState;

	UpdateAnimation();
	MV1SetPosition(EnemyHandle, position);
	MV1SetRotationXYZ(EnemyHandle, VGet(0.0f, 0.0f, 0.0f));
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

void Enemy::DrawTexture()
{
	// �e�N�X�`���̕`��
	DrawRectGraph(0, 0, 0, 0, 1600, 900, EnptyHpGauge, TRUE, FALSE);
	DrawRectGraph(0, 0, 0, 0, HpGaugeWidth, 900, HpGauge, TRUE, FALSE);
}

void Enemy::Draw()
{
	DrawShadow();
	MV1DrawModel(EnemyHandle);
}

void Enemy::DrawGameOver()
{
	MV1DrawModel(EnemyHandle);
}