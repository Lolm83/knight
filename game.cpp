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

	Hero player(33, 33, RUNL, LEFT);

	void Game::Tick(float dt)
	{
		screen->Clear(0x000000);

		if (GetAsyncKeyState(VK_LEFT))
			player.Input(RUNL, LEFT);

		else if (GetAsyncKeyState(VK_RIGHT)) 
			player.Input(RUN, RIGHT);

		else if (GetAsyncKeyState(VK_SPACE))
		{
			if (player.m_direction == RIGHT)
				player.Input(ATTACK, RIGHT);
			else
				player.Input(ATTACKL, LEFT);
		}
		player.Simulate(dt);
		player.Animate(dt, screen);
	
	}
};