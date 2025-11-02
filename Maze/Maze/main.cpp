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

int playerX;
int playerY;

/*
	2 Dimensional Arrays
	You can think of these as being an array of arrays
	
	The maze has kMazeColumnsX columns across (20 by default) represented by an array
	We then have kMazeRowsY (20) of these arrays, one for each row
	
	Columns and rows can be confusing so we tend to prefer working with x and y
	x is the horizontal axis (columns) across and y is the vertical axis (rows) down.

	Each single item is called a cell. 
	
	E.g. to output the value of the cell at 16 X (column 16) and 1 Y (row 1) we would write:
	cout << map[1][16] << endl; // outputs G
*/

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

void canMoveThere()
{
	EKeyPressed keypressed = GetLastKeyPressed();
	switch (keypressed)
	{
	case EKeyPressed::eNone:
		break;
	case EKeyPressed::eLeft:
		
		break;
	case EKeyPressed::eUp:
		if (map[playerY - 1][playerX])
		{

		}
		break;
	case EKeyPressed::eRight:
		
		break;
	case EKeyPressed::eDown:
		

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
		cout << "Left" << endl;
		playerX--;
		break;
	case EKeyPressed::eUp:
		cout << "Up" << endl;
		playerY--;
		break;
	case EKeyPressed::eRight:
		cout << "Right" << endl;
		playerX++;
		break;
	case EKeyPressed::eDown:
		cout << "Down" << endl;
		playerY++;
		break;
	default:
		break;
	}
}

int main()
{
	while (UpdateFramework())
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
				case 'P':
					//Blue Player
					int pPosX = CellX + playerX;
					int pPosY = CellY + playerY;
					ChangeColour(0, 0, 255, 255);
					DrawRectangle(pPosX * 40, pPosY * 30, 40, 30);
					break;
				}
			}
		}
		movement();
	}

	return 0;
}
