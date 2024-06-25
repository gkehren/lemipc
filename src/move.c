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
	*enemy_x = -1;
	*enemy_y = -1;
	return (1);
}

int closest_player(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int team_id, int enemy_x, int enemy_y)
{
	int player_distance = abs(x - enemy_x) + abs(y - enemy_y);
	int closest_distance = INT_MAX;
	int second_closest_distance = INT_MAX;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == team_id)
			{
				int distance = abs(i - enemy_x) + abs(j - enemy_y);
				if (distance < closest_distance)
				{
					second_closest_distance = closest_distance;
					closest_distance = distance;
				}
				else if (distance < second_closest_distance)
					second_closest_distance = distance;
			}
		}
	}

	if (player_distance == closest_distance || player_distance == second_closest_distance)
		return (0);
	else
		return (1);
}

int	check_adjcent_enemies(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int team_id)
{
	int	adjcent_enemies = 0;

	if (x > 0 && board[x - 1][y] != -1 && board[x - 1][y] != team_id)
		adjcent_enemies++;
	if (x < BOARD_SIZE - 1 && board[x + 1][y] != -1 && board[x + 1][y] != team_id)
		adjcent_enemies++;
	if (y > 0 && board[x][y - 1] != -1 && board[x][y - 1] != team_id)
		adjcent_enemies++;
	if (y < BOARD_SIZE - 1 && board[x][y + 1] != -1 && board[x][y + 1] != team_id)
		adjcent_enemies++;
	if (x > 0 && y > 0 && board[x - 1][y - 1] != -1 && board[x - 1][y - 1] != team_id)
		adjcent_enemies++;
	if (x > 0 && y < BOARD_SIZE - 1 && board[x - 1][y + 1] != -1 && board[x - 1][y + 1] != team_id)
		adjcent_enemies++;
	if (x < BOARD_SIZE - 1 && y > 0 && board[x + 1][y - 1] != -1 && board[x + 1][y - 1] != team_id)
		adjcent_enemies++;
	if (x < BOARD_SIZE - 1 && y < BOARD_SIZE - 1 && board[x + 1][y + 1] != -1 && board[x + 1][y + 1] != team_id)
		adjcent_enemies++;

	return (adjcent_enemies);
}
