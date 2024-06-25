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

#define BOARD_SIZE	25
#define VIEW_DIST	2

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
	int		team_id;
}	t_lemipc;

typedef enum	e_move_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
}	t_move_dir;

// ipc.c
void	init_ipc_ressources(t_lemipc *lemipc);
void	cleanup_ipc_ressources(t_lemipc *lemipc);
int		send_message(int msgq_id, int team_id, char *msg);
int		receive_message(int msgq_id, int team_id, t_msg *msg);

// move.c
int		move_to(t_lemipc *lemipc, t_move_dir dir);
int		find_enemy(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int *enemy_x, int *enemy_y);
int		check_adjcent_enemies(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int team_id);

// utils.c
void	lock_semaphore(int sem_id);
void	unlock_semaphore(int sem_id);
void	display_board(int board[BOARD_SIZE][BOARD_SIZE], int sem_id);
int		team_count(int board[BOARD_SIZE][BOARD_SIZE], int sem_id);

#endif
