#include "../include/lemipc.h"

void	init_ipc_ressources(t_lemipc *lemipc)
{
	// Create shared memory
	lemipc->shm_id = shmget(SHM_KEY, sizeof(t_board), IPC_CREAT | 0666);
	if (lemipc->shm_id < 0)
	{
		perror("shmget");
		exit(1);
	}

	// Attach shared memory
	lemipc->board = (t_board *)shmat(lemipc->shm_id, NULL, 0);
	if (lemipc->board == (t_board *)-1)
	{
		perror("shmat");
		exit(1);
	}

	// Create semaphore
	lemipc->sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
	if (lemipc->sem_id < 0)
	{
		perror("semget");
		exit(1);
	}

	// Init semaphore
	semctl(lemipc->sem_id, 0, SETVAL, 1);

	// Create message queue
	lemipc->msgq_id = msgget(MSGQ_KEY, IPC_CREAT | 0666);
	if (lemipc->msgq_id < 0)
	{
		perror("msgget");
		exit(1);
	}

	// Init board
	memset(lemipc->board->board, -1, sizeof(lemipc->board->board));
	lemipc->board->player_count = 0;
	lemipc->board->init = 1;
}

void	cleanup_ipc_ressources(t_lemipc *lemipc)
{
	// Detach shared memory
	shmdt(lemipc->board);

	// Remove shared memory
	shmctl(lemipc->shm_id, IPC_RMID, NULL);

	// Remove semaphore
	semctl(lemipc->sem_id, 0, IPC_RMID);

	// Remove message queue
	msgctl(lemipc->msgq_id, IPC_RMID, NULL);
}
