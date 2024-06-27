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
	ft_memset(lemipc->board->board, -1, sizeof(lemipc->board->board));
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

int	send_message(int msgq_id, int team_id, char *msg)
{
	t_msg	message;

	message.msg_type = team_id;
	ft_strcpy(message.msg_text, msg);
	if (msgsnd(msgq_id, &message, sizeof(message.msg_text), 0) < 0)
	{
		perror("msgsnd");
		return (1);
	}
	ft_printf("Sent message: %s\n", msg);
	return (0);
}

int	receive_message(int msgq_id, int team_id, t_msg *msg)
{
	if (msgrcv(msgq_id, msg, sizeof(msg->msg_text), team_id, IPC_NOWAIT) < 0)
	{
		if (errno != ENOMSG)
		{
			perror("msgrcv");
			return (1);
		}
		else
			return (2);
	}
	return (0);
}
