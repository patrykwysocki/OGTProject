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
	Vector2D getPosition();
	SDL_Rect getRect();
	SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
	bool moved;
	void makeChaser()
	{
		isChaser = !isChaser;
		isChaser ? gDotTexture.setColor(255, 0, 0) : gDotTexture.setColor(0, 255, 0);
	}
	bool GetLocal() { return isLocalplayer; };
	std::string  GetPosAsString()
	{
		return std::string("X: " + std::to_string(m_position.getX()) + ", " + "Y: " + std::to_string(m_position.getY()));
	}
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void handleInput();
private:
	Vector2D m_velocity;
	Vector2D m_position;
	float mSpeed = 0;
	SDL_Texture* m_texture = NULL;
	SDL_Rect m_rect;
	LTexture gDotTexture;
	bool isLocalplayer;
	bool isChaser;
	const Uint8* state = SDL_GetKeyboardState(NULL);
};