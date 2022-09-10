namespace Tmpl8
{

	Surface tiles("assets/_Tileset.jpg");

	Sprite backdrop[4] = {
		Sprite(new Surface("assets/_CloudsBack.png") , 1),
		Sprite(new Surface("assets/_CloudsFront.png") , 1),
		Sprite(new Surface("assets/_BGBack.png") , 1),
		Sprite(new Surface("assets/_BGFront.png") , 1)
	};

	const char map1[16][75] = {
				 "ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja",
				 "ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja",
				 "ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja",
				 "ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja",
				 "ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja",
				 "ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja",
				 "ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja",
				 "ja ja ja ja ja ja aagbaicajja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja",
				 "ja ja ja ja ja ja ac bc cc ja gb ge hb ja ja ja ja ja ja ja ja ja ja ja ja",
				 "jaAjaBjaCjaDjaEcajja ja ja ja aagbaibaicajja ja ja ja ja ja ja ja ja ja ja",
				 "jaFjaGjaHjaIjaJcb ja ja ja ja ac bc bc cc ja ja ja ja ja ja ja ja ja ja ja",
				 "jaGjaGjaGjaGjaGcb ja aagcajja ja ja ja ja ja ja ja ja ja ja ja ja ja ja ja",
				 "jaGjaGjaGjaGjaGcb ja ac cc ja ja ff gf hf jb gd hd id jd jb ie ja ja ja ja",
				 "jaGjaGjaGjaGjaGha ca ja ja aa dagbaibahdaidajba bagbajdagbaibajheChe he he",
				 "jaGjaGjaGjaGjaGja cb je je ab db bb bb bb db bb dc bb bb bb dc caHja ja aa",
				 "jaGjaGjaGjaGjaGja eb da da ga bb bb dc bb bb bb bb db bb bb bb eb caBjaCab",
	};


	class Level
	{
	public:
		Level(const char(*map)[16][75], Sprite(*backdrop)[4])
		{
			m_height = 16; m_width = 25;
			m_t_height = 32; m_t_width = 32;
			m_map = map; m_backdrop = backdrop;
		}
		void DrawLevel(Surface* screen);

	private:
		int m_width, m_height;
		int m_t_width, m_t_height;

		Sprite(*m_backdrop)[4];
		const char(*m_map)[16][75];


	};


	void Level::DrawLevel(Surface* screen)
	{
		for (int i = 0; i <= 3; i++)
		{
			(*m_backdrop)[i].DrawScaled(0, 0, 800, 512, screen);
		}

		for (int y = 0; y < m_height; y++)
			for (int x = 0; x < m_width; x++)
			{
				int tx = (*m_map)[y][x * 3] - 'a';  // Thank you 3DGEP!
				int ty = (*m_map)[y][x * 3 + 1] - 'a';
				int flair = (*m_map)[y][x * 3 + 2]; // foreground and background decorative elements
												  // assigned per-tile
				Pixel* src = tiles.GetBuffer() + tx * 32 + (ty * 32) * 320;
				Pixel* dst = screen->GetBuffer() + x * 32 + y * 32 * 800;

				
				if (flair >= 'A' && flair <= 'O')
				{
					dst = screen->GetBuffer() + x * 32 + y * 32 * 800;
					for (int i = 0; i < 32; i++)
					{
						for (int j = 0; j < 32; j++)
						{
							// A = 0, B = 1, C = 2, D = 3, E = 4,
						   // F = 5, G = 6, H = 7, I - 8, J = 9,
						  // K = 10, L = 11, M = 12, N = 13, O = 14

						// Group D (ty = 3)
							if (flair == 'A')
							{
								int fx = flair - 'A';
								src = tiles.GetBuffer() + fx * 32 + (3 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'B')
							{
								int fx = flair - 'A';
								src = tiles.GetBuffer() + fx * 32 + (3 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'C')
							{
								int fx = flair - 'A';
								src = tiles.GetBuffer() + fx * 32 + (3 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'D')
							{
								int fx = flair - 'A';
								src = tiles.GetBuffer() + fx * 32 + (3 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'E')
							{
								int fx = flair - 'A';
								src = tiles.GetBuffer() + fx * 32 + (3 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}

						// Group E (ty = 4)
							else if (flair == 'F')
							{
								int fx = flair - 'F';
								src = tiles.GetBuffer() + fx * 32 + (4 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'G')
							{
								int fx = flair - 'F';
								src = tiles.GetBuffer() + fx * 32 + (4 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'H')
							{
								int fx = flair - 'F';
								src = tiles.GetBuffer() + fx * 32 + (4 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'I')
							{
								int fx = flair - 'F';
								src = tiles.GetBuffer() + fx * 32 + (4 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'J')
							{
								int fx = flair - 'F';
								src = tiles.GetBuffer() + fx * 32 + (4 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}

						// Group K (ty = 5)
							else if (flair == 'K')
							{
								int fx = flair - 'K';
								src = tiles.GetBuffer() + fx * 32 + (5 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'L')
							{
								int fx = flair - 'K';
								src = tiles.GetBuffer() + fx * 32 + (5 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'M')
							{
								int fx = flair - 'K';
								src = tiles.GetBuffer() + fx * 32 + (5 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'N')
							{
								int fx = flair - 'K';
								src = tiles.GetBuffer() + fx * 32 + (5 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'O')
							{
							int fx = flair - 'K';
							src = tiles.GetBuffer() + fx * 32 + (5 * 32) * 320 + (i * 320);
							if (src[j] >= 0x88000000)
								dst[j] = src[j];
							}


						}
						dst += 800;
					}
				}
					
				
					// Drawing the Main Tile
					dst = screen->GetBuffer() + x * 32 + y * 32 * 800;
					src = tiles.GetBuffer() + tx * 32 + (ty * 32) * 320;
					for (int i = 0; i < 32; i++)
					{
						for (int j = 0; j < 32; j++)
							if (src[j] >= 0x88000000)
								dst[j] = src[j];

						src += 320, dst += 800;
					}

				if (flair >= 'g' && flair <= 'j')
				{
					dst = screen->GetBuffer() + x * 32 + y * 32 * 800;
					for (int i = 0; i < 32; i++)
					{
						for (int j = 0; j < 32; j++)
						{
							// g = 7, h = 8, i = 9, j = 10
							if (flair == 'g')
							{
								int fx = flair - 'a';
								src = tiles.GetBuffer() + fx * 32 + (2 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'h')
							{
								int fx = flair - 'a';
								src = tiles.GetBuffer() + fx * 32 + (2 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'i')
							{
								int fx = flair - 'a';
								src = tiles.GetBuffer() + fx * 32 + (2 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
							else if (flair == 'j')
							{
								int fx = flair - 'a';
								src = tiles.GetBuffer() + fx * 32 + (2 * 32) * 320 + (i * 320);
								if (src[j] >= 0x88000000)
									dst[j] = src[j];
							}
						}
						dst += 800;
					}
				}


			}
	}
}

	





