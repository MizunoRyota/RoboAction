#include"Dxlib.h"
#include"Pallet.h"
#include"Input.h"
#include"UI.h"

UI::UI()
	:AHandle(0)
	, FalseAHandle(0)
	, BHandle(0)
	, FalseBHandle(0)
	, XHandle(0)
	, FalseXHandle(0)
	, YHandle(0)
	, FalseYHandle(0)
	, WantedHandle(0)
	, PlayTitleHandle(0)
	, HowToPlayTitleHandle(0)
	, HowToPlay(false)
	, ChosePlay(true)
	, GameOverHandle(0)
{
}

UI::~UI()
{
}

void UI::Initialize()
{
	ChosePlay = true;
	HowToPlay = false;
}

void UI::Load()
{
	AHandle = LoadGraph("data/Ui/A.png");
	FalseAHandle = LoadGraph("data/Ui/FalseA.png");
	BHandle = LoadGraph("data/Ui/B.png");
	FalseBHandle = LoadGraph("data/Ui/FalseB.png");
	XHandle = LoadGraph("data/Ui/X.png");
	FalseXHandle = LoadGraph("data/Ui/FalseX.png");
	YHandle = LoadGraph("data/Ui/Y.png");
	FalseYHandle = LoadGraph("data/Ui/FalseY.png");
	PlayTitleHandle = LoadGraph("data/Ui/Texture/PlayTitle2.png");
	HowToPlayTitleHandle = LoadGraph("data/Ui/Texture/HowToPlayTitle2.png");
	GameOverHandle = LoadGraph("data/Ui/Texture/GameOver2.png");
	TutorialHandle = LoadGraph("data/Ui/Texture/Tutorial2.png");
	GameClearHandle = LoadGraph("data/Ui/Texture/GameClear2.png");
}

void UI::UpdateTitle(Input& input)
{

	if (input.GetNowFrameInput() & PAD_INPUT_RIGHT)
	{
		HowToPlay = true;
		ChosePlay = false;
	}
	else if (input.GetNowFrameInput() & PAD_INPUT_LEFT)
	{
		HowToPlay = false;
		ChosePlay = true;
	}

}

void UI::DrawTitle()
{
	if (ChosePlay)
	{
		DrawGraph(0, 0, PlayTitleHandle, true);
	}
	else if (HowToPlay)
	{
		DrawGraph(0, 0, HowToPlayTitleHandle, true);
	}
}

void UI::DrawGame(const Input& input)
{

	//if (input.GetNowFrameInput() & PAD_INPUT_C)
	//{
	//	DrawGraph(1000, 800, FalseXHandle, TRUE);
	//}
	//else
	//{
	//	DrawGraph(1000, 800, XHandle, TRUE);
	//}
	//SetFontSize(40);
	//DrawFormatString(1200, 825, Pallet::AliceBlue.GetHandle(),"ATTACK");
	//DrawGraph(1475, 725, BHandle, TRUE);
	//if (input.GetNowFrameInput() & PAD_INPUT_A)
	//{
	//	DrawGraph(1325, 725, FalseAHandle, TRUE);
	//}
	//else
	//{
	//	DrawGraph(1325, 725, AHandle, TRUE);
	//}
	//DrawGraph(1400, 650, YHandle, TRUE);
}



void UI::DrawGameOver()
{
	DrawGraph(0, 0, GameOverHandle, true);
}

void UI::DrawTutorial()
{
	DrawGraph(0, 0, TutorialHandle, true);
}	

void UI::DrawGameClear()
{
	DrawGraph(0, 0, GameClearHandle, true);
}