#ifndef LEMIPC_H
#define LEMIPC_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#define BOARD_SIZE	10
#define SHM_KEY		42
#define SEM_KEY		43
#define MSGQ_KEY	44

typedef struct	s_board
{
	int	board[BOARD_SIZE][BOARD_SIZE];
	int	player_count;
	int	init;
}	t_board;

typedef struct	s_msg
{
	long		msg_type;
	char		msg_text[100];
}	t_msg;

typedef struct	s_lemipc
{
	int		shm_id;
	int		sem_id;
	int		msgq_id;
	t_board	*board;
	int		x;
	int		y;
}	t_lemipc;

// ipc.c
void	init_ipc_ressources(t_lemipc *lemipc);
void	cleanup_ipc_ressources(t_lemipc *lemipc);

// utils.c
void	lock_semaphore(int sem_id);
void	unlock_semaphore(int sem_id);
void	display_board(int board[BOARD_SIZE][BOARD_SIZE], int sem_id);
int		team_count(int board[BOARD_SIZE][BOARD_SIZE], int sem_id);

#endif
