# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarazicchieri <sarazicchieri@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/8 10:28:27 by sarazicchie       #+#    #+#              #
#    Updated: 2023/03/11 13:59:44 by sarazicchie      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC =	./src/*.c \
		./src/utils/*.c \
		./src/syntax/*.c \
		./src/parsing/*.c \
		./src/execute/*.c \
		./src/execute/execve/*.c \
		./src/built_in/*.c \
		./src/redirection/*.c \
		./src/expand_dollar/*.c

OBJC = $(SRC:%.c=%.o)

CC = gcc

USER = szicchie
HOME = /Users/${USER}

FLAGS = -Wall -Werror -Wextra 
##FLAG_READLINE =-lreadline -lcurses -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include
FLAG_READLINE =-lreadline -lcurses -L/opt/homebrew/opt/readline/lib

all: $(NAME)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $(FLAG_READLINE) $(F_IRINA) $(LDFLAGS) $(CPPFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f ${HOME}/.42minishell_history
	@rm -f fil*
	@rm -f .heredoc
	@rm -rf *.dSYM
	
re: fclean all

.PHONY: all clean fclean re
