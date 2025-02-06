#pragma once

class OnAttackedPlayer
{
public:
	OnAttackedPlayer();
	~OnAttackedPlayer();
	void Update(const Player& player, const Enemy& enemy);
	bool CheckBeAttackHit(const Player& player, const Enemy& enemy);
	const bool& GetisOnAttack() const { return isOnAttack; }

private:
	static constexpr  float PlayerHight = 0.3f;		//�v���C���[�̍���
	bool isOnAttack;

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

