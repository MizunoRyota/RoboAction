#pragma once

class EnemyAttackRangeChecker;
class OnAttackedEnemy;
class Player;
class Sound;	
class Enemy
{
public:

	enum class State :int
	{
		Idol = 0,
		Charge = 1,
		TireIdol = 2,
		Run = 3,
		Trun = 4,
		OnAttack = 5,
		Explosion = 6,
		Die = 7,
		JumpAttack = 8,
	};
	enum class AnimKind : int
	{
		Idol = 0,
		Charge = 1,
		TireIdol = 2,
		Run = 3,
		Trun = 4,
		OnAttack = 5,
		Explosion = 6,
		Die = 7,
		JumpAttack = 8,
	};

	Enemy();
	~Enemy();
	void Load();									//������
	void Initialize();								//������
	void InitializeAttack();						//������
	void PlayExplosion();
	void PlayOnenemy();
	void ChangeTire();								//����
	void TireTimer();								//���鎞��		
	void Update(const Player& player, const EnemyAttackRangeChecker& attackRange, const OnAttackedEnemy& onAttacked, const Sound& sound);			//�X�V
	State UpdateEnemyState(const EnemyAttackRangeChecker& attackRange, const OnAttackedEnemy& onAttacked);						//
	void RushAttack(const Player& player, const EnemyAttackRangeChecker& attackRange);											//
	void DecreaseHp(const OnAttackedEnemy& onAttacked);			//Hp�̌���
	void UpdateAnimationState(State prevState);					//
	void UpdateAngle(const Player& player);						//�����̍X�V
	void UpdateAnimation();										//
	void UpdateShadow();										//�e�̍X�V
	void UpdateEffect(const OnAttackedEnemy& onAttacked);		//�G�t�F�N�g�̍X�V
	void MoveOnAttack(const OnAttackedEnemy& onAttacked);		//�U�����󂯂����̈ړ�
	void LimitRange(const OnAttackedEnemy& onAttacked);			//�͈͐���
	void ChangeMotion(AnimKind  motionNum);						//���[�V�����ύX
	void ChangeChasing();										//�ǂ�������
	void AttackTimer();											//�U������
	void DrawTexture();											//�e�N�X�`���̕`��
	void DrawShadow();											//�e�̕`��
	void Draw();												//�e�̕\��
	void DrawGameOver();										//�Q�[���I�[�o�[�̕\��
	void UpdateGameClear();										//�Q�[���N���A�X�V
	void UpdateGameOver();										//�Q�[���I�[�o�[�̍X�V	
	// ���f���n���h���̎擾.
	const bool& GetIsExplosion() const { return isExplosion; }
	const int& GetChaseCount() const { return chaseCount; }
	const VECTOR& GetAngle() const { return angleVector; }
	const bool& GetIsAttack() const { return isAttack; }
	const VECTOR& GetPos() const { return position; }
	const int& GetHp() const { return hp; }
	const float& GetFloatAngle() const { return angle; }

private:
	//�A�j���[�V�����Ɋւ��郁���o�ÓI�萔
	static constexpr float playAnimSpeed = 0.5f;	//�A�j���[�V������i�߂鑬�x
	static constexpr float AnimBlendSpeed = 0.1f;	// �A�j���[�V�����̃u�����h���ω����x
	static constexpr float AngleSpeed = 0.6f;		// �p�x�ω����x
	static constexpr float Scale = 0.04f;			//�傫��
	static constexpr float OnMoveSpeed = 1.5;		// �ړ����x
	static constexpr float ChargeAnimSpeed = 0.35;	

	//Enemy���g�Ɋւ��郁���o�ϐ�
	VECTOR angleVector;				//����
	VECTOR position;				//�|�W�V����
	int EnemyHandle;				//���f���n���h��
	float angle;					//�p�x
	int hp;							//�̗�
	float MoveSpeed;				// �ړ����x
	//2/14�ǉ�
	bool isOnAttack;
	//Enemy�̍U���Ɋւ��郁���o�ϐ�
	bool isShortAttack;		//
	bool isDecreaseHp;		//
	bool islimitRange;		//
	bool isExplosion;		//
	bool isChasing;		//
	bool onAttack;		//
	bool isAttack;		//
	bool isCharge;		//
	bool isTurn;		//
	bool tire;		//
	float attackTimer;		//
	float returnRange;		//
	float tireTimer;		//
	int chaseCount;			//
	//�A�j���[�V�����Ɋւ��郁���o�ϐ�
	State currentState;				//���݂̃A�j���[�V�����̏��
	float playTime;					//�A�j���[�V�����̎��Ԃ̍��v
	float AnimTime;					//�A�j���[�V������i�߂�ϐ�
	int AttachIndex;				//�A�j���[�V������t�^�����ϐ�
	int PlayAnim;					//���݂̃A�j���[�V�����A�^�b�`�ԍ�

	float animBlendRate;			//�ߋ��ƌ��݂̃A�j���[�V�����̃u�����h��
	float prevPlayTime;				//�O�̃A�j���[�V�����̎��Ԃ̍��v
	int prevPlayAnim;				//�O�̃A�j���[�V�����A�^�b�`�ԍ�

	//Enemy�[�̉e
	VECTOR shadowToppos;		//�e�̒��_
	VECTOR shadowBottompos;		//�e�̒��
	float ShadowRad;			//�e�̔��a

	//�G�t�F�N�g�Ɋւ��郁���o�ϐ�
	static constexpr float EffektScale = 10.0f;		//�傫��

	int playingEffectHandle = -1;	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	int ExplosionHandle;			//���n���h��
	int BoostDashHandleFhase1;		//
	int BoostDashHandleFhase2;		//
	int BoostDashHandleFhase3;		//
	int BoostDashHandleFhase4;		//
	int BoostDashHandleFhase5;		//

	int TireHandle;					//
	int ChargeHandle;				//	
	int time;						//���Ԃ�����������(����I�ɃG�t�F�N�g���Đ����邽��)

	//HP
	int HpGauge;					//
	float HpGaugeWidth;				//
	int EnptyHpGauge;				//

	int ExplosionSEHandle;			//
	int OnenemyHandle;				//

};

