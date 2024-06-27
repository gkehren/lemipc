# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkehren <gkehren@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/19 16:01:19 by gkehren           #+#    #+#              #
#    Updated: 2024/05/23 15:56:18 by gkehren          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	 ft_memset.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
					ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strcmp.c \
					ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_toupper.c ft_tolower.c ft_bzero.c ft_memcpy.c  ft_calloc.c \
					ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c ft_memdel.c ft_strnew.c \
					ft_strnstr.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
					ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
					ft_split.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
					ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strlcpy.c \
					ft_substr.c ft_free.c get_next_line.c ft_printf.c

OBJS			= ${SRCS:.c=.o}

BONUS			=	 ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
					ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstclear.c

BONUS_OBJS		= $(BONUS:.c=.o)

NAME			= libft.a

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

all:			${NAME}

${NAME}:		${OBJS}
						ar rcs ${NAME} ${OBJS}

clean:
						${RM} ${OBJS} ${BONUS_OBJS}

fclean:			clean
						${RM} ${NAME}

re:				fclean ${NAME}

bonus:			$(OBJS) $(BONUS_OBJS)
						ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:			all clean fclean re bonus
