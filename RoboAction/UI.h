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
	int AHandle;				//Aボタンの画像
	int FalseAHandle;			//Aボタンを押していないときの画像
	int BHandle;				//
	int FalseBHandle;			//
	int XHandle;				//
	int FalseXHandle;			//
	int YHandle;				//
	int FalseYHandle;			//
	int WantedHandle;			//
	int PlayTitleHandle;		//ゲームを始めるを洗濯時の画像
	int HowToPlayTitleHandle;	//遊び方洗濯時の画像
	int TutorialHandle;			//チュートリアル画像
	bool ChosePlay;				//
	bool HowToPlay;				//
	int GameOverHandle;			//ゲームオーバー画像
	int GameClearHandle;		//ゲームクリア画像
	int LessonHandle;			//敵の倒し方の画像
};

