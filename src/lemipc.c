#include "../include/lemipc.h"

t_lemipc	lemipc;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		lock_semaphore(lemipc.sem_id);
		lemipc.board->board[lemipc.x][lemipc.y] = -1;
		lemipc.board->player_count--;
		if (lemipc.board->player_count == 0)
			cleanup_ipc_ressources(&lemipc);
		unlock_semaphore(lemipc.sem_id);
		exit(0);
	}
}

void	player_process(int	team_id)
{
	lock_semaphore(lemipc.sem_id);
	if (!lemipc.board->init)
		init_ipc_ressources(&lemipc);
	unlock_semaphore(lemipc.sem_id);

	lemipc.x = rand() % BOARD_SIZE;
	lemipc.y = rand() % BOARD_SIZE;

	lock_semaphore(lemipc.sem_id);
	while (lemipc.board->board[lemipc.x][lemipc.y] != -1)
	{
		lemipc.x = rand() % BOARD_SIZE;
		lemipc.y = rand() % BOARD_SIZE;
	}
	lemipc.board->board[lemipc.x][lemipc.y] = team_id;
	lemipc.board->player_count++;
	unlock_semaphore(lemipc.sem_id);

	while (team_count(lemipc.board->board, lemipc.sem_id) < 2)
		sleep(1);

	// Main loop
	while (1)
	{
		// Check death condition
		int	adjcent_enemies = 0;

		if (lemipc.x > 0 && lemipc.board->board[lemipc.x - 1][lemipc.y] != -1 && lemipc.board->board[lemipc.x - 1][lemipc.y] != team_id)
			adjcent_enemies++;
		if (lemipc.x < BOARD_SIZE - 1 && lemipc.board->board[lemipc.x + 1][lemipc.y] != -1 && lemipc.board->board[lemipc.x + 1][lemipc.y] != team_id)
			adjcent_enemies++;
		if (lemipc.y > 0 && lemipc.board->board[lemipc.x][lemipc.y - 1] != -1 && lemipc.board->board[lemipc.x][lemipc.y - 1] != team_id)
			adjcent_enemies++;
		if (lemipc.y < BOARD_SIZE - 1 && lemipc.board->board[lemipc.x][lemipc.y + 1] != -1 && lemipc.board->board[lemipc.x][lemipc.y + 1] != team_id)
			adjcent_enemies++;
		if (lemipc.x > 0 && lemipc.y > 0 && lemipc.board->board[lemipc.x - 1][lemipc.y - 1] != -1 && lemipc.board->board[lemipc.x - 1][lemipc.y - 1] != team_id)
			adjcent_enemies++;
		if (lemipc.x > 0 && lemipc.y < BOARD_SIZE - 1 && lemipc.board->board[lemipc.x - 1][lemipc.y + 1] != -1 && lemipc.board->board[lemipc.x - 1][lemipc.y + 1] != team_id)
			adjcent_enemies++;
		if (lemipc.x < BOARD_SIZE - 1 && lemipc.y > 0 && lemipc.board->board[lemipc.x + 1][lemipc.y - 1] != -1 && lemipc.board->board[lemipc.x + 1][lemipc.y - 1] != team_id)
			adjcent_enemies++;
		if (lemipc.x < BOARD_SIZE - 1 && lemipc.y < BOARD_SIZE - 1 && lemipc.board->board[lemipc.x + 1][lemipc.y + 1] != -1 && lemipc.board->board[lemipc.x + 1][lemipc.y + 1] != team_id)
			adjcent_enemies++;

		// If surrounded by at least 2 enemies, die
		if (adjcent_enemies >= 2)
			break;

		// Check if we are the last team
		if (team_count(lemipc.board->board, lemipc.sem_id) == 1)
			break;

		// Move to a random adjacent cell
		int	dir = rand() % 4;
		int	new_x = lemipc.x;
		int	new_y = lemipc.y;

		switch (dir)
		{
			case 0: new_x = lemipc.x - 1; break; // UP
			case 1: new_x = lemipc.x + 1; break; // DOWN
			case 2: new_y = lemipc.y - 1; break; // LEFT
			case 3: new_y = lemipc.y + 1; break; // RIGHT
		}

		// Check if new position is valid
		if (new_x >= 0 && new_x < BOARD_SIZE && new_y >= 0 && new_y < BOARD_SIZE)
		{
			lock_semaphore(lemipc.sem_id);
			// Check if new position is free
			if (lemipc.board->board[new_x][new_y] == -1)
			{
				lemipc.board->board[lemipc.x][lemipc.y] = -1;
				lemipc.board->board[new_x][new_y] = team_id;
				lemipc.x = new_x;
				lemipc.y = new_y;
			}
			unlock_semaphore(lemipc.sem_id);
		}

		// Sleep for a while
		sleep(1);
	}

	lock_semaphore(lemipc.sem_id);
	lemipc.board->board[lemipc.x][lemipc.y] = -1;
	lemipc.board->player_count--;
	if (lemipc.board->player_count == 0)
		cleanup_ipc_ressources(&lemipc);
	unlock_semaphore(lemipc.sem_id);
}

int	main(int argc, char **argv)
{
	int	display = 0;
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <team_id>\n", argv[0]);
		return (1);
	}
	if (strcmp(argv[1], "display") == 0)
		display = 1;
	else
		signal(SIGINT, signal_handler);

	int	team_id = atoi(argv[1]);

	// Attach shared memory
	lemipc.shm_id = shmget(SHM_KEY, sizeof(t_board), 0666);
	if (lemipc.shm_id < 0)
	{
		if (display == 1)
		{
			fprintf(stderr, "No shared memory found (the game needs to be started first)\n");
			return (1);
		}
		if (errno == ENOENT)
			init_ipc_ressources(&lemipc);
		else
		{
			perror("shmget");
			return (1);
		}
	}

	lemipc.board = (t_board *)shmat(lemipc.shm_id, NULL, 0);
	if (lemipc.board == (t_board *)-1)
	{
		perror("shmat");
		return (1);
	}

	lemipc.sem_id = semget(SEM_KEY, 1, 0666);
	if (lemipc.sem_id < 0)
	{
		perror("semget");
		return (1);
	}

	lemipc.msgq_id = msgget(MSGQ_KEY, 0666);
	if (lemipc.msgq_id < 0)
	{
		perror("msgget");
		return (1);
	}

	if (display == 1)
	{
		while (1)
		{
			display_board(lemipc.board->board, lemipc.sem_id);
			sleep(1);
		}
	}
	else
		player_process(team_id);

	return (0);
}
