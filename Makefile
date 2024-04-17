# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 21:52:00 by kaan              #+#    #+#              #
#    Updated: 2024/04/17 20:29:27 by mdomnik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./lib/libft/libft.a

INC	= inc/

OBJ_DIR	= obj/

CC = cc

FLAGS = -g -Wall -Wextra -Werror -I

READFLAG = -lreadline

RM = rm -f

SRC =	src/expander/expander_process.c\
		src/expander/expander_struct.c\
		src/expander/expander.c\
		src/lexer/lexer_redir.c\
		src/lexer/lexer_struct.c\
		src/lexer/lexer_word.c\
		src/lexer/lexer.c\
		src/main/error_seq.c\
		src/main/main.c\
		src/main/testing.c\
		src/parser/parser.c\
		src/utils/gen_utils_1.c\
		src/utils/gen_utils_split.c\

OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC))

start:
	@make all

$(LIBFT):
	@make -C ./lib/libft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(INC) $(OBJ) $(LIBFT) $(READFLAG) -o $(NAME)

$(OBJ_DIR)%.o:		%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -C ./lib/libft

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: fclean all

.PHONY: start all clean fclean re
