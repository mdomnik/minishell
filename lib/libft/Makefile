# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 14:44:47 by kaan              #+#    #+#              #
#    Updated: 2024/02/05 17:57:04 by kaan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC	= inc/

SRC_DIR = src/

OBJ_DIR	= obj/

CC = gcc

FLAGS = -Wall -Wextra -Werror -I

RM = rm -f

AR	= ar rcs

SRC = $(SRC_DIR)ft_atoi.c\
		$(SRC_DIR)ft_bzero.c\
		$(SRC_DIR)ft_calloc.c\
		$(SRC_DIR)ft_isalnum.c\
		$(SRC_DIR)ft_isalpha.c\
		$(SRC_DIR)ft_isascii.c\
		$(SRC_DIR)ft_isdigit.c\
		$(SRC_DIR)ft_isprint.c\
		$(SRC_DIR)ft_itoa.c\
		$(SRC_DIR)ft_memchr.c\
		$(SRC_DIR)ft_memcmp.c\
		$(SRC_DIR)ft_memcpy.c\
		$(SRC_DIR)ft_memmove.c\
		$(SRC_DIR)ft_memset.c\
		$(SRC_DIR)ft_putchar_fd.c\
		$(SRC_DIR)ft_putendl_fd.c\
		$(SRC_DIR)ft_putnbr_fd.c\
		$(SRC_DIR)ft_putstr_fd.c\
		$(SRC_DIR)ft_split.c\
		$(SRC_DIR)ft_strchr.c\
		$(SRC_DIR)ft_strdup.c\
		$(SRC_DIR)ft_striteri.c\
		$(SRC_DIR)ft_strjoin.c\
		$(SRC_DIR)ft_strlcat.c\
		$(SRC_DIR)ft_strlcpy.c\
		$(SRC_DIR)ft_strlen.c\
		$(SRC_DIR)ft_strmapi.c\
		$(SRC_DIR)ft_strncmp.c\
		$(SRC_DIR)ft_strnstr.c\
		$(SRC_DIR)ft_strrchr.c\
		$(SRC_DIR)ft_strtrim.c\
		$(SRC_DIR)ft_substr.c\
		$(SRC_DIR)ft_tolower.c\
		$(SRC_DIR)ft_toupper.c\
		$(SRC_DIR)ft_lstadd_back.c\
		$(SRC_DIR)ft_lstadd_front.c\
		$(SRC_DIR)ft_lstclear.c\
		$(SRC_DIR)ft_lstdelone.c\
		$(SRC_DIR)ft_lstiter.c\
		$(SRC_DIR)ft_lstlast.c\
		$(SRC_DIR)ft_lstmap.c\
		$(SRC_DIR)ft_lstnew.c\
		$(SRC_DIR)ft_lstsize.c

OBJ = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) .cache_exists

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
