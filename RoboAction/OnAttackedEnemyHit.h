#pragma once

class Energy;
class Player;
class Enemy;

class OnAttackedEnemy
{
public:
	OnAttackedEnemy();
	~OnAttackedEnemy();
	void Update(const Energy& ball, const Enemy& enemy, const Player& player);
	bool CheckOnAttackHit(const Energy& ball, const Enemy& enemy);
	bool CheckOnBallHit(const Player& player,const Energy& ball);
	const bool& GetisOnAttack() const { return isOnAttack; }
	const bool& GetisBallHit() const { return isBallHit; }
	const VECTOR& GetAttackAngle() const { return attackAngle; }
	void Draw();
private:

	static constexpr  float PlayerHight = 0.3f;		//�v���C���[�̍���
	static constexpr  float EnemyHight = 3.5f;		//�v���C���[�̍���


	VECTOR AngleVec;
	bool isOnAttack;

	//�G�l���M�[�{�[���̓����蔻��ϐ�
	VECTOR energyCircle;				//�v���C���[�̓����蔻��̃|�W�V����
	float  energyRadius;				//�v���C���[�̓����蔻��̔��a
	float energyHight;					//�v���C���[�̍���
	//Enemy�̓����蔻��
	VECTOR enemyCircle;					//Enemy�̓����蔻��̃|�W�V����
	float enemyRadius;					//Enemy�̓����蔻��̔��a

	//�v���C���[�̍U���͈�
	VECTOR PlayerAttackPosition;			//�v���C���[�̓����蔻��̃|�W�V����
	float  playerAttackRadius;				//�v���C���[�̓����蔻��̔��a
	VECTOR attackAngle;
	float attackDistance;
	VECTOR keepBallAttackDistance;
	float ballAttackDistance;
	float attackBallLength;
	bool isBallHit;

	float Distance;						//����
	VECTOR keepDistance;				//������ێ�����ϐ�
	float Length;						//�v���C���[�̉~��Enemy�̉~�̔��a�̍��v
};

