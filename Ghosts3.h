#pragma once
#include <iostream>
#include"Ghosts1.h"
#include<cstdlib>
#include<ctime>
#include <SFML/Graphics.hpp>
using namespace sf;
class Ghosts3 : public Ghosts1
{
private:
	Sprite ghostSprite;
	Texture ghostTexture;
	int x;
	int y;
	int startX;
	int startY;
	float speed = 60.0f;
public:
	
	void setFrightened(bool value)override;
	Ghosts3(int startX, int startY);
	void moves(char layout[maximum_rows][maximum_cols],int pacX,int pacY, int gx1, int gy1, int gx2, int gy2, int gx3, int gy3) override;
	int getX() override;
	int getY() override;
	void reset() override;
	~Ghosts3();
	void draw(RenderWindow& window)override;
};