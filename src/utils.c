#include "../include/lemipc.h"

void	lock_semaphore(int sem_id)
{
	struct sembuf	sem_op;

	sem_op.sem_num = 0;
	sem_op.sem_op = -1;
	sem_op.sem_flg = 0;
	semop(sem_id, &sem_op, 1);
}

void	unlock_semaphore(int sem_id)
{
	struct sembuf	sem_op;

	sem_op.sem_num = 0;
	sem_op.sem_op = 1;
	sem_op.sem_flg = 0;
	semop(sem_id, &sem_op, 1);
}

void	display_board(int board[BOARD_SIZE][BOARD_SIZE], int sem_id)
{
	lock_semaphore(sem_id);

	printf("\033[H\033[J");
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == -1)
				printf(".");
			else
				printf("%d", board[i][j]);
		}
		printf("\n");
	}

	unlock_semaphore(sem_id);
}

int	team_count(int board[BOARD_SIZE][BOARD_SIZE], int sem_id)
{
	lock_semaphore(sem_id);

	int	teams[BOARD_SIZE * BOARD_SIZE];
	memset(teams, -1, sizeof(teams));
	int	team_count = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int team = board[i][j];
			if (team == -1)
				continue;
			int found = 0;
			for (int k = 0; k < team_count; k++)
			{
				if (teams[k] == team)
				{
					found = 1;
					break;
				}
			}
			if (!found)
				teams[team_count++] = team;
		}
	}

	unlock_semaphore(sem_id);
	return (team_count);
}
