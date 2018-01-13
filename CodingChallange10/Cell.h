#pragma once

class Cell
{
private:
	float x, y, side;
	bool walls[4] { true, true, true, true };
	bool visited{ false };
public:
	Cell();
	Cell(int i, int j, float w);
	~Cell();
	void Draw();
	void Draw(unsigned char r, unsigned char g, unsigned char b);
	void Visit();
	void RemoveTop();
	void RemoveRight();
	void RemoveBottom();
	void RemoveLeft();
	bool IsVisited();
};

