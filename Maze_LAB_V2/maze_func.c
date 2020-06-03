#include "maze_func.h"


void GenerateMaze() {
	Maze = (int**)malloc(Size * sizeof(int*));
	for (int i = 0; i < Size; i++) {
		(Maze)[i] = (int*)malloc(Size * sizeof(int));
	}
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			(Maze)[i][j] = 0;
		}
	}
	int x = rand() % Size;
	int y = rand() % Size;
	Point* head = (Point*)malloc(sizeof(Point));
	head->x = x;
	head->y = y;
	head->next = 0;
	head->prev = 0;
	int flag = 0;
	int step_count = 1;
	(Maze)[x][y] = 1;
	while (flag == 0) {
		int direction = rand() % 4;
		int count = 0;
		if (x == 0) {
			count++;
		}
		else if ((Maze)[x - 1][y] != 0) {
			count++;
		}
		if (y == 0) {
			count++;
		}
		else if ((Maze)[x][y - 1] != 0) {
			count++;
		}
		if (x == Size - 1) {
			count++;
		}
		else if ((Maze)[x + 1][y] != 0) {
			count++;
		}
		if (y == Size - 1) {
			count++;
		}
		else if ((Maze)[x][y + 1] != 0) {
			count++;
		}
		if (count == 4) {
			if (head->prev == 0 || step_count > Size* Size / (rand() % 3 + 1)) {
				break;
			}
			else {
				head = head->prev;
				free(head->next);
				x = head->x;
				y = head->y;
			}

		}
		switch (direction) {
		case 0:
			if (x != 0 && (Maze)[x - 1][y] == 0) {
				x--;
				head->next = (Point*)malloc(sizeof(Point));
				head->next->x = x;
				head->next->y = y;
				head->next->next = 0;
				head->next->prev = head;
				head = head->next;
				step_count++;
				(Maze)[x][y] = 1;
			}
			break;
		case 1:
			if (y != 0 && (Maze)[x][y - 1] == 0) {
				y--;
				head->next = (Point*)malloc(sizeof(Point));
				head->next->x = x;
				head->next->y = y;
				head->next->next = 0;
				head->next->prev = head;
				head = head->next;
				step_count++;
				(Maze)[x][y] = 1;
			}
			break;
		case 2:
			if (x != Size - 1 && (Maze)[x + 1][y] == 0) {
				x++;
				head->next = (Point*)malloc(sizeof(Point));
				head->next->x = x;
				head->next->y = y;
				head->next->next = 0;
				head->next->prev = head;
				head = head->next;
				step_count++;
				(Maze)[x][y] = 1;
			}
			break;
		case 3:
			if (y != Size - 1 && (Maze)[x][y + 1] == 0) {
				y++;
				head->next = (Point*)malloc(sizeof(Point));
				head->next->x = x;
				head->next->y = y;
				head->next->next = 0;
				head->next->prev = head;
				head = head->next;
				step_count++;
				(Maze)[x][y] = 1;
			}
			break;
		default:
			continue;
		}
	}
	while (head->prev != 0) {
		head = head->prev;
		free(head->next);
	}
	free(head);
}

void DeleteMaze() {
	for (int i = 0; i < Size; i++) {
		free(Maze[i]);
	}
	free(Maze);
}