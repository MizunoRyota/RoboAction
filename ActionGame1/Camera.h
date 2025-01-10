#pragma once

class Player;

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
	void ReadyUpdate(const VECTOR& playerpos);//�`���[�g���A�����
	void Update(const Player& playerpos);	// �X�V.
	void ShakeCamera(float intensity, float duration,const Player& player);
	void GameEnd(const VECTOR& planepos);//�Q�[���I�[�o�[��ʏ���

	// �|�W�V������getter/setter.
	const VECTOR& GetPosition() const { return position; }

	const VECTOR& GetTarget()	const { return targetposition; }
private:
	float Zoom;				//z���̃J�����|�W�V����
	float Hight;			//y���̃J�����|�W�V����
	float TargetHight;		//�^�[�Q�b�g�̌��鍂��
	// �h��̋����Ǝ�������
	static constexpr float shakeIntensity=5.0f;
	static constexpr float shakeDuration = 2.0f;
	float shakeTime;
	bool isDamage;
	VECTOR Offset;
	VECTOR OriginalOffset;
	VECTOR	position;			// �|�W�V����.
	VECTOR targetposition;		//�@�J��������������|�W�V����
};