#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>

#include "Hero.cpp"

namespace Tmpl8
{

	class Enemy
	{
	public:


	private:


	};

	void Game::Init()
	{
		
	}

	void Game::Shutdown()
	{

	}

	Hero player(33, 300, RUNL, LEFT);
	Sprite test(new Surface("assets/ball.png"),1);
	int last_input;
	void Game::Tick(float dt)
	{
		screen->Clear(0x000000);
		
		test.Draw(screen, 33, 33);
		test.Draw(screen, 333, 333);

		// Handling Inputs
		if (!player.m_acting)
		{
			if (GetAsyncKeyState(VK_LEFT))
				player.Input(RUN, LEFT); 

			else if (GetAsyncKeyState(VK_RIGHT))
				player.Input(RUN, RIGHT);

			else if (GetAsyncKeyState(VK_SPACE))
			{
				if (player.m_direction == RIGHT)
					player.Input(ATTACK, RIGHT);
				else
					player.Input(ATTACK, LEFT);
			}
			else if (player.m_direction == RIGHT)
				player.Input(IDLE, RIGHT);
			else
				player.Input(IDLE, LEFT);
			
		}
		player.Simulate(dt);
		player.Animate(dt, screen);
	
	}
};