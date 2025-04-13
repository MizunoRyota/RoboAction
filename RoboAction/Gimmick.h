#pragma once
class Enemy;
class Gimmick
{
public:
	Gimmick(VECTOR Setposition);
	~Gimmick();
	void Load();						//�ǂݍ���
	void UpdateEffect(const Enemy& enemy);					//�G�t�F�N�g�̍X�V
	void Update(const Enemy& enemy);							//�X�V
	void UpdateMove(const Enemy& enemy);						//�X�V
	void UpdateMoveCircle(const Enemy& enemy);						//�X�V
	void DropTimer(const Enemy& enemy);
	void UpdateShadow();					//�e�̍X�V
	void Draw();						//�`��
	const VECTOR& GetPos() const { return position; }
	const bool& GetIsGimmickSporn() const { return isGimmickSporn; }
	void MoveOriginPosition(const Enemy& enemy);
	void MoveResetPosition(const Enemy& enemy);
	void ReturnGimmickPos(const Enemy& enemy);
	void UpdateAngle(const Enemy& enemy);
private:

	int GimmickHandle;
	static constexpr float EffektScale = 10.0f;		//�傫��
	static constexpr float returnRange = 0.0f;		//�傫��
	static constexpr float ModelScale = 0.0025f;	//�傫��
	// �~�^���̂��߂̒萔
	static constexpr float Radius = 7.0f; // �~�̔��a
	static constexpr float AngleSpeed = 0.025f; // �p���x
	VECTOR position;							    //�|�W�V����.
	VECTOR AngleVec;							    //�x�N�g��
	VECTOR Resetposition;							//���Z�b�g�|�W�V����
	float dropTime;                                 //
	float moveSpeed;                                //
	bool isLimitRange;								//
	bool isGimmickSporn;                            //
	float endDropTime;
	bool isOrigin;
	float moveTime;
	bool decreaseEnemyHp;
	// ���Ԃ�����������(����I�ɃG�t�F�N�g���Đ����邽��)
	int time;
	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	int playingEffectHandle = -1;
	// �G�t�F�N�g�̉e
	VECTOR shadowBottompos;				//�e�̒��
	VECTOR shadowToppos;				//�e�̒��_
	float ShadowRad;					//�e�̔��a
	int GimmickModelHandle;
	VECTOR modelPosition;
	bool returnEnemyPos;
	float angle;
};