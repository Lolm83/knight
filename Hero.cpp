
namespace Tmpl8
{
	Sprite idle(new Surface("assets/_Idle.png"), 10);
	Sprite idleL(new Surface("assets/_IdleL.png"), 10);
	Sprite attack(new Surface("assets/_Attack2.png"), 6);
	Sprite attackL(new Surface("assets/_Attack2L.png"), 6);
	Sprite run(new Surface("assets/_Run.png"), 10);
	Sprite runL(new Surface("assets/_RunL.png"), 10);

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
		JUMPL
	};
	enum Direction
	{
		RIGHT,
		LEFT
	};

	class Hero
	{
	private:
		Sprite animation[6] = { idle, idleL, attack, attackL, run, runL };


	public:
		Hero(int x = 200, int y = 200, Status status = IDLE, Direction direction = RIGHT)
		{
			m_x = x; m_dx = 10;
			m_y = y; 
			m_aTime = 0;
			m_status = status;
			m_direction = direction;

		}
		void Input(Status status, Direction direction);
		void Simulate(float dt);
		void Animate(float dt, Surface* screen);
		void Action(float dt);
		

		Status m_status;
		Direction m_direction;
		bool m_acting;
		int m_x, m_y;

	private:
		
		int m_space = 40;
		float m_dx;
		float m_aTime;
		int m_aFrame;

		

		
	};

	void Hero::Input(Status status, Direction direction)
	{
		if (status != m_status && status <= RUNL)
		{
			m_status = status;
		}
		if (direction != m_direction && direction <= LEFT)
		{
			m_direction = direction;
		}
		

	}

	void Hero::Animate(float dt, Surface* screen)
	{
		float frame_count = 10;
		if (m_status == ATTACK || m_status == ATTACKL)
		{
			frame_count = 6;
			if (m_acting == false)
				m_aTime = 0;
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
			animation[m_status].Draw(screen, m_x - m_space, m_y);
		}
		else if (m_direction == LEFT) {
			animation[m_status + 1].SetFrame(m_aFrame);
			animation[m_status + 1].Draw(screen, m_x - m_space, m_y);
		}
	}

	void Hero::Simulate(float dt)
	{
		if (m_status == RUN)
			if (m_direction == RIGHT)
			m_x += (m_dx * dt) / 50;
		else if (m_direction == LEFT)
			m_x -= (m_dx * dt) / 75;
		
	}
};