
namespace Tmpl8
{
	Sprite idle(new Surface("assets/_Idle.png"), 10);
	Sprite idleL(new Surface("assets/_IdleL.png"), 10);
	
	Sprite attack(new Surface("assets/_Attack2.png"), 6);
	Sprite attackL(new Surface("assets/_Attack2L.png"), 6);
	
	Sprite run(new Surface("assets/_Run.png"), 10);
	Sprite runL(new Surface("assets/_RunL.png"), 10);
	
	Sprite jump(new Surface("assets/_Jump.png"), 3);
	Sprite jumpL(new Surface("assets/_JumpL.png"), 3);
	Sprite jumpfalltrasition(new Surface("assets/_JumpFallTransition.png"), 2);
	Sprite jumpfalltrasitionL(new Surface("assets/_JumpFallTransitionL.png"), 2);
	Sprite fall(new Surface("assets/_Fall.png"), 3);
	Sprite fallL(new Surface("assets/_FallL.png"), 3);


	// Status enum corresponds to animation in array
	enum Status
	{
		IDLE,
		IDLEL,
		ATTACK,
		ATTACKL,
		RUN,
		RUNL,
		JUMP,
		JUMPL,
		JUMP_TRANS,
		JUMP_TRANSL,
		FALL,
		FALLL,
		STATUS
	};
	enum Direction
	{
		RIGHT,
		LEFT,
		DEFAULT
	};

	class Hero
	{
	private:
		Sprite animation[12] = { idle, idleL, attack, attackL, run, runL, jump, jumpL, jumpfalltrasition, jumpfalltrasitionL, fall, fallL};


	public:
		Hero(int x = 200, int y = 200, Status status = IDLE, Direction direction = RIGHT)
		{
			m_x = x; m_dx = 10;
			m_y = y; m_dy = 8.5;
			m_aTime = 0;
			m_status = status;
			m_direction = direction;

		}
		void Input(Status status, Direction direction);
		void Simulate(float dt, Level* level);
		void Animate(float dt, Surface* screen);
		void Action(float dt);
		

		Status m_status;
		Direction m_direction;
		
		float m_x, m_y;

		// Lock out certain inputs while doing certaian actions
		bool m_acting;

		 // The Sprites come with a bit of empty space to the left and right of the character.
		// m_space variables are based on RIGHT facing sprite (invert for LEFT) 
		int m_spaceL = 49, m_spaceR = 58;

	private:
		
		int m_space = 40;
		float m_dx, m_dy;
		float m_aTime;
		int m_aFrame;



		float m_airtime = 0;
		bool m_freefall = true;
	};

	void Hero::Input(Status status, Direction direction)
	{
		if (status != m_status && status <= FALLL)
		{
			m_status = status;
		}
		
		if (direction != m_direction && direction <= LEFT)
		{
			m_direction = direction;
		}
		
		if (m_status == JUMP || m_status == FALL)
			if (direction == DEFAULT)
				m_freefall = true;
			else
				m_freefall = false;

	}

	void Hero::Animate(float dt, Surface* screen)
	{
		float frame_count = 10;
		if (m_status == ATTACK)
		{
			frame_count = 6;
			if (m_acting == false)
				m_aTime = 0;
		}
		else if (m_status == JUMP || m_status == FALL)
		{
			frame_count = 3;
		}
		else if (m_status == JUMP_TRANSL)
			frame_count = 2;

		if (m_aTime == 0)
			if (m_status == ATTACK)
				m_acting = true;
			
		m_aTime += (dt / 100);
		if (m_aTime >= frame_count) {
			m_aTime = 0;
			if (m_status == ATTACK)
				m_acting = false;
		}

		if (m_direction == RIGHT)
			m_aFrame = m_aTime;
		else
        m_aFrame = (frame_count - m_aTime) - 0.1f;

		if (m_direction == RIGHT) {
			animation[m_status].SetFrame(m_aFrame);
			animation[m_status].Draw(screen, m_x - m_space, m_y);
		}
		else if (m_direction == LEFT) {
			animation[m_status + 1].SetFrame(m_aFrame);
			animation[m_status + 1].Draw(screen, m_x - m_space, m_y);
		}
	}

