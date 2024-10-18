#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>


#include "constants.h"
#include "utilities.h"

class Ball
{
public:

	
	Ball() {  };
	void Init(std::vector<Ball>& ballArray, Ball ball);

	void SetVisibility();
	void Update(std::vector<Ball>& ballArray, SDL_Renderer* renderer);
	void Delete(std::vector<Ball>& ballArray);
	void Display(SDL_Renderer* renderer);

	void Game(Uint32 timeElapsed, Uint32 startTicks, 
		std::vector<Ball> ballArray, Ball ball, SDL_Renderer* renderer);
	~Ball() {  };

private:

	int X;
	int Y;
	int VelocityX;
	int VelocityY;
	int R, G, B;
	int Radius = 20;

	bool isVisible = true;


	void randomValuesInit();

	int drawCircle(SDL_Renderer* renderer);

	int invertMovements();
	void collisions(std::vector<Ball>& ballArray);

	int borderCollisions();

	void correctOverlap(std::vector<Ball>& ballArray, double distance, double radiusSum, Ball& ball1, Ball& ball2);

	int updateMovements();

};