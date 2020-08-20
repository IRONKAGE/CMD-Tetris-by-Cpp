// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include <cstdlib>
#include <cstring>
#include <ctime>
#include "TestApp.h"
#include "Tetrominos.h"
#include "stdlib.h"    
#include "stdio.h"
#include "conio.h"

char blockFill = 9641, blockEmpty = ' ';
char borderFill = '#';

int score = 0;
int speed = 0;
int speedStep = 2;
int currentSeed = rand() % 7;

const int fieldPlay = 15, fieldFigure = 9, fieldFooter = 4;
int offset = 3;
char currentScore[fieldPlay + fieldFigure - 2];
char currentField[fieldPlay - 1][fieldPlay - 1];
const int _fieldPlay = fieldPlay - 1;

Tetrominos currentFigure;
Tetrominos incomingFigure;

bool first_iteration = true;
bool nextdraw = true;
bool endGame = false;

TestApp::TestApp() : Parent(fieldPlay + fieldFigure, fieldPlay + fieldFooter - 1)
{
	mObj1XOld = mObj1X = 7;
	mObj1YOld = mObj1Y = 2;
	mObj2X = 7;
	mObj2Y = 2;
}

// Заповнення тла
void fillBoard()
{
	for (int i = 0; i < fieldPlay - 1; i++)
		for (int j = 0; j < fieldPlay - 1; j++)
			currentField[i][j] = blockEmpty;
}

// Знищення лінії
int deleteLines()
{
	int counter;
	int i;
	for (i = 0; i < _fieldPlay; i++)
	{
		counter = 0;

		for (int j = 0; j < _fieldPlay; j++)
		{
			if (currentField[j][i] == blockFill)
				counter++;
		}

		if (counter == _fieldPlay - 1)
			break;
	}

	if (counter != _fieldPlay - 1)
		return 0;

	for (int j = i; j >= 0; j--)
	{
		for (int k = 0; k < _fieldPlay; k++)
		{
			currentField[k][j] = (j == 0) ? blockEmpty : currentField[k][j - 1];
		}
	}

	return deleteLines() + 1;
}

// Завершення гри
void stopGame() {
	endGame = true;
	exit(0);
}

// Керування фігурою
void TestApp::KeyPressed(int btnCode)
{
	int a = 97, A = 85, leftKey = 75;
	int s = 115, S = 83, downKey = 80;
	int d = 100, D = 68, rightKey = 77;
	int spaceKey = 32;

	if (btnCode == spaceKey)
		rotation = 1;
	else if ((btnCode == s) || (btnCode == S) || (btnCode == downKey))
		acceleration = 1;
	else if ((btnCode == a) || (btnCode == A) || (btnCode == leftKey))
		mObj1X--;
	else if ((btnCode == d) || (btnCode == D) || (btnCode == rightKey))
		mObj1X++;

	if (mObj1X < 0)
		mObj1X = 0;
	else if (mObj1X >= X_SIZE)
		mObj1X = X_SIZE - 1;

	if (mObj1Y < 0)
		mObj1Y = 0;
	else if (mObj1Y >=Y_SIZE)
		mObj1Y = Y_SIZE - 1;
}

// Створення комірки з фігурою
void generateSeedFigure(Tetrominos &figure, int seed)
{
	Tetrominos seedFig(seed);
	figure = seedFig;
}

// Створення фігури
void generateFigures()
{
	int incomeSeed = rand() % 7;
	srand(time(NULL));
	generateSeedFigure(currentFigure, currentSeed);
	generateSeedFigure(incomingFigure, incomeSeed);
	currentSeed = incomeSeed;
}

// Події на взаємодію з фігурою
void nextStep(int &CoordX, int &CoordY)
{
	for (int i = 0; i < currentFigure.GetX(); i++)
		for (int j = 0; j < currentFigure.GetY(); j++)
		{
			currentField[CoordX + i][CoordY + j] = (currentFigure.GetChar(i, j) == blockFill || currentField[CoordX + i][CoordY + j] == blockFill) ? blockFill : currentFigure.GetChar(i, j);
		}
	score += deleteLines();

	if (CoordY < currentFigure.GetY())
		stopGame();
	CoordX = 7;
	CoordY = 1;
	generateFigures();
	speedStep = 2;
	nextdraw = true;
}

void TestApp::UpdateF(float deltaTime)
{
	speed += speedStep;
	mObj1Y += speed / 50;
	if (speed >= 50)
		speed = 0;

	if (first_iteration)
	{
		fillBoard();
		generateFigures();
		first_iteration = 0;
	}
	if (rotation)
	{
		currentFigure.Rotate();
		rotation = 0;
	}
	if (acceleration)
	{
		speedStep = 10;
		acceleration = 0;
	}

	// Промальовка всього вікна
	for (int i = 0; i < fieldPlay + fieldFigure; i++)
	{
		for (int j = 0; j < fieldPlay + fieldFooter; j++)
		{
			if (i == 0 || i == fieldPlay - 1 && j < fieldPlay || j == 0 || j == fieldPlay - 1 || i == fieldPlay + fieldFigure - 1 || j == fieldPlay + fieldFooter - 1)
				SetChar(i, j, borderFill);
			else
				if (i >= fieldPlay || j >= fieldPlay)
					SetChar(i, j, blockEmpty);
				else SetChar(i, j, currentField[i][j]);
		}
	}
	
	// Розрахунок результату
	sprintf(currentScore, "Lines destroyed = %d", score);
	for (int i = 2; i < fieldPlay + fieldFigure; i++)
	{
		if (i < strlen(currentScore) + 2)
			SetChar(i, fieldPlay + 1, currentScore[i - 2]);
	}
	string author = "Create by IRONKAGE";

	// Промальовка ігрової фігури
	for (int i = 0; i < currentFigure.GetX(); i++)
	{
		for (int j = 0; j < currentFigure.GetY(); j++)
		{
			SetChar(mObj1XOld - 1, mObj1YOld - 1, blockEmpty);

			if (mObj1XOld - 1 == 0 || mObj1YOld - 1 == 0)
				SetChar(mObj1XOld - 1, mObj1YOld - 1, borderFill);

			SetChar(mObj1X + i, mObj1Y + j, currentFigure.GetChar(i, j));
			mObj1XOld = mObj1X;
			mObj1YOld = mObj1Y;
		}
	}

	// Промальовка попередньої фігури
	for (int i = 0; i < incomingFigure.GetX(); i++)
		for (int j = 0; j < incomingFigure.GetY(); j++)
			if (incomingFigure.GetChar(i, j) == blockFill)
				SetChar(fieldPlay + offset + i, offset + j, incomingFigure.GetChar(i, j));

	// Відслідковування граничних меж для фігури 
	for (int i = 0; i < currentFigure.GetX(); i++)
	{
		for (int j = 0; j < currentFigure.GetY(); j++)
		{
			// Умова для правої сторони
			if (mObj1X < 1)
				mObj1X++;
			else
				if (mObj1X > fieldPlay - 1 - currentFigure.GetX())
					mObj1X--;

			// Умова для нижньої сторони
			if (mObj1Y + currentFigure.GetY() >= fieldPlay - 1)
			{
				while (mObj1Y + currentFigure.GetY() >= fieldPlay)
					mObj1Y -= 2;
				nextStep(mObj1X, mObj1Y);
			}
			
			// Умови для накладання фігури
			if (j == currentFigure.GetY() - 1)
			{
				if (currentFigure.GetChar(i, j) == blockFill && currentField[mObj1X + i][mObj1Y + currentFigure.GetY()] == blockFill)
					nextStep(mObj1X, mObj1Y);
			}
			else
			{
				if (currentFigure.GetChar(i, j) == blockFill && currentField[mObj1X + i][mObj1Y + currentFigure.GetY() - 1] == blockFill)
					nextStep(mObj1X, mObj1Y);
			}
		}
	}
}