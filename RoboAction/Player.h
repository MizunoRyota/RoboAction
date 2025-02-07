#pragma once

class Input;
class Camera;
class OnAttackedPlayer;
class Sound;

class Player
{
public:
	// ���
	enum class State : int
	{
		None = -1,				// �Ȃ�
		Stand = 0,				// �s��
		FinishAttack = 1,		// �Ƃǂ߂̈ꌂ
		FirstAttack = 2,		// �ŏ��̍U��
		SecondAttack = 3,		// 2�i�ڂ̍U��
		LastAttack = 4,			// �Ō�̍U��
		Squat = 5,				//���Ⴊ��
		Roll = 6,				//���[�����O
		Idol = 7,				//�����~�܂�
		Run = 8,				//����
		TakeDamage = 9,			//�_���[�W���󂯂�
	};
	enum class AnimKind : int
	{
		None = -1,				// �Ȃ�
		Stand = 0,				// �s��
		FinishAttack = 1,		// �Ƃǂ߂̈ꌂ
		FirstAttack = 2,		// �ŏ��̍U��
		SecondAttack = 3,		// 2�i�ڂ̍U��
		LastAttack = 4,			// �Ō�̍U��
		Squat = 5,				//���Ⴊ��
		Roll = 6,				//���[�����O
		Idol = 7,				//�����~�܂�
		Run = 8,				//����
		TakeDamage = 9,			//�_���[�W���󂯂�
	};

	Player();
	~Player();

	void Load();	//������
	void Initialize();	//������
	void PlayOnplayer();
	void PlaySlash();
	void Update(const Input& input, const OnAttackedPlayer& onattacked, const Camera& camera, const Sound& sound);  //�X�V
	void UpdateTitle();
	void UpdateTutorial(const Input& input, const OnAttackedPlayer& onattacked, const Camera& camera);		//�Q�[����ʍX�V
	void UpdateGameOver();
	void UpdateGameClear();	
	State UpdateMoveParameterWithPad(const Input& input, VECTOR& moveVec, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec);//�p�b�h�̓��͍X�V
	bool BeAttacked(const OnAttackedPlayer& onattacked);
	void Move(VECTOR& moveVec);
	void DecreaseHp();			//Hp�̌���
	void UpdateEffect();		//�G�t�F�N�g�̍X�V
	void UpdateShadow();		//�v���C���[�̉e�̍X�V
	void UpdateAngle();
	void LimitRange();
	void InvincibleTimer();
	void DrawTexture();											//�e�N�X�`���̕`��
	void DrawShadow();		//�v���C���[�̉e�̕`��
	void Draw();				//�`��
	// ���f���n���h���̎擾.
	const VECTOR& GetPos() const { return position; }
	const VECTOR& GetDirection() const { return targetMoveDirection; }
	const bool& GetisIsAttack() const { return isAttack; }
	const bool& GetisOnAttack() const { return isOnAttack; }
	const int& GetHp() const { return hp; }
private:
	// �ÓI�萔.
	//�v���C���[���g�Ɋւ��郁���o�ÓI�萔
	static constexpr float Scale = 0.006f;		//�傫��
	//�A�j���[�V�����Ɋւ��郁���o�ÓI�萔
	static constexpr float playAttackAnimSpeed = 0.50f;		//�A�j���[�V������i�߂鑬�x
	static constexpr float AnimBlendSpeed = 0.1f;	// �A�j���[�V�����̃u�����h���ω����x
	static constexpr float playAnimSpeed = 0.75f;		//�A�j���[�V������i�߂鑬�x
	static constexpr float	AngleSpeed = 0.6f;		// �p�x�ω����x
	static constexpr float	MoveSpeed = 0.35f;		// �ړ����x
	static constexpr float	AttackSpeed = 1.5f;		// �ړ����x

	Sound* sound;

	//�v���C���[���g�Ɋւ��郁���o�ϐ�
	VECTOR targetMoveDirection;			// ���f���������ׂ������̃x�N�g��
	VECTOR position;					// �|�W�V����.
	int PlayerHandle;					// �v���C���[�̃��f���n���h��
	int hp;								//�̗�
	bool isOnAttack;					// �v���C���[���U�����󂯂����ǂ���	
	bool isAttack;						// �v���C���[���U�������ǂ���
	bool isDecreaseHp;					// �v���C���[��Hp���������������ǂ���
	float isInvincible;					// �v���C���[�����G��Ԃ��ǂ���
	float returnRange;					//�ő�ړ�����
	float invincible;					//���G����
	float angle;						// �p�x
	int alpha;							// �����x
	//HP
	int HpGauge;
	float HpGaugeWidth;
	int EnptyHpGuage;
	//�v���C���[�̍U���Ɋւ��郁���o�ϐ�
	bool isFirstAttack; 
	bool isSecondAttack;
	bool isThirdAttack;
	bool isMoveStick;
	//�A�j���[�V�����Ɋւ��郁���o�ϐ�
	State currentState;				//���݂̃A�j���[�V�����̏��
	//AttackAnimKind currentAttack;	//���݂̍U���A�j���[�V�����̏��
	float playTime;					//�A�j���[�V�����̎��Ԃ̍��v
	int PlayAnim;					//���݂̃A�j���[�V�����A�^�b�`�ԍ�
	int AttachIndex;				//�A�j���[�V������t�^�����ϐ�
	float AnimTime;					//�A�j���[�V������i�߂�ϐ�
	float prevPlayTime;				//�O�̃A�j���[�V�����̎��Ԃ̍��v
	int prevPlayAnim;				//�O�̃A�j���[�V�����A�^�b�`�ԍ�
	float animBlendRate;			//�ߋ��ƌ��݂̃A�j���[�V�����̃u�����h��

	//�v���C���[�̉e
	VECTOR shadowBottompos;			//�e�̒��
	VECTOR shadowToppos;			//�e�̒��_
	float ShadowRad;				//�e�̔��a

	void UpdateAnimationState(State prevState);				//�A�j���[�V�����̏�ԍX�V����
	void UpdateAttackState(State prevState);				//�U����ԍX�V����
	void UpdateAnimation(State prevState);					//Player�̃A�j���[�V�����X�V
	void ChangeMotion(AnimKind  motionNum);					//���[�V�����ύX
	void ResetMotion(State prevState);						//���[�V�������Z�b�g
	void UpdateAttack();									//�U���X�V
	 
	//�G�t�F�N�g�Ɋւ��郁���o�ϐ�

	static constexpr float EffektScale = 10.0f;		//�傫��

	int AttackHandle;					//�G�t�F�N�g�n���h��
	int SecondAttackHandle;				//�G�t�F�N�g�n���h��
	int ThirdAttackHandle;				//�G�t�F�N�g�n���h��
	// �G�t�F�N�g�̕\������ʒu��ݒ肷��B

	// ���Ԃ�����������(����I�ɃG�t�F�N�g���Đ����邽��)
	int time;

	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	int playingEffectHandle = -1;

	int OnPlayerHandle;			//�v���C���[�̃��f���n���h��
	int SlashHandle;			//�X���b�V���G�t�F�N�g�n���h��	

};