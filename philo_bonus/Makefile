# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/27 15:00:30 by mmaila            #+#    #+#              #
#    Updated: 2024/03/02 23:56:09 by mmaila           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc

FLAGS= -Wall -Werror -Wextra -pthread -fsanitize=thread

SRCS= main_bonus.c init_bonus.c children_bonus.c utils_bonus.c srcs_bonus/ft_atoi_bonus.c srcs_bonus/ft_isdigit_bonus.c srcs_bonus/ft_putstr_fd_bonus.c

OBJS= $(SRCS:.c=.o)

NAME= philo_bonus

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c Includes/philo_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all