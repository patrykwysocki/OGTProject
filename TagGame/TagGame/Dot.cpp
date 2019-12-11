//#include "Dot.h"
//
//Dot::Dot(bool chaser)
//{
//	isChaser = chaser;
//	//Initialize the offsets
//	mPosX = 0;
//	mPosY = 0;
//
//	//Initialize the velocity
//	mVelX = 20;
//	mVelY = 20;
//
//
//	isChaser ? gDotTexture.setColor(255, 0, 0) : gDotTexture.setColor(0, 255, 0);
//
//	width = 100;
//	height = 100;
//	m_position = Vector2D(500, 500);
//}
//
//Dot::~Dot()
//{
//	gDotTexture.free();
//}
//
//void Dot::SetPosition(int x, int y)
//{
//	mPosX = x;
//	mPosY = y;
//
//	mCenterX = mPosX + (width / 2);
//	mCenterY = mPosY + (height / 2);
//}
//
//void Dot::makeChaser()
//{
//	isChaser = !isChaser;
//	isChaser ? gDotTexture.setColor(255, 0, 0) : gDotTexture.setColor(0, 255, 0);
//}
//
////"dot.bmp"
//void Dot::Init(SDL_Renderer *gRenderer)
//{
//	gDotTexture.loadFromFile("Assets/circle.png", gRenderer);
//	isChaser ? gDotTexture.setColor(255, 0, 0) : gDotTexture.setColor(0, 255, 0);
//}
//
//void Dot::handleEvent(SDL_Event& e)
//{
//	if (isChaser)
//	{
//		//If a key was pressed
//		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
//		{
//			//Adjust the velocity
//			switch (e.key.keysym.sym)
//			{
//			case SDLK_w: mVelY -= DOT_VEL; break;
//			case SDLK_s: mVelY += DOT_VEL; break;
//			case SDLK_a: mVelX -= DOT_VEL; break;
//			case SDLK_d: mVelX += DOT_VEL; break;
//			}
//		}
//		//If a key was released
//		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
//		{
//			//Adjust the velocity
//			switch (e.key.keysym.sym)
//			{
//			case SDLK_w: mVelY += DOT_VEL; break;
//			case SDLK_s: mVelY -= DOT_VEL; break;
//			case SDLK_a: mVelX += DOT_VEL; break;
//			case SDLK_d: mVelX -= DOT_VEL; break;
//			}
//		}
//	}
//	else if (!isChaser)
//	{
//		//If a key was pressed
//		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
//		{
//			//Adjust the velocity
//			switch (e.key.keysym.sym)
//			{
//			case SDLK_UP: mVelY -= DOT_VEL; break;
//			case SDLK_DOWN: mVelY += DOT_VEL; break;
//			case SDLK_LEFT: mVelX -= DOT_VEL; break;
//			case SDLK_RIGHT: mVelX += DOT_VEL; break;
//			}
//		}
//		//If a key was released
//		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
//		{
//			//Adjust the velocity
//			switch (e.key.keysym.sym)
//			{
//			case SDLK_UP: mVelY += DOT_VEL; break;
//			case SDLK_DOWN: mVelY -= DOT_VEL; break;
//			case SDLK_LEFT: mVelX += DOT_VEL; break;
//			case SDLK_RIGHT: mVelX -= DOT_VEL; break;
//			}
//		}
//	}
//}
//
//void Dot::move(int SCREEN_HEIGHT, int SCREEN_WIDTH)
//{
//	//Move the dot left or right
//	mPosX += mVelX;
//	
//	//If the dot went too far to the left or right
//	if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
//	{
//		//Move back
//		mPosX -= mVelX;
//	}
//
//	//Move the dot up or down
//	mPosY += mVelY;
//
//	//If the dot went too far up or down
//	if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
//	{
//		//Move back
//		mPosY -= mVelY;
//	}
//	std::cout << mPosX << " , " << mPosY << std::endl;
//	mCenterX = mPosX + (width / 2);
//	mCenterY = mPosY + (height / 2);
//}
//
//void Dot::render(SDL_Renderer *gRenderer)
//{
//	//Show the dot
//	gDotTexture.render(mPosX, mPosY, gRenderer);
//}
//
//std::string Dot::GetPosAsString()
//{
//	return std::string("X: "+std::to_string(mPosX) + ", " + "Y: " + std::to_string(mPosY));
//}
//
//int Dot::GetCenterX()
//{
//	return mCenterX;
//}
//
//int Dot::GetCenterY()
//{
//	return mCenterY;
//}
//
//bool Dot::Checkcollision(int centerX, int centerY)
//{
//	int distance = sqrt(((mCenterX - centerX) * (mCenterX - centerX)) + ((mCenterY - centerY) * (mCenterY - centerY)));
//	
//	if (distance <= width)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
#include "Dot.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Dot::Dot()
{
	m_position = Vector2D(100.0f, 100.0f);
	m_rect.x = 100;
	m_rect.y = 100;
	m_rect.w = 50;
	m_rect.h = 50;
	mSpeed = 0.5f;
	isChaser ? gDotTexture.setColor(255, 0, 0) : gDotTexture.setColor(0, 255, 0);
}

void Dot::update(double dt)
{
	m_velocity *= dt;

	//std::cout << dt << std::endl;

	m_position += m_velocity;

	if ((m_position.getX() < 0) || (m_position.getX() + m_rect.w > SCREEN_WIDTH))
	{
		//Move back
		//m_position.getX() -= m_velocity.getX();
	}
	if ((m_position.getY() < 0) || (m_position.getY() + m_rect.h > SCREEN_HEIGHT))
	{
		//Move back
		//m_position.getY() -= m_velocity.getY();
	}
}

void Dot::render(SDL_Renderer* renderer)
{
	m_rect.x = (int)m_position.getX();
	m_rect.y = (int)m_position.getY();
	SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
}

void Dot::initTexture(SDL_Renderer* renderer, std::string string)
{
	m_texture = loadTexture(string, renderer);
}
void Dot::setPosition(Vector2D t_pos)
{
	m_position = t_pos;
}

Vector2D Dot::getPosition()
{
	return m_position;
}

SDL_Rect Dot::getRect()
{
	return m_rect;
}

SDL_Texture* Dot::loadTexture(std::string path, SDL_Renderer* renderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}