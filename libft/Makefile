# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/02 22:00:41 by mpivet-p          #+#    #+#              #
#    Updated: 2019/08/06 12:46:22 by mpivet-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
CC= gcc
CFLAGS= -Wall -Wextra -Werror

INC_PATH= inc/
SRC_PATH= src/
OBJ_PATH= obj/

INC_NAME= libft.h get_next_line.h
SRC_NAME = ft_atoi.c ft_atol.c ft_base_size.c ft_bzero.c ft_isalnum.c \
	ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c \
	ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstlen.c ft_lstmap.c ft_lstnew.c \
	ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
	ft_memdup.c ft_memmove.c ft_memset.c ft_print_char_tab.c ft_print_int_tab.c \
	ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
	ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c \
	ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
	ft_strequ.c ft_strinsert.c ft_striter.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
	ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
	ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c \
	ft_tolower.c ft_toupper.c ft_sqrt.c get_next_line.c print_bits.c \
	get_options.c ft_cat_buffer.c ft_sort_params.c ft_splitwhitespaces.c \
	ft_strreplace.c ft_strbchr.c ft_putscap.c free_tab.c how_many_lines.c \
	tabdup.c tab_realloc.c ft_clamp.c ft_max.c ft_tabdel.c
OBJ_NAME= $(SRC_NAME:.c=.o)

INC= -I inc/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

GRN= \033[92m
BLU= \033[94m
DEF= \033[0m

.PHONY: all clean fclean re

all: $(NAME)
	@:

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
