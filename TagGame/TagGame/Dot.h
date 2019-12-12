#pragma once
#include "LTexture.h"
#include "SDL.h"
#include <iostream>
#include "Vector2D.h"
class Dot
{

public:
	Dot();
	void update(double dt);
	void render(SDL_Renderer* renderer);
	void initTexture(SDL_Renderer* renderer, std::string string, bool t_isChaser);
	void setPosition(Vector2D t_pos);
	void move(Vector2D t_vec);
	bool checkCollision(Vector2D pos, int otherRadius);
	void moveUp(bool val);
	void moveDown(bool val);
	void moveLeft(bool val);
	void moveRight(bool val);
	Vector2D getPosition();
	SDL_Rect getRect();
	SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
	bool moved;
	void makeChaser()
	{
		isChaser = !isChaser;
		isChaser ? gDotTexture.setColor(255, 0, 0) : gDotTexture.setColor(0, 255, 0);
	}
	bool getIschaser() { return isChaser; };
	int getRadius() { return radius; };
	bool GetLocal() { return isLocalplayer; };
	std::string  GetPosAsString()
	{
		return std::string("X: " + std::to_string(m_position.getX()) + ", " + "Y: " + std::to_string(m_position.getY()));
	}
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
private:
	Vector2D m_position;
	SDL_Texture* m_texture = NULL;
	SDL_Rect m_rect;
	LTexture gDotTexture;
	bool isLocalplayer;
	bool isChaser;
	int radius = 50;
	const Uint8* state = SDL_GetKeyboardState(NULL);

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};