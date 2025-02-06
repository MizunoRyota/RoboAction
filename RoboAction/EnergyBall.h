#pragma once

class Enemy;
class Player;
class OnAttackedEnemy;
class Energy
{
public:
	Energy();
	~Energy();
    void Load();							//������
    void BallSporn(const Enemy& enemy);     //�G�l���M�[�{�[���̐���
    void DropTimer(const Enemy& enemy);     //
	void LimitRange();						//�͈͐���
	void Update(const Enemy& enemy, const Player& player, const OnAttackedEnemy& onAttacked);		//�X�V
	void BlowAway(const Player& player, const OnAttackedEnemy& onAttacked);		//������΂�
	void ChangeBlowAway(const Player& player, const OnAttackedEnemy& onAttacked);	//�{�[��������������
    void UpdateShadow();					//�e�̍X�V	
    void UpdateEffect();					//�G�t�F�N�g�̍X�V
    void DrawShadow();						//�e�̕`��  
    void Draw();							//�`��
    void UpdateExplosionEffect();			//�����G�t�F�N�g�̍X�V
	// ���f���n���h���̎擾.
	const VECTOR& GetPos() const { return position; }
	const bool& GetisLimitRange() const { return isLimitRange; }
	const bool& GetisIsBlowAway() const { return isBlowAway; }
private:
	static constexpr float EffektScale = 10.0f;		//�傫��
    VECTOR position;							    //�|�W�V����.
	VECTOR AngleVec;							    //�x�N�g��
    int EnergyBallHandle;							//�G�l���M�[�{�[�����f���n���h��
    int ExplosionHandle;						    //�����G�t�F�N�g�n���h��
    float dropTime;                                 //
	float moveSpeed;                                //
	bool isBallSporn;                               //
	bool isDrop;								    //
	bool isBlowAway;						        //
	bool isLimitRange;								//
	float limitRange;								//
	// ���Ԃ�����������(����I�ɃG�t�F�N�g���Đ����邽��)
	int time;
	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	int playingEffectHandle = -1;

    // �G�t�F�N�g�̉e
	VECTOR shadowBottompos;				//�e�̒��
	VECTOR shadowToppos;				//�e�̒��_
	float ShadowRad;					//�e�̔��a
};