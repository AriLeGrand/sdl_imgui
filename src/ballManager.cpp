#include "ballManager.h";

void Ball::Init(std::vector<Ball>& ballArray, Ball ball) {
	//Ball initialisation
	randomValuesInit();
	ballArray.emplace_back(ball);
}

void Ball::SetVisibility()
{
	isVisible = false;
	return;
}

void Ball::Update(std::vector<Ball>& ballArray, SDL_Renderer* renderer)
{
	borderCollisions();
	collisions(ballArray);
	return;
}

void Ball::Delete(std::vector<Ball>& ballArray) 
{
	//Removing the ball from the array and free the memory
	ballArray[0].SetVisibility();
	ballArray.erase(ballArray.begin());
	ballArray.shrink_to_fit();
}
//Je sais c'est criminel

void Ball::Game(Uint32 timeElapsed, Uint32 startTicks, std::vector<Ball> ballArray, Ball ball, SDL_Renderer* renderer)
{
	if (timeElapsed >= 1000)
	{
		ball.Init(ballArray, ball);
		startTicks = SDL_GetTicks64();

	}
	if (ballArray.size() >= MAX_BALL_AMOUNT)
	{
		ball.Delete(ballArray);
	}

	for (int i = 0; i < ballArray.size(); i++)
	{
		ballArray[i].Update(ballArray, renderer);
	}
}


void Ball::randomValuesInit()
{
	Utilities utility;

	X = utility.Randomise(0,WINDOW_WIDTH);
	Y = utility.Randomise(0, WINDOW_HEIGHT);

	VelocityX = utility.Randomise(1,8);
	VelocityY = utility.Randomise(1,8);

	R = utility.Randomise(1, 255);
	G = utility.Randomise(1, 255);
	B = utility.Randomise(1, 255);

	Radius = utility.Randomise(10, 25);

	return;
}

int Ball::drawCircle(SDL_Renderer* renderer)
{

	for (int w = 0; w < Radius * 2; w++)
	{
		for (int h = 0; h < Radius * 2; h++)
		{

			int dx = Radius - w; // horizontal offset
			int dy = Radius - h; // vertical offset

			//Making sure the points are within boundaries
			if ((dx * dx + dy * dy) <= (Radius * Radius))
			{
				SDL_RenderDrawPoint(renderer, X + dx, Y + dy);
			}
		}
	}
	return 0;
}

void Ball::Display(SDL_Renderer* renderer)
{
	//Making the ball invisible when dispawn
	if (!isVisible) { return; }

	SDL_SetRenderDrawColor(renderer, R, G, B, 255);
	drawCircle(renderer);
}

int Ball::invertMovements()
{
	VelocityX *= -1;
	VelocityY *= -1;

	updateMovements();

	return 0;
}

void Ball::collisions(std::vector<Ball>& ballArray)
{
	//Comparing two balls from the array
	for (int i = 0; i < ballArray.size(); i++)
	{
		for (int k = i + 1; k < ballArray.size(); k++)
		{
			//Formula of the vector norm
			double distance = sqrt(pow(ballArray[k].X - ballArray[i].X, 2) +
				pow(ballArray[k].Y - ballArray[i].Y, 2));

			int radiusSum = ballArray[i].Radius + ballArray[k].Radius;

			if (distance <= radiusSum)
			{
				ballArray[i].invertMovements();
				ballArray[k].invertMovements();

			}
			if (distance < radiusSum)
			{
				correctOverlap(ballArray, distance, radiusSum, ballArray[i], ballArray[k]);
			}
		}


	}
	return;
}

int Ball::borderCollisions()
{
	if (X + Radius / 2 >= WINDOW_WIDTH ) {

		X = WINDOW_WIDTH - Radius / 2;
		VelocityX *= -1;

	}
	else if (X - Radius / 2 <= 0)
	{
		X = Radius / 2;
		VelocityX *= -1;
	}

	if (Y  + Radius / 2 >= WINDOW_HEIGHT) {

		Y = WINDOW_HEIGHT - Radius / 2;
		VelocityY *= -1;
	}
	else if (Y - Radius / 2<= 0 )
	{
		Y = Radius / 2;
		VelocityY *= -1;
	}

	updateMovements();

	return 0;
}

void Ball::correctOverlap(std::vector<Ball>& ballArray, double distance, double radiusSum, Ball& ball1, Ball& ball2)
{

	double overlap = radiusSum - distance;

	double dx = ball2.X - ball1.X;
	double dy = ball2.Y - ball1.Y;
	//Checking if the distance between the ball is 0 or not and calculating the factor
	double distanceFactor = distance == 0 ? 1 : (1.0 / distance);

	dx *= distanceFactor;
	dy *= distanceFactor;


	//Correcting the overlap
	ball1.X -= dx * (overlap / 2);
	ball1.Y -= dy * (overlap / 2);

	ball2.X += dx * (overlap / 2);
	ball2.Y += dy * (overlap / 2);
}

int Ball::updateMovements()
{

	X += VelocityX;
	Y += VelocityY;

	return 0;
}