	void Hero::Simulate(float dt, Level* level)
	{
		// Run Movement
		if (m_status == RUN)
			if (m_direction == RIGHT)
			m_x += (m_dx * dt) / 75;
		else if (m_direction == LEFT)
			m_x -= (m_dx * dt) / 75;

		// Walks off of a platform
		if (m_status != JUMP && m_status != FALL)
		{
			std::vector<Tile>::iterator iter;
			for (iter = level->level_tiles.begin(); iter != level->level_tiles.end(); iter++)
			{
				int offset = 40; 
				if ((*iter).m_type == PLATFORM)
				{
					if ((*iter).m_y <= (m_y + (animation[m_status].GetHeight() + 32)) && (*iter).m_y >= (m_y + (animation[m_status].GetHeight() - 4)))
					{
						bool falling = true;

						if (m_direction == LEFT)
						{
							if ((*iter).m_x <= (m_x + animation[m_status].GetWidth() - m_spaceL - offset) && ((*iter).m_x + (*iter).m_size) >= (m_x + m_spaceR) - offset)
								falling = false;
						}
						else if (m_direction == RIGHT)
						{
							if ((*iter).m_x <= (m_x + animation[m_status].GetWidth() - m_spaceR - offset) && ((*iter).m_x + (*iter).m_size) >= (m_x + m_spaceL) - offset)
								falling = false;
						}
						if (!falling)
							break;
					}
				}

				if (iter == level->level_tiles.end() - 1)
				{
					Input(FALL, DEFAULT);
					m_acting = true;
					m_airtime = 0;
				}
			}
		}
		
		// Jump simulation 
		else if (m_status == JUMP)
		{	
			m_acting = true;

			float a = -15.00f;
			m_airtime += (dt / 1000);
			// SUVAT s = ut + 0.5(at^2)
			m_y -= ((m_dy * m_airtime) + 0.5 * (a * m_airtime * m_airtime));

			// SUVAT v = u + at
			if ((m_dy + a * m_airtime) <= 0)
			{
				m_airtime = 0;
				m_status = FALL;
			}

			if (!m_freefall)
				if (m_direction == RIGHT)
					m_x += (m_dx * dt) / 100;
				else if (m_direction == LEFT)
					m_x -= (m_dx * dt) / 100;

		}

		// Falling Simulation
		else if (m_status == FALL)
		{
			float a = -12.f;
			m_airtime += (dt / 1050);
			// SUVAT s = ut + 0.5(at^2)
			m_y -=  0.5 * (a * m_airtime * m_airtime);

			// Landing Detection
			std::vector<Tile>::iterator iter;
			for (iter = level->level_tiles.begin(); iter != level->level_tiles.end(); iter++)
			{
				int offset = 40;
				if ((*iter).m_type == PLATFORM)
				{
					if ((*iter).m_y <= (m_y + (animation[FALL].GetHeight() + 2)) && (*iter).m_y >= (m_y + (animation[FALL].GetHeight() - 4)))
					{
						bool landed = false; 
						
						if (m_direction == LEFT)
						{
							if ((*iter).m_x <= (m_x + animation[m_status].GetWidth() - m_spaceL - offset) && ((*iter).m_x + (*iter).m_size) >= (m_x + m_spaceR) - offset)
								landed = true;
						}
						else if (m_direction == RIGHT)
						{
							if ((*iter).m_x <= (m_x + animation[m_status].GetWidth() - m_spaceR - offset) && ((*iter).m_x + (*iter).m_size) >= (m_x + m_spaceL) - offset)
								landed = true;
						}

						if (landed)
						{
							m_y = (*iter).m_y - (animation[FALL].GetHeight()) + 1;
							m_status = IDLE;
							m_acting = false;
							break;
						}						
					}
				}
			}	
			
			// Controlled falling
			if (!m_freefall)
				if (m_direction == RIGHT)
					m_x += (m_dx * dt) / 100;
				else if (m_direction == LEFT)
					m_x -= (m_dx * dt) / 100;
		}

		if (m_status == IDLE)
			m_airtime = 0;
	}
};