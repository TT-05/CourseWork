#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "maze.h"

struct Maze {

        char **grid;
        int row_num;
        struct Pos player;
        struct Pos start;
        struct Pos goal;
};

// helper function to check wether the given coordinate is in the grid
// return 1 if is in grid else 0
int inGrid(struct Maze *maze, struct Pos *pos){

	int x = pos->x;
	int y = pos->y;

	if (x >= 0 && y >= 0 && x < maze->row_num && ((maze->grid)[x][y]) != '\0') return 1;

	return 0;

}

// helper function to teleport player
// return new position coordinate
struct Pos teleport(struct Maze *maze, struct Pos *pos, char tile){
		
	for (int i = 0; i < maze->row_num; i++){
		
		for (int j = 0; (maze->grid)[i][j] != '\0'; j++){
			
			if ((maze->grid)[i][j] == tile && i != pos->x && j != pos->y){
				
				pos->x = i;
				pos->y = j;
				return *pos;
            }
        }
    }
    return *pos;
}

	/*
	int i = 0;
	int j = 0;

	for (; i < maze->row_num; i++){

		for (; (maze->grid)[i][j] != tile || i == pos->x || j == pos->y; j++);
	
	}
		
	pos->x = i;
	pos->y = j;

	return *pos;
	*/


struct Maze *readMaze(){

	int row_cap = 8;
	int col_cap = 8;
	int row_num = 0;
	int start = 0;
	int goal = 0;
	char c;

	struct Maze *maze = malloc(sizeof(struct Maze));

	char **grid = malloc(sizeof(char *)*row_cap);

	while ((c = getchar()) != '\n'){

		char *row = malloc(sizeof(char)*col_cap);
		int col_num = 0;

		while (c != '\n'){

			if (col_num == col_cap){

				col_cap *= 2;
				
				char *new_row = malloc(col_cap*sizeof(char));

				for (int i = 0; i < col_num; i++) new_row[i] = row[i];

				free(row);
				row = new_row;
			
			}

			row[col_num] = c;
			col_num++;

			if (c == 'S'){

				start++;

			}else if (c == 'G'){
				goal++;

			}

			c = getchar();
		}
		row[col_num] = '\0';

		if (row_num == row_cap){

			row_cap *= 2;

			char **new_grid = malloc(row_cap*sizeof(char*));

			for (int i = 0; i < row_num; i++) new_grid[i] = grid[i];

			free(grid);
			grid = new_grid;
		
		}

		grid[row_num] = row;
		row_num++;
	
	}

	if (start == 1 && goal > 0){

		maze->grid = grid;
		maze->row_num = row_num;

		for (int i = 0; i < maze->row_num; i++){

			for (int j = 0; (maze->grid)[i][j] != '\0'; j++){

				if ((maze->grid)[i][j] == 'S'){

					maze->start.x = i;
					maze->start.y = j;
					maze->player.x = i;
					maze->player.y = j;
				
				}else if ((maze->grid)[i][j] == 'G'){

					maze->goal.x = i;
					maze->goal.y = j;
				
				}
			}
		}

		return maze;

	}else{

		for (int i = 0; i < row_num; i++){

			free(grid[i]);
		
		}

		free(grid);

		return NULL;
	
	}
}

struct Pos makeMove(struct Maze *maze, char c){

	struct Pos new_pos;
	int dx, dy;

	if (c == 'n'){

		dx = -1;
		dy = 0;
	
	}else if (c == 's'){

		dx = 1;
		dy = 0;
	
	}else if (c == 'w'){

		dx = 0;
		dy = -1;
	
	}else if (c = 'e'){

		dx = 0;
		dy = 1;
	
	}

	new_pos.x = maze->player.x + dx;
	new_pos.y = maze->player.y + dy;

	int isInGrid = inGrid(maze, &new_pos);

	if (isInGrid == 0){

		new_pos.x = maze->player.x;
		new_pos.y = maze->player.y;

		return new_pos;
	
	}

	char new_tile = maze->grid[new_pos.x][new_pos.y];

	if (new_tile == 'G'){

		new_pos.x = -1;
		new_pos.y = -1;

	}else if (new_tile == 'X'){

		new_pos.x = maze->player.x;
                new_pos.y = maze->player.y;
	
	}else if (new_tile == 'I'){

		while (new_tile == 'I' && isInGrid == 1){

			new_pos.x += dx;
			new_pos.y += dy;
			isInGrid = inGrid(maze, &new_pos);
			if (!isInGrid) break;
			new_tile = maze->grid[new_pos.x][new_pos.y];
		
		}
		if (isInGrid == 0 || new_tile == 'X'){

			new_pos.x -= dx;
			new_pos.y -= dy;

		}else if (new_tile > '0' && new_tile < '9'){

			new_pos = teleport(maze, &new_pos, new_tile);
		
		}
	
	}else if (new_tile > '0' && new_tile < '9'){

		new_pos = teleport(maze, &new_pos, new_tile);
	
	}

	maze->player.x = new_pos.x;
        maze->player.y = new_pos.y;

	return new_pos;
}

void reset(struct Maze *maze){

	maze->player.x = maze->start.x;
	maze->player.y = maze->start.y;

}

void printMaze(struct Maze *maze){

	int count = 0;
	while ((maze->grid)[0][count] != '\0'){

		printf("-");
		count++;
	
	}
	printf("--\n");

	for (int i = 0; i < maze->row_num; i++){

                printf("|");
		for (int j = 0; (maze->grid)[i][j] != '\0'; j++){

                        if (maze->player.x == i && maze->player.y == j){

				printf("P");
			
			}else{

				printf("%c", (maze->grid)[i][j]);

			}
                }

                printf("|\n");

        }

	count = 0;
	while ((maze->grid)[(maze->row_num)-1][count] != '\0'){

                printf("-");
                count++;
	}

	printf("--\n");
}

struct Maze *destroyMaze(struct Maze *maze){

	for (int i = 0; i < maze->row_num; i++){

		free(maze->grid[i]);
	}
	free(maze->grid);
	free(maze);
	maze = NULL;

	return maze;
}


