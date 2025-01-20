#pragma once

class UI
{
public:
	UI();
	~UI();
	void Load();
	void DrawGame(const Input& input);

private:
	int AHandle;
	int FalseAHandle;
	int BHandle;
	int FalseBHandle;
	int XHandle;
	int FalseXHandle;
	int YHandle;
	int FalseYHandle;
};

