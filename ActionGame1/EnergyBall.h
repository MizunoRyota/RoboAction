#pragma once

class Enemy;

class Energy
{
public:
	Energy();
	~Energy();
    void Load();								//������
    void BallSporn(const Enemy& enemy);         //�G�l���M�[�{�[���̐���
    void Update(const Enemy& enemy);			//�X�V
    void UpdateShadow();						//�e�̍X�V	
    void UpdateEffect();						//�G�t�F�N�g�̍X�V
    void DrawShadow();							//�e�̕`��  
    void Draw();								//�`��
    void UpdateExplosionEffect();				//�����G�t�F�N�g�̍X�V
private:
	static constexpr float EffektScale = 10.0f;		//�傫��
    VECTOR position;								//�|�W�V����.
    int EnergyBallHandle;							//�G�l���M�[�{�[�����f���n���h��
    int ExplosionHandle;							//�����G�t�F�N�g�n���h��
	bool isBallSporn;
	// ���Ԃ�����������(����I�ɃG�t�F�N�g���Đ����邽��)
	int time;
	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	int playingEffectHandle = -1;
    // �G�t�F�N�g�̉e
	VECTOR shadowBottompos;				//�e�̒��
	VECTOR shadowToppos;				//�e�̒��_
	float ShadowRad;					//�e�̔��a
};

