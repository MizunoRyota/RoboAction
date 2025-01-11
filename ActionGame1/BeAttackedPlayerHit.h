#pragma once

class BeAttackedPlayer
{
public:
	BeAttackedPlayer();
	~BeAttackedPlayer();
	void Update(const Player& player, const Enemy& enemy);
	bool CheckBeAttackHit(const Player& player, const Enemy& enemy);
	const bool& GetIsBeAttack() const { return IsBeAttack; }

private:
	static constexpr  float PlayerHight = 0.8f;		//�v���C���[�̍���
	bool IsBeAttack;

	//�v���C���[�̓����蔻��ϐ�
	VECTOR playerCircle;				//�v���C���[�̓����蔻��̃|�W�V����
	float playerRadius;					//�v���C���[�̓����蔻��̔��a

	//Enemy�̓����蔻��
	VECTOR enemyCircle;					//Enemy�̓����蔻��̃|�W�V����
	float enemyRadius;					//Enemy�̓����蔻��̔��a

	VECTOR keepDistance;				//������ێ�����ϐ�
	float Distance;						//����
	float Length;						//�v���C���[�̉~��Enemy�̉~�̔��a�̍��v
};

