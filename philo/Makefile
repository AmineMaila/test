# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/27 15:00:30 by mmaila            #+#    #+#              #
#    Updated: 2024/03/02 23:26:28 by mmaila           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc

FLAGS= -Wall -Werror -Wextra -pthread 
# -fsanitize=thread

SRCS= main.c init.c threads.c utils.c srcs/ft_atoi.c srcs/ft_isdigit.c srcs/ft_putstr_fd.c

OBJS= $(SRCS:.c=.o)

NAME= philo

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c Includes/philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all