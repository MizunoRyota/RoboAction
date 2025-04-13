#pragma once

class EnemyAttackRangeChecker;
class Player;
class Enemy;
class Input;
/// <summary>
/// �J����
/// </summary>
class Camera
{
public:
	Camera();			// �R���X�g���N�^.
	~Camera();			// �f�X�g���N�^.
	void Load();		//������

	void GameTitle(const Player& player);//�Q�[���^�C�g��
	void ReadyUpdate(const Player& player);//�`���[�g���A�����
	void Update(const Player& player,const Input& input, const Enemy& enemy, const EnemyAttackRangeChecker& attackRange);	// �X�V.
	void FixCameraPosition();
	void ShakeCamera(float intensity, float duration, const Player& player);
	void GameEnd(const Enemy& enemy);//�Q�[���I�[�o�[��ʏ���
	void GameClear(const Enemy& enemy);//�Q�[���N���A��ʏ���
	// �|�W�V������getter/setter.
	const VECTOR& GetPosition() const { return position; }
	const VECTOR& GetTarget()	const { return targetposition; }

private:
	static constexpr float Zoom = -3.0f;			//z���̃J�����|�W�V����
	static constexpr float Hight = 3.0f;			//y���̃J�����|�W�V����
	static constexpr float TargetHight = 1.3;		//�^�[�Q�b�g�̌��鍂��
	static constexpr float AngleSpeed = 0.15f;		//�������ς��X�s�[�h
	float            angleVertical;					// �J�����̐����p�x
	float            angleHorizontal;				// �J�����̐����p�x

	// �h��̋����Ǝ�������
	static constexpr float shakeIntensity = 5.0f;		//�h��̋���
	static constexpr float shakeDuration = 10.0f;		//�h��̍ő厞��
	static constexpr float Distance = 5.0f;				//����

	float shakeTime;			//�h�ꎞ��
	bool isDamage;				//�_���[�W���󂯂Ă��邩
	bool isShake;				//�h��Ă��邩
	Input* rightInput;			//�E�X�e�B�b�N���
	VECTOR Offset;				//
	VECTOR OriginalOffset;		//
	VECTOR AngleVec;			//�����x�N�g��
	VECTOR	position;			// �|�W�V����.
	VECTOR targetposition;		//�@�J��������������|�W�V����
};