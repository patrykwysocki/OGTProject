#include "Dot.h"

Dot::Dot(bool chaser)
{
	isChaser = chaser;
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 20;
	mVelY = 20;


	isChaser ? gDotTexture.setColor(255, 0, 0) : gDotTexture.setColor(0, 255, 0);

	width = 100;
	height = 100;
}

Dot::~Dot()
{
	gDotTexture.free();
}

void Dot::SetPosition(int x, int y)
{
	mPosX = x;
	mPosY = y;

	mCenterX = mPosX + (width / 2);
	mCenterY = mPosY + (height / 2);
}

void Dot::makeChaser()
{
	isChaser = !isChaser;
	isChaser ? gDotTexture.setColor(255, 0, 0) : gDotTexture.setColor(0, 255, 0);
}

//"dot.bmp"
void Dot::Init(SDL_Renderer *gRenderer)
{
	gDotTexture.loadFromFile("Assets/circle.png", gRenderer);
	isChaser ? gDotTexture.setColor(255, 0, 0) : gDotTexture.setColor(0, 255, 0);
}

void Dot::handleEvent(SDL_Event& e)
{
	if (isChaser)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: mVelY -= DOT_VEL; break;
			case SDLK_s: mVelY += DOT_VEL; break;
			case SDLK_a: mVelX -= DOT_VEL; break;
			case SDLK_d: mVelX += DOT_VEL; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: mVelY += DOT_VEL; break;
			case SDLK_s: mVelY -= DOT_VEL; break;
			case SDLK_a: mVelX += DOT_VEL; break;
			case SDLK_d: mVelX -= DOT_VEL; break;
			}
		}
	}
	else if (!isChaser)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: mVelY -= DOT_VEL; break;
			case SDLK_DOWN: mVelY += DOT_VEL; break;
			case SDLK_LEFT: mVelX -= DOT_VEL; break;
			case SDLK_RIGHT: mVelX += DOT_VEL; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: mVelY += DOT_VEL; break;
			case SDLK_DOWN: mVelY -= DOT_VEL; break;
			case SDLK_LEFT: mVelX += DOT_VEL; break;
			case SDLK_RIGHT: mVelX -= DOT_VEL; break;
			}
		}
	}
}

void Dot::move(int SCREEN_HEIGHT, int SCREEN_WIDTH)
{
	//Move the dot left or right
	mPosX += mVelX;
	
	//If the dot went too far to the left or right
	if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH))
	{
		//Move back
		mPosX -= mVelX;
	}

	//Move the dot up or down
	mPosY += mVelY;

	//If the dot went too far up or down
	if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT))
	{
		//Move back
		mPosY -= mVelY;
	}
	std::cout << mPosX << " , " << mPosY << std::endl;
	mCenterX = mPosX + (width / 2);
	mCenterY = mPosY + (height / 2);
}

void Dot::render(SDL_Renderer *gRenderer)
{
	//Show the dot
	gDotTexture.render(mPosX, mPosY, gRenderer);
}

std::string Dot::GetPosAsString()
{
	return std::string("X: "+std::to_string(mPosX) + ", " + "Y: " + std::to_string(mPosY));
}

int Dot::GetCenterX()
{
	return mCenterX;
}

int Dot::GetCenterY()
{
	return mCenterY;
}

bool Dot::Checkcollision(int centerX, int centerY)
{
	int distance = sqrt(((mCenterX - centerX) * (mCenterX - centerX)) + ((mCenterY - centerY) * (mCenterY - centerY)));
	
	if (distance <= width)
	{
		return true;
	}
	else
	{
		return false;
	}
}