#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>


#include "Hero.cpp"
#include "Enemy.cpp"
#include "Level.cpp"

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
		if (!player.m_acting)
		{
			// Key Inputs LEFT
			if (GetAsyncKeyState(VK_LEFT))
			{
				if (GetAsyncKeyState(VK_SPACE))
					player.Input(ATTACK, LEFT);
				else 
					player.Input(RUN, LEFT);
			}
			// Key Inputs RIGHT
			else if (GetAsyncKeyState(VK_RIGHT))
			{
				if (GetAsyncKeyState(VK_SPACE))
					player.Input(ATTACK, RIGHT);
				else
					player.Input(RUN, RIGHT);
			}
			// Neutral ATTACK
			else if (GetAsyncKeyState(VK_SPACE))
			{
				if (player.m_direction == RIGHT)
					player.Input(ATTACK, RIGHT);
				else
					player.Input(ATTACK, LEFT);
			}
			// else, IDLE
			else if (player.m_direction == RIGHT)
				player.Input(IDLE, RIGHT);
			else
				player.Input(IDLE, LEFT);
		}
		

		level1.DrawLevel(screen);

		richard.Simulate(dt, &player);
	

		richard.Animate(dt, screen);


		player.Simulate(dt);
		player.Animate(dt, screen);
	}
};