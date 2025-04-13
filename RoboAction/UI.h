#pragma once

class UI
{
public:
	UI();
	~UI();
	void Load();
	void Initialize();
	void UpdateTitle(Input& input);
	void UpdateGameOver();
	void DrawTitle();
	void DrawLesson();
	void DrawTutorial();
	void DrawGame(const Input& input);
	void DrawGameOver();
	void DrawGameClear();
	const bool& GetisIsChosePlay() const { return ChosePlay; }
	const bool& GetisIsHowToPlay() const { return HowToPlay; }

private:
	int AHandle;				//A�{�^���̉摜
	int FalseAHandle;			//A�{�^���������Ă��Ȃ��Ƃ��̉摜
	int BHandle;				//
	int FalseBHandle;			//
	int XHandle;				//
	int FalseXHandle;			//
	int YHandle;				//
	int FalseYHandle;			//
	int WantedHandle;			//
	int PlayTitleHandle;		//�Q�[�����n�߂����󎞂̉摜
	int HowToPlayTitleHandle;	//�V�ѕ����󎞂̉摜
	int TutorialHandle;			//�`���[�g���A���摜
	bool ChosePlay;				//
	bool HowToPlay;				//
	int GameOverHandle;			//�Q�[���I�[�o�[�摜
	int GameClearHandle;		//�Q�[���N���A�摜
	int LessonHandle;			//�G�̓|�����̉摜
};

