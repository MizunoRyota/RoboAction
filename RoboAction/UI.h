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
	void DrawTutorial();
	void DrawGame(const Input& input);
	void DrawGameOver();
	void DrawGameClear();
	const bool& GetisIsChosePlay() const { return ChosePlay; }
	const bool& GetisIsHowToPlay() const { return HowToPlay; }

private:
	int AHandle;
	int FalseAHandle;
	int BHandle;
	int FalseBHandle;
	int XHandle;
	int FalseXHandle;
	int YHandle;
	int FalseYHandle;
	int WantedHandle;
	int PlayTitleHandle;
	int HowToPlayTitleHandle;
	int TutorialHandle;
	bool ChosePlay;
	bool HowToPlay;
	int GameOverHandle;
	int GameClearHandle;
};

