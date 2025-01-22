#pragma once

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
	void GameTitle(const VECTOR& mappos);//�Q�[���^�C�g��
	void ReadyUpdate(const VECTOR& playerpos,const Enemy& enemy);//�`���[�g���A�����
	void Update(const Player& player,const Input& input, const Enemy& enemy);	// �X�V.
	void FixCameraPosition();
	void ShakeCamera(float intensity, float duration, const Player& player);
	void GameEnd(const VECTOR& planepos);//�Q�[���I�[�o�[��ʏ���

	// �|�W�V������getter/setter.
	const VECTOR& GetPosition() const { return position; }
	const VECTOR& GetTarget()	const { return targetposition; }
private:
	static constexpr float Zoom = -3.0f;				//z���̃J�����|�W�V����
	static constexpr float Hight = 1.5f;			//y���̃J�����|�W�V����
	static constexpr float TargetHight = 1.3;		//�^�[�Q�b�g�̌��鍂��
	static constexpr float AngleSpeed = 0.15f;
	float            angleVertical;           // �J�����̐����p�x
	float            angleHorizontal;         // �J�����̐����p�x

	// �h��̋����Ǝ�������
	static constexpr float shakeIntensity = 5.0f;
	static constexpr float shakeDuration = 2.0f;
	static constexpr float Distance = 5.0f;		//����

	float shakeTime;
	bool isDamage;
	Input* rightInput;
	VECTOR Offset;
	VECTOR OriginalOffset;
	VECTOR AngleVec;
	VECTOR	position;			// �|�W�V����.
	VECTOR targetposition;		//�@�J��������������|�W�V����
};