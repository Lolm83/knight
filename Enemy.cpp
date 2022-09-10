namespace Tmpl8
{
	Sprite s_idle(new Surface("assets/_SkeletonIdle.png"), 11);
	Sprite s_idleL(new Surface("assets/_LSkeletonIdle.png"), 11);
	Sprite s_attack(new Surface("assets/_SkeletonAttack.png"), 18);
	Sprite s_attackL(new Surface("assets/_LSkeletonAttack.png"), 18);
	Sprite s_run(new Surface("assets/_SkeletonRun.png"), 13);
	Sprite s_runL(new Surface("assets/_LSkeletonRun.png"), 13);

	class Enemy
	{
	public:
		Enemy(int x = 500, int y = 200, Status status = IDLE, Direction direction = RIGHT)
		{
			m_x = x; m_dx = 5;
			m_y = y; m_acting = false; m_aFrame = 0;
			m_aTime = 0;
			m_status = status;
			m_direction = direction;
		}

		void Simulate(float dt, Hero* hero);
		void Animate(float dt, Surface* screen);
		void Action(float dt);


		Status m_status;
		Direction m_direction;
		bool m_acting;

		int m_x, m_y;
	private:
		Sprite animation[6] = { s_idle, s_idleL, s_attack, s_attackL, s_run, s_runL };
		float m_posx = 0, m_posy = 0;
		float m_dx;
		float m_aTime;
		int m_aFrame;
		int m_space = 20;



	};

	void Enemy::Action(float dt)
	{

	}

	void Enemy::Animate(float dt, Surface* screen)
	{
		float frame_count = 11;
		if (m_status == ATTACK || m_status == ATTACKL)
		{
			m_y -= 6;
			frame_count = 18;
			if (m_acting == false)
				m_aTime = 0;
		}
		else if (m_status == RUN || m_status == RUNL)
		{
			frame_count = 13;
		}

		if (m_aTime == 0)
			if (m_status == ATTACK)
				m_acting = true;

		m_aTime += (dt / 100);
		if (m_aTime >= frame_count) {
			m_aTime = 0;
			m_acting = false;
		}

		if (m_direction == RIGHT)
			m_aFrame = m_aTime;
		else
			m_aFrame = (frame_count - m_aTime) - 0.1f;

		if (m_direction == RIGHT) {
			animation[m_status].SetFrame(m_aFrame);
			animation[m_status].Draw(screen, m_x, m_y);
		}
		else if (m_direction == LEFT) {
			animation[m_status + 1].SetFrame(m_aFrame);
			if (m_status == ATTACK)
				animation[m_status + 1].Draw(screen, m_x - m_space, m_y);
			else
				animation[m_status + 1].Draw(screen, m_x, m_y);
		}

		if (m_status == ATTACK)
			m_y += 6;
	}

	void Enemy::Simulate(float dt, Hero* hero)
	{
		if (!m_acting)
		{
			if (hero->m_x <= m_x && hero->m_x >= m_x - 30) // Adjacent LEFT
				m_status = ATTACK;
			else if (hero->m_x >= m_x && hero->m_x <= m_x + 15) // Adjacent RIGHT
				m_status = ATTACK; 
			else if (hero->m_x <= m_x + 200 && hero->m_x > m_x) // Aggro Right
			{
				m_direction = RIGHT;
				m_status = RUN;
			}
			else if (hero->m_x >= m_x - 200 && hero->m_x < m_x) // Aggro Left
			{
				m_direction = LEFT;
				m_status = RUN;
			}
			else
				m_status = IDLE;

			if (m_status == RUN)
				if (m_direction == RIGHT)
					m_posx += (m_dx * dt) / 50;
				else if (m_direction == LEFT)
					m_posx -= (m_dx * dt) / 60;

			if (m_posx < 0)
				m_posx = 0;
			else if (m_posx > 750)
				m_posx = 750;
			m_x = m_posx;
		}
	}
};