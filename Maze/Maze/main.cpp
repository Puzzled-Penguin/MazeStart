/*
	GPF Week 6 - Maze Start Code
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>

#include "Framework.h"
using namespace std;

// Screen dimensions
int gScreenWidth{ 800 };
int gScreenHeight{ 600 };

// Delay to slow things down
int gTimeDelayMS{ 100 };

// Maze size as constants
constexpr int kMazeColumnsX{ 20 };
constexpr int kMazeRowsY{ 20 };

int playerX = 0;
int playerY = 0;
bool canMove = true;

char map[kMazeRowsY][kMazeColumnsX] = {
	// 20 columns (x axis) by 20 rows (y axis)
	// X0   X1   X2   X3   X4   X5   X6   X7   X8   X9   X10  X11  X12  X13  X14  X15  X16  X17  X18  X19 
	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y0
	{ 'W', '.', '.', '.', '.', 'W', '.', '.', '.', 'W', 'W', '.', '.', '.', '.', 'W', 'G', '.', '.', 'W' },	//Y1
	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W', '.', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W' },	//Y2
	{ 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W', '.', 'W', 'W', '.', 'W', '.', '.', '.', '.', 'W' },	//Y3
	{ 'W', '.', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', '.', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', 'W' },	//Y4
	{ 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', '.', '.', '.', 'W', '.', 'W', '.', '.', '.', '.', 'W' },	//Y5
	{ 'W', '.', 'W', '.', 'W', 'W', 'W', '.', '.', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', '.', '.', 'W' },	//Y6
	{ 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W' },	//Y7
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W', '.', '.', '.', 'W', '.', '.', '.', '.', 'W' },	//Y8
	{ 'W', '.', 'W', '.', 'W', '.', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', 'W', 'W', 'W', '.', 'W', 'W' },	//Y9
	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', '.', 'W', 'W', '.', 'W', 'W' },	//Y10
	{ 'W', '.', '.', '.', '.', 'W', '.', '.', '.', 'W', 'W', '.', '.', '.', '.', 'W', '.', '.', '.', 'W' },	//Y11
	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', '.', '.', '.', 'W', '.', 'W', 'W', 'W', 'W', '.', 'W' },	//Y12
	{ 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W', 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', 'W' },	//Y13
	{ 'W', '.', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W' },	//Y14
	{ 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', '.', 'W', '.', 'W', '.', 'W', '.', '.', '.', 'W', 'W' },	//Y15
	{ 'W', '.', 'W', '.', 'W', 'W', 'W', '.', '.', 'W', 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W' },	//Y16
	{ 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W', '.', '.', 'W', 'W', 'W', '.', 'W', 'W', '.', 'W' },	//Y17
	{ 'W', 'P', '.', '.', '.', '.', '.', '.', '.', 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y18
	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y19
};

void drawMaze()
{
	for (size_t CellY = 0; CellY < kMazeRowsY; CellY++) // Rows
	{
		for (size_t CellX = 0; CellX < kMazeColumnsX; CellX++) // Columns
		{
			switch (map[CellY][CellX])
			{
			case 'W':
				//Black Wall
				ChangeColour(0, 0, 0, 255);
				DrawRectangle(CellX * 40, CellY * 30, 40, 30);
				break;
			case '.':
				//White Empty
				ChangeColour(255, 255, 255, 255);
				DrawRectangle(CellX * 40, CellY * 30, 40, 30);
				break;
			case 'G':
				//Red Goal
				ChangeColour(255, 0, 0, 255);
				DrawRectangle(CellX * 40, CellY * 30, 40, 30);
				break;
			}
		}
	}
}

void drawPlayer()
{
	//Blue Player
	ChangeColour(0, 0, 255, 255);
	DrawRectangle(playerX * 40, playerY * 30, 40, 30);
}

void initializePlayer()
{
	for (size_t CellY = 0; CellY < kMazeRowsY; CellY++) // Rows
	{
		for (size_t CellX = 0; CellX < kMazeColumnsX; CellX++) // Columns
		{
			if (map[CellY][CellX] == 'P')
			{
				//Blue Player
				playerX = CellX;
				playerY = CellY;
				map[CellY][CellX] = '.';
				break;
			}
		}
	}
}

void canMoveThere(EKeyPressed keypressed)
{
	switch (keypressed)
	{
	case EKeyPressed::eNone:
		break;
	case EKeyPressed::eLeft:
		if (map[playerY][playerX - 1] == 'G') { cout << "Win" << endl; }
		if (map[playerY][playerX - 1] != '.' && map[playerY][playerX - 1] != 'G') { canMove = false; }
		break;
	case EKeyPressed::eUp:
		if (map[playerY - 1][playerX] == 'G') { cout << "Win" << endl; }
		if (map[playerY - 1][playerX] != '.' && map[playerY - 1][playerX] != 'G') { canMove = false; }
		break;
	case EKeyPressed::eRight:
		if (map[playerY][playerX + 1] == 'G') { cout << "Win" << endl; }
		if (map[playerY][playerX + 1] != '.' && map[playerY][playerX + 1] != 'G') { canMove = false; }
		break;
	case EKeyPressed::eDown:
		if (map[playerY + 1][playerX] == 'G') { cout << "Win" << endl; }
		if (map[playerY + 1][playerX] != '.' && map[playerY + 1][playerX] != 'G') { canMove = false; }
		break;
	default:
		break;
	}
}

void movement()
{
	EKeyPressed keypressed = GetLastKeyPressed();
	switch (keypressed)
	{
	case EKeyPressed::eNone:
		break;
	case EKeyPressed::eLeft:
		canMoveThere(keypressed);
		if (canMove) { playerX--; }
		break;
	case EKeyPressed::eUp:
		canMoveThere(keypressed);
		if (canMove) { playerY--; }
		break;
	case EKeyPressed::eRight:
		canMoveThere(keypressed);
		if (canMove) { playerX++; }
		break;
	case EKeyPressed::eDown:
		canMoveThere(keypressed);
		if (canMove) { playerY++; }
		break;
	default:
		break;
	}
}

int main()
{
	initializePlayer();
	while (UpdateFramework())
	{
		drawMaze();
		drawPlayer();
		movement();
		canMove = true;
	}
	return 0;
}
