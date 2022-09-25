#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>

#include "Tile.cpp"
#include "Level.cpp"
#include "Hero.cpp"
#include "Enemy.cpp"


namespace Tmpl8
{

	void Game::Init()
	{
		
	}

	void Game::Shutdown()
	{

	}

	Enemy richard(32, 384);
	Hero player(320, 337, RUNL, LEFT);

	Level level1(&map1, &backdrop);

	int last_input;
	void Game::Tick(float dt)
	{
		screen->Clear(0x000000);

	// Handling Player Inputs

		// Controlled Jumping / Falling	
		if (player.m_status == JUMP || player.m_status == FALL)
		{
			if (GetAsyncKeyState(VK_LEFT))
				player.Input(STATUS, LEFT);
			else if (GetAsyncKeyState(VK_RIGHT))
				player.Input(STATUS, RIGHT);
			else 
				player.Input(STATUS, DEFAULT);
		}
		
		// Full Range of Actions (Not currently Acting)
		if (!player.m_acting)
		{
			// Key Inputs LEFT
			if (GetAsyncKeyState(VK_LEFT))
			{
				if (GetAsyncKeyState(VK_SPACE))
					player.Input(ATTACK, LEFT);
				else if (GetAsyncKeyState(VK_UP))
					player.Input(JUMP, LEFT);
				else 
					player.Input(RUN, LEFT);

				
			}
			// Key Inputs RIGHT
			else if (GetAsyncKeyState(VK_RIGHT))
			{
				if (GetAsyncKeyState(VK_SPACE))
					player.Input(ATTACK, RIGHT);
				else if (GetAsyncKeyState(VK_UP))
					player.Input(JUMP, RIGHT);
				else
					player.Input(RUN, RIGHT);
			}

			else if (GetAsyncKeyState(VK_UP))
					player.Input(JUMP, DEFAULT);

			else if (GetAsyncKeyState(VK_DOWN))
				player.Input(FALL, DEFAULT);

			// Neutral ATTACK
			else if (GetAsyncKeyState(VK_SPACE))
					player.Input(ATTACK, DEFAULT);
			// else, IDLE
			else 
				player.Input(IDLE, DEFAULT);
		}
		

		level1.DrawLevel(screen);

		richard.Simulate(dt, &player);
	

		richard.Animate(dt, screen);


		player.Simulate(dt, &level1);
		player.Animate(dt, screen);
	}
};