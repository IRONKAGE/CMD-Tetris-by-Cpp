#pragma once
#include <iostream>
#include "TestApp.h"

using namespace std;

class Tetrominos
{
	private:
		int SizeX;
		int SizeY;
		char ** m_figure;
		char blockFill = 9641, blockEmpty = ' ';

	public:
		Tetrominos()
		{
			SizeX = 4;
			SizeY = 4;
			m_figure = (char **)malloc(SizeX * sizeof(char *));
			for (int i = 0; i < SizeX; ++i)
			{
				m_figure[i] = (char *)malloc(SizeY * sizeof(char));
			}
			for (int i = 0; i < SizeX; i++)
				for (int j = 0; j < SizeY; j++)
					m_figure[i][j] = blockFill;
		};

	Tetrominos(int currentFigure)
	{
		switch (currentFigure)
		{
			// T - tetracube
			case 0:
			{
				SizeX = 2;
				SizeY = 3;
				m_figure = (char **)malloc(SizeX * sizeof(char *));

				for (int i = 0; i < SizeX; ++i)
				{
					m_figure[i] = (char *)malloc(SizeY * sizeof(char));
				}

				for (int i = 0; i < SizeX; i++)
					for (int j = 0; j < SizeY; j++)
					{
						if (i == 1 || j == 1)
							m_figure[i][j] = blockFill;
						else
							m_figure[i][j] = blockEmpty;
					}

				break;

			}

			// L - tetracube
			case 1:
			{
				SizeX = 2;
				SizeY = 3;
				m_figure = (char **)malloc(SizeX * sizeof(char *));

				for (int i = 0; i < SizeX; ++i)
				{
					m_figure[i] = (char *)malloc(SizeY * sizeof(char));
				}

				for (int i = 0; i < SizeX; i++)
					for (int j = 0; j < SizeY; j++)
					{
						if (i == 0 || j == 2)
							m_figure[i][j] = blockFill;
						else
							m_figure[i][j] = blockEmpty;
					}

				break;
			}

			// J - tetracube
			case 2:
			{
				SizeX = 2;
				SizeY = 3;
				m_figure = (char **)malloc(SizeX * sizeof(char *));

				for (int i = 0; i < SizeX; ++i)
				{
					m_figure[i] = (char *)malloc(SizeY * sizeof(char));
				}

				for (int i = 0; i < SizeX; i++)
					for (int j = 0; j < SizeY; j++)
					{
						if (i == 1 || j == 2)
							m_figure[i][j] = blockFill;
						else
							m_figure[i][j] = blockEmpty;
					}

				break;
			}

			// S - skew tetracube
			case 3:
			{
				SizeX = 2;
				SizeY = 3;
				m_figure = (char **)malloc(SizeX * sizeof(char *));

				for (int i = 0; i < SizeX; ++i)
				{
					m_figure[i] = (char *)malloc(SizeY * sizeof(char));
				}

				for (int i = 0; i < SizeX; i++)
					for (int j = 0; j < SizeY; j++)
					{
						if (i == 0 && j == 2 || i == 1 && j == 0)
							m_figure[i][j] = blockEmpty;
						else
							m_figure[i][j] = blockFill;
					}

				break;
			}

			// Z - skew tetracube
			case 4:
			{
				SizeX = 2;
				SizeY = 3;
				m_figure = (char **)malloc(SizeX * sizeof(char *));

				for (int i = 0; i < SizeX; ++i) {
					m_figure[i] = (char *)malloc(SizeY * sizeof(char));
				}

				for (int i = 0; i < SizeX; i++)
					for (int j = 0; j < SizeY; j++)
					{
						if (i == 0 && j == 0 || i == 1 && j == 2)
							m_figure[i][j] = blockEmpty;
						else
							m_figure[i][j] = blockFill;
					}

				break;
			}

			// I - straight tetracube
			case 5:
			{
				SizeX = 4;
				SizeY = 1;
				m_figure = (char **)malloc(SizeX * sizeof(char *));

				for (int i = 0; i < SizeX; ++i)
				{
					m_figure[i] = (char *)malloc(SizeY * sizeof(char));
				}

				for (int i = 0; i < SizeX; i++)
					for (int j = 0; j < SizeY; j++)
						m_figure[i][j] = blockFill;

				break;
			}

			// O - square tetracube
			case 6:
			{
				SizeX = 2;
				SizeY = 2;
				m_figure = (char **)malloc(SizeX * sizeof(char *));
				for (int i = 0; i < SizeX; ++i)
				{
					m_figure[i] = (char *)malloc(SizeY * sizeof(char));
				}

				for (int i = 0; i < SizeX; i++)
					for (int j = 0; j < SizeY; j++)
					{
						m_figure[i][j] = blockFill;
					}

				break;
			}

			default:
			{
				cout << "Invalid constructing figure" << endl;
				break;
			}
		}
	}

	~Tetrominos()
	{
		for (int i = 0; i < SizeX; ++i)
		{
			free(m_figure[i]);
		}
		free(m_figure);
	}

	void Rotate()
	{
		char ** m_figureloc = (char **)malloc(SizeY * sizeof(char *));

		for (int i = 0; i < SizeY; ++i)
		{
			m_figureloc[i] = (char *)malloc(SizeX * sizeof(char));
		}

		for (int i = 0; i < SizeX; i++)
			for (int j = 0; j < SizeY; j++)
			{
				m_figureloc[j][SizeX - i - 1] = m_figure[i][j];
			}

		for (int i = 0; i < SizeX; ++i)
		{
			free(m_figure[i]);
		}
		free(m_figure);

		m_figure = (char * *)malloc(SizeY * sizeof(char *));
		for (int i = 0; i < SizeY; ++i)
		{
			m_figure[i] = (char *)realloc(m_figureloc[i], SizeX * sizeof(char));
		}

		free(m_figureloc);
		int tmp = SizeX;
		SizeX = SizeY;
		SizeY = tmp;
	}

	int GetX()const
	{
		return SizeX;
	}

	int GetY()const
	{
		return SizeY;
	}

	char GetChar(int x, int y) const
	{
		if (x >= SizeX)
			return 0;
		return  m_figure[x][y];
	}

	void SetChar(int x, int y, char c)
	{
		m_figure[x][y] = c;
	}

	void SetSizeX(int x)
	{
		this->SizeX = x;
	}

	void SetSizeY(int y)
	{
		this->SizeY = y;
	}

	Tetrominos& operator=(const Tetrominos &f)
	{
		if (this == &f)
			return *this;

		for (int i = 0; i < SizeX; ++i)
		{
			free(m_figure[i]);
		}
		free(m_figure);

		SetSizeX(f.GetX());
		SetSizeY(f.GetY());

		m_figure = (char **)malloc(SizeX * sizeof(char *));
		for (int i = 0; i < SizeX; ++i)
		{
			this->m_figure[i] = (char *)malloc(SizeY * sizeof(char));
		}

		for (int i = 0; i < SizeX; i++)
			for (int j = 0; j < SizeY; j++)
				this->m_figure[i][j] = f.GetChar(i, j);
		return *this;
	}
};