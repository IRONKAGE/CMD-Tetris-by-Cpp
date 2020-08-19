// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#include "TestApp.h"

TestApp::TestApp() : Parent(100, 80)
{
	mDirection = true;
	mObj1XOld = mObj1X = 10;
	mObj1YOld = mObj1Y = 10;
	mObj2X = 10;
	mObj2Y = 12;
}

void TestApp::KeyPressed(int btnCode)
{
	int w = 119, W = 87, upKey = 72;
	int s = 115, S = 83, downKey = 80;
	int a = 97, A = 85, leftKey = 75;
	int d = 100, D = 68, rightKey = 77;
	int spaceKey = 32;

	if (btnCode == spaceKey)
		return;
	else if ((btnCode == w) || (btnCode == W) || (btnCode == upKey))
		mObj1Y--;
	else if ((btnCode == s) || (btnCode == S) || (btnCode == downKey))
		mObj1Y++;
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

void TestApp::UpdateF(float deltaTime)
{
	SetChar(mObj1XOld, mObj1YOld, L' ');
	SetChar(mObj1X, mObj1Y, L'O');

	mObj1XOld = mObj1X;
	mObj1YOld = mObj1Y;

	//-----------------------------

	SetChar(mObj2X, mObj2Y, L' ');
	if (mDirection)
	{
		mObj2X++;
		if (mObj2X == 40)
			mDirection = false;
	}
	else
	{
		mObj2X--;
		if (mObj2X == 10)
			mDirection = true;
	}
	SetChar(mObj2X, mObj2Y, L'F');
}
