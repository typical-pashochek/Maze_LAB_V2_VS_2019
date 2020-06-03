#ifndef maze_func
#define maze_func
struct Point {
	int x;
	int y;
	struct Point* next;
	struct Point* prev;
};

typedef struct Point Point;
int Size;
int Delay;
int** Maze;
void GenerateMaze();
void DeleteMaze();
#endif
