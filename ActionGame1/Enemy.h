#pragma once

class EnemyAttackRangeChecker;
class Player;

class Enemy
{
public:

	enum class State :int
	{
		Trun = 0,
		Charge = 1,
		JumpAttack = 2,
		SpinAttack = 3,
		Walk = 4,
		Run = 5,
		Idol = 6,
		Musscle = 7,
		TireIdol = 8,
		SmallDamage = 9,
		BigDamge = 10,
		Missile = 11,
		Blow = 12,
		Die = 13,
	};
	enum class AnimKind : int
	{
		Trun = 0,
		Charge = 1,
		JumpAttack = 2,
		SpinAttack = 3,
		Walk = 4,
		Run = 5,
		Idol=6,
		Musscle=7,
		TireIdol=8,
		SmallDamage=9,
		BigDamge=10,
		Missile=11,
		Blow=12,
		Die=13,
	};

	Enemy();
	~Enemy();
	void Load();									//������
	void InitializeAttack();
	void ChangeTire();
	void TireTimer();
	void Update(const Player& player, const EnemyAttackRangeChecker& attackRange);				//�X�V
	State UpdateEnemyState(const EnemyAttackRangeChecker& attackRange);						//
	void RushAttack(const Player& player, const EnemyAttackRangeChecker& attackRange);
	void UpdateShadow();							//�e�̍X�V
	void UpdateAngle(const Player& player);			//�����̍X�V
	void UpdateAnimationState(State prevState);		//
	void UpdateAnimation();							//
	void UpdateEffect();
	void ChangeChasing();
	void LimitRange();
	void AttackTimer();
	void ChangeMotion(AnimKind  motionNum);			//���[�V�����ύX
	void DrawShadow();								//�e�̕`��
	void Draw();									//�e�̕\��
	// ���f���n���h���̎擾.
	const VECTOR& GetPos() const { return position; }
	const bool& GetIsAttack() const { return isAttack; }

private:
	//�A�j���[�V�����Ɋւ��郁���o�ÓI�萔
	static constexpr float playAnimSpeed = 0.7f;		//�A�j���[�V������i�߂鑬�x
	static constexpr float AnimBlendSpeed = 0.1f;	// �A�j���[�V�����̃u�����h���ω����x
	static constexpr float	MoveSpeed = 0.50f;		// �ړ����x
	static constexpr float Scale = 0.04f;  //�傫��
	static constexpr float	AngleSpeed = 0.6f;		// �p�x�ω����x

	//Enemy���g�Ɋւ��郁���o�ϐ�
	VECTOR position;
	VECTOR angleVector;
	float angle;
	int EnemyHandle;
	int hp;
	//Enemy�̍U���Ɋւ��郁���o�ϐ�
	bool isShortAttack;
	bool islimitRange;
	bool attackReady;
	bool isChasing;
	bool isAttack;
	bool isCharge;
	bool isTurn;
	bool tire;
	float attackTimer;
	float returnRange;
	float tireTimer;
	int chaseCount;
	//�A�j���[�V�����Ɋւ��郁���o�ϐ�
	State currentState;				//���݂̃A�j���[�V�����̏��
	float playTime;					//�A�j���[�V�����̎��Ԃ̍��v
	float AnimTime;					//�A�j���[�V������i�߂�ϐ�
	int AttachIndex;					//�A�j���[�V������t�^�����ϐ�
	int PlayAnim;					//���݂̃A�j���[�V�����A�^�b�`�ԍ�

	float animBlendRate;				//�ߋ��ƌ��݂̃A�j���[�V�����̃u�����h��
	float prevPlayTime;				//�O�̃A�j���[�V�����̎��Ԃ̍��v
	int prevPlayAnim;				//�O�̃A�j���[�V�����A�^�b�`�ԍ�

	//Enemy�[�̉e
	VECTOR shadowToppos;			//�e�̒��_
	VECTOR shadowBottompos;		//�e�̒��
	float ShadowRad;				//�e�̔��a

	//�G�t�F�N�g�Ɋւ��郁���o�ϐ�

	static constexpr float EffektScale = 10.0f;		//�傫��

	
	int TireHandle;

	// ���ł������̂ŉ摜��ǂݍ��ށB
	int grBackgroundHandle;
	int grFrontHandle;
	// �G�t�F�N�g�̕\������ʒu��ݒ肷��B
	VECTOR effectPosition;
	// ���Ԃ�����������(����I�ɃG�t�F�N�g���Đ����邽��)
	int time;

	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	int EnemyEffectHandle = -1;

};

