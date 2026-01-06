/*
	GPF Week 6 - Maze Start Code
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string>

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

char map[kMazeRowsY][kMazeColumnsX] = { {'W'} };

void setMazeMap()
{
	ifstream MazeMap("MazeMap.txt");

	if (!MazeMap.is_open())
	{
		cout << "MazeMap.txt Not Found!" << endl;
		return;
	}

	string line;
	int y = 0;

	while (y < kMazeRowsY && getline(MazeMap, line))
	{
		for (int x = 0; x < kMazeColumnsX; x++)
		{
			if (x < (int)line.size())
				map[y][x] = line[x];
		}
		y++;
	}
	
}

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

void saveHighScore()
{
	ofstream HighScore("Highscore.txt");
	HighScore << GetElapsedTime();
}

void gameWon()
{
	cout << "Win" << endl;
	saveHighScore();
	StartClock();

	for (size_t CellY = 0; CellY < kMazeRowsY; CellY++) // Rows
	{
		for (size_t CellX = 0; CellX < kMazeColumnsX; CellX++) // Columns
		{
			if (map[CellY][CellX] == 'G')
			{
				map[CellY][CellX] = '.';
			}
		}
	}
	// Loop through empty spaces
	int emptySpaces = 0;
	for (size_t CellY = 0; CellY < kMazeRowsY; CellY++) // Rows
	{
		for (size_t CellX = 0; CellX < kMazeColumnsX; CellX++) // Columns
		{
			if (map[CellY][CellX] == '.' && !(CellY == playerY && CellX == playerX))
			{
				emptySpaces++;
			}
		}
	}

	// Choose random empty space
	srand(time(0));
	int emptyTarget = rand() % emptySpaces + 1;

	// Loop through empty spaces till Target is reached and place Goal
	int emptyCount = 0;
	for (size_t CellY = 0; CellY < kMazeRowsY; CellY++) // Rows
	{
		for (size_t CellX = 0; CellX < kMazeColumnsX; CellX++) // Columns
		{
			if (map[CellY][CellX] == '.' && !(CellY == playerY && CellX == playerX))
			{
				emptyCount++;
				if (emptyCount == emptyTarget)
				{
					map[CellY][CellX] = 'G';
					return;
				}
			}
		}
	}
}

void saveGame()
{
	ofstream saveFile("SaveGame.txt");

	if (!saveFile.is_open())
	{
		cout << "Failed to save game" << endl;
		return;
	}

	saveFile << playerX << " " << playerY << endl;

	for (int y = 0; y < kMazeRowsY; y++)
	{
		for (int x = 0; x < kMazeColumnsX; x++)
		{
			saveFile << map[y][x];
		}
		saveFile << endl;
	}
}

void loadGame()
{
	ifstream loadFile("SaveGame.txt");

	if (!loadFile.is_open())
	{
		cout << "No save file found" << endl;
		return;
	}

	loadFile >> playerX >> playerY;
	loadFile.ignore();

	string line;
	for (int y = 0; y < kMazeRowsY; y++)
	{
		getline(loadFile, line);
		for (int x = 0; x < kMazeColumnsX; x++)
		{
			if (x < (int)line.size())
				map[y][x] = line[x];
		}
	}

	loadFile.close();
	cout << "Game loaded" << endl;
}

void canMoveThere(EKeyPressed keypressed)
{
	switch (keypressed)
	{
	case EKeyPressed::eNone:
		break;
	case EKeyPressed::eLeft:
		if (map[playerY][playerX - 1] == 'G') { gameWon(); }
		if (map[playerY][playerX - 1] != '.' && map[playerY][playerX - 1] != 'G') { canMove = false; }
		break;
	case EKeyPressed::eUp:
		if (map[playerY - 1][playerX] == 'G') { gameWon(); }
		if (map[playerY - 1][playerX] != '.' && map[playerY - 1][playerX] != 'G') { canMove = false; }
		break;
	case EKeyPressed::eRight:
		if (map[playerY][playerX + 1] == 'G') { gameWon(); }
		if (map[playerY][playerX + 1] != '.' && map[playerY][playerX + 1] != 'G') { canMove = false; }
		break;
	case EKeyPressed::eDown:
		if (map[playerY + 1][playerX] == 'G') { gameWon(); }
		if (map[playerY + 1][playerX] != '.' && map[playerY + 1][playerX] != 'G') { canMove = false; }
		break;
	default:
		break;
	}
}

void movement()
{
	EKeyPressed keypressed = GetLastKeyPressed();

	if (keypressed == EKeyPressed::eSave)
	{
		saveGame();
		return;
	}
	if (keypressed == EKeyPressed::eLoad)
	{
		loadGame();
		return;
	}

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
	setMazeMap();
	initializePlayer();
	StartClock();

	while (UpdateFramework())
	{
		drawMaze();
		drawPlayer();
		movement();

		canMove = true;
		cout << GetElapsedTime() << endl;
	}
	return 0;
}
