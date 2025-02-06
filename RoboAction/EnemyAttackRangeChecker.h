#pragma once

class EnemyAttackRangeChecker : public HitChecker
{
public:
	EnemyAttackRangeChecker();
	virtual~EnemyAttackRangeChecker();

	void Update(const Player& player, const Enemy& enemy)override;	// �X�V
	bool CheckShortHit(const Player& player, const Enemy& enemy);
	bool CheckMiddleHit(const Player& player, const Enemy& enemy);
	bool CheckLongHit(const Player& player, const Enemy& enemy);

	void DrawCircle()override;
	// �͈͓��ɓ����Ă��邩�̎擾.
	const bool& GetisShortWithin() const { return isShortWithin; }
	const bool& GetisMiddleWithin() const { return isMiddleWithin; }
	const bool& GetisLongWithin() const { return isLongWithin; }

private:
	bool isShortWithin;				//�ߋ�������
	bool isMiddleWithin;			//����������
	bool isLongWithin;				//����������
	float AttackShrotRange;			//�ߋ����͈�
	float AttackMiddleRange;		//�������͈�
	float AttackLongRange;			//�������͈�
	float LengthRange;				//�~�Ɖ~�̋���
	VECTOR keepDistance;			//������ێ�����ϐ�
	float Distance;					//����
	float Length;					//�v���C���[�̉~��Enemy�̉~�̔��a�̍��v
};