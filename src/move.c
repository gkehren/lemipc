#include "../include/lemipc.h"

// Return 0 if move is successful, 1 otherwise
int	move_to(t_lemipc *lemipc, t_move_dir dir)
{
	int	new_x = lemipc->x;
	int	new_y = lemipc->y;
	int	ret = 1;

	switch (dir)
	{
		case UP: new_x = lemipc->x - 1; break;
		case DOWN: new_x = lemipc->x + 1; break;
		case LEFT: new_y = lemipc->y - 1; break;
		case RIGHT: new_y = lemipc->y + 1; break;
	}

	// Check if new position is valid
	if (new_x >= 0 && new_x < BOARD_SIZE && new_y >= 0 && new_y < BOARD_SIZE)
	{
		lock_semaphore(lemipc->sem_id);
		// Check if new position is free
		if (lemipc->board->board[new_x][new_y] == -1)
		{
			lemipc->board->board[lemipc->x][lemipc->y] = -1;
			lemipc->board->board[new_x][new_y] = lemipc->team_id;
			lemipc->x = new_x;
			lemipc->y = new_y;
			ret = 0;
		}
		unlock_semaphore(lemipc->sem_id);
	}
	return (ret);
}

int	find_enemy(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int *enemy_x, int *enemy_y)
{
	for (int i = x - VIEW_DIST; i <= x + VIEW_DIST; i++)
	{
		for (int j = y - VIEW_DIST; j <= y + VIEW_DIST; j++)
		{
			if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && board[i][j] != -1 && board[i][j] != board[x][y])
			{
				*enemy_x = i;
				*enemy_y = j;
				return (0);
			}
		}
	}
	return (1);
}
