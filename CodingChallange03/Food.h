#pragma once
class Food
{
private:
	int cs;
	float x, y, sz;
public:
	Food();
	Food(int chessSqrs);
	~Food();
	void Draw();
	void SetRandomPos();
	void GetPos(float &x, float &y);
};

