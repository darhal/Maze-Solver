#pragma once

#include <vector>
#include <array>
#include <utility>
#include <algorithm>
#include <random>
#include "graph.hpp"
#include <SDL.h>

static int random_n(int n) 
{ 
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, n - 1);
	return dist(rng);
}

// Creating a shortcut for int, int pair type 
typedef std::pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type 
typedef std::pair<double, std::pair<int, int>> pPair;

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

// A structure to hold the neccesary parameters 
struct cell
{
	// Row and Column index of its parent 
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	int parent_i, parent_j;
	// f = g + h 
	double f, g, h;
};


class Maze
{
public:
	typedef std::vector<std::vector<uint32_t>> MazeArray;

	enum wall_t {
		WALL = 0x000000,
		SPACE = 0xffffff,
		TRACE = 0xffff00,
	};
public:
    Maze();

	void Init(SDL_Renderer* renderer, int h = 32, int w = 32);

    void DigMaze(int r, int c, uint32_t* wall);

    void BuildMaze();

    void DisplayMaze();

    MazeArray& GetMazeArray() { return maze; }

	void ColorCase(SDL_Rect* rect, int row, int col, int r, int g, int b);

	void ColorCase(SDL_Rect* rect, int row, int col, uint32_t color);

	Graph ConstructGraph();

	void Solve();

	// Dijsktra
	void Dijsktra(int srcCol, int srcRow);

	std::pair<uint32_t , uint32_t> Get2DCoord(uint32_t coord);

	// A*
	bool isValid(int row, int col);

	bool isUnBlocked(int row, int col);

	bool isDestination(int row, int col, Pair dest);

	void AStarSearch(Pair src, Pair dest);

	void tracePath(const std::vector<std::vector<cell>>& cellDetails, Pair dest);

	// Utility:
	int GetH() const { return H - 2; }

	int GetW() const { return W - 2; }

	void SetCell(wall_t type, int row, int col);

	SDL_Rect& getRect() { return texture_sz; }
private:
    MazeArray maze;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect texture_sz;
    int H, W;

	static constexpr int TILE_W = 1;
	static constexpr int TILE_H = 1;

	void Dijsktra();
};