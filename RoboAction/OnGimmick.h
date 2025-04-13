#pragma once
class Player;
class Gimmick;

class OnGimmick
{
public:
	OnGimmick();
	~OnGimmick();
	void Update(const Player& player, const Gimmick& gimmick);		// �X�V
	bool CheckHit(const Player& player, const Gimmick& gimmick);	//�����蔻��`�F�b�N
	void DrawCircle();
	const bool& GetisOnGimmick() const { return isOnGimmick; }

private:
	static constexpr  float PlayerHight = 0.8f;		//�v���C���[�̍���
	static constexpr  float playerRadius = 1.0f;		//�v���C���[�̓����蔻��̔��a
	static constexpr  float gimmickRadius = 1.0f;		//Enemy�̓����蔻��̔��a

	bool isHit;
	bool isOnGimmick;
	//�v���C���[�̓����蔻��ϐ�
	VECTOR playerCircle;				//�v���C���[�̓����蔻��̃|�W�V����

	//Enemy�̓����蔻��
	VECTOR enemyCircle;					//Enemy�̓����蔻��̃|�W�V����

	VECTOR keepDistance;				//������ێ�����ϐ�
	float Distance;						//����
	float Length;						//�v���C���[�̉~��Enemy�̉~�̔��a�̍��v

};