namespace Tmpl8
{
	enum T_Type
	{
		EMPTY,
		PLATFORM,
		WALL,
		HAZARD
	};


	class Tile
	{
		
	public:
		Tile(int x = 0, int y = 0, int tx = 'j', int ty = 'a') :
			m_tx(tx), m_ty(ty)
		{
			m_x = x * m_size; m_y = y * m_size;
			T_TypeInit();
		}

		void Reassign(int x, int y, int tx, int ty)
		{
			if (x <= m_size * 25 && y <= m_size * 16)
				m_x = x, m_y = y;
			if (tx <= 'j' && ty <= 'f')
				m_tx = tx, m_ty = ty;
			T_TypeInit();
		}

		int m_size = 32;
		T_Type m_type;
		
		int m_x, m_y;

	private:
		void T_TypeInit();
		int m_tx, m_ty;

	};

	void Tile::T_TypeInit()
	{
		if (m_tx == 'j' && m_ty == 'e')
			m_type = HAZARD;  // Spikes
		else if (m_tx <= 'd' && m_ty == 'a')
			m_type = PLATFORM; // Stones
		else if (m_tx == 'h' && m_ty == 'e')
			m_type = PLATFORM; // Bridge
		else
			m_type = EMPTY;
	}

}