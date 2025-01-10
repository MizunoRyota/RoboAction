#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Stage.h"

Stage::Stage()
    :position(VGet(0, 0, -20))
	, effectPosition ( VGet(0, 0, 0))
	,effectHandle(0)
    , StageHandle(-1)
	,time(0)
{
    //�����Ȃ�
}

Stage::~Stage()
{
	// �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
	DeleteEffekseerEffect(effectHandle);
}

void Stage::Load()
{
    StageHandle = MV1LoadModel("data/model/stage/NewStage.mv1");
	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	effectHandle = LoadEffekseerEffect("data/effekseer/EfkFile/GroundFire.efkefc",4.5f);
	
	SetScalePlayingEffekseer3DEffect(effectHandle, EffektScale, EffektScale,EffektScale);
    // 3D���f���̃X�P�[������
    MV1SetScale(StageHandle, VGet(Scale, Scale, Scale));
    // �R�c���f����Y���̉�]�l�𐳖ʂɃZ�b�g����
    MV1SetRotationXYZ(StageHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));
    // �X�e�[�̃��f���̍��W���X�V����
    MV1SetPosition(StageHandle, position);
}

void Stage::Update()
{
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();

	// ����I�ɃG�t�F�N�g���Đ�����
	if (time % 60 == 0)
	{
		StopEffekseer3DEffect(playingEffectHandle);
		// �G�t�F�N�g���Đ�����B
		playingEffectHandle = PlayEffekseer3DEffect(effectHandle);
	}

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();

	// ���Ԃ��o�߂�����B
	time++;
}

void Stage::Draw()
{
    MV1DrawModel(StageHandle);
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
}