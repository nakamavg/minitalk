# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 18:33:13 by dgomez-m          #+#    #+#              #
#    Updated: 2024/01/02 17:21:58 by dgomez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS			= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c 		\
				ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
				ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c 		\
				ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
      			ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
				ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_tolower.c \
					ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
					ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
					ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c \
					ft_lstsize_bonus.c get_next_line.c get_next_line_utils.c \
					ft_strings.c ft_print.c ft_numbers.c \

					
OBJS			= $(SRCS:.c=.o)
 
CC				= @cc
RM				= @rm -f
CFLAGS			= -Wall -Wextra -Werror -ggdb -pedantic -I.

NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS)
				@ar rcs $(NAME) $(OBJS)


clean:
				@$(RM) $(OBJS) 

fclean:			clean
				@$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re 
