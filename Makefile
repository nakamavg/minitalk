# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 15:38:53 by ael-khni          #+#    #+#              #
#    Updated: 2024/01/05 04:36:37 by dgomez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
includes		=	./includes
CFLAGS			+=	-I. -I./includes
RM				=	rm -rf
SERVER			= server
CLIENT			= client

# Libft
LIBFT_DIR		=	lib/libft
LIBFT			=	$(LIBFT_DIR)/libft.a
CFLAGS			+=	-I $(LIBFT_DIR)

# Sources and objects

OBJ_S		=	server.o
OBJ_C		=	client.o
%.o:	%.c
	$(CC)	$(CFLAGS)	-c	$<	-o	$@


all:  $(LIBFT)
	$(MAKE) $(SERVER)
	$(MAKE) $(CLIENT)
	
$(SERVER):	$(OBJ_S)	$(LIBFT)
	$(CC)	$(CFLAGS)	-o	$(SERVER)	$(OBJ_S)	$(LIBFT)

$(CLIENT):	$(OBJ_C)	$(LIBFT)
	$(CC)	$(CFLAGS)	-o	$(CLIENT)	$(OBJ_C)	$(LIBFT)

$(LIBFT):
	 make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: all clean fclean re

.PHONY: all clean fclean re
