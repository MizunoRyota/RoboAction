#include"Dxlib.h"
#include"Input.h"
#include"UI.h"

UI::UI()
	:AHandle(0)
 ,FalseAHandle(0)
 ,BHandle(0)
 ,FalseBHandle(0)
 ,XHandle(0)
 ,FalseXHandle(0)
 ,YHandle(0)
 ,FalseYHandle(0)
{
}

UI::~UI()
{
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
}

void UI::DrawGame(const Input& input)
{

	if (input.GetNowFrameInput() & PAD_INPUT_A)
	{
		DrawGraph(1400, 800, FalseAHandle, TRUE);
	}
	else
	{
		DrawGraph(1400, 800, AHandle, TRUE);
	}
	DrawGraph(1475, 725, BHandle, TRUE);
	if (input.GetNowFrameInput() & PAD_INPUT_C)
	{
		DrawGraph(1325, 725, FalseXHandle, TRUE);
	}
	else
	{
		DrawGraph(1325, 725, XHandle, TRUE);
	}
	DrawGraph(1400, 650, YHandle, TRUE);
}