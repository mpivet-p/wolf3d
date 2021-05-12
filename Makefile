# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/22 02:45:47 by mpivet-p          #+#    #+#              #
#    Updated: 2020/08/12 11:17:21 by mpivet-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= wolf3d
CC= gcc
CFLAGS= -Wall -Wextra -Werror -g
OS = $(shell uname)

INC_PATH= includes
SRC_PATH= srcs/
OBJ_PATH= obj/

INC_NAME= wolf.h
SRC_NAME= main.c events.c tools.c camera.c parser.c misc.c draw_scene.c\
			visualizer.c bresenham.c draw_square.c rotate_vector.c draw_map.c\
			delta_dist.c side_dist.c textures_tools.c set_new_sprite.c\
			get_map_properties.c set_new_wall.c floor_ceiling_casting.c\
			get_index.c draw_sprites.c get_world_data.c intersect.c\
			get_sprites_dist.c init_socket.c connect.c send_pos_to_server.c\
			receive_players_pos.c
OBJ_NAME= $(SRC_NAME:.c=.o)

ifeq ($(OS), Linux)
	LIBS= -L libft/ -lft -L mlx/mlx_linux/ -lmlx -lm -lbsd -lX11 -lXext
	FRAM_MLX=
else
	MLX_DIR= mlx/mlx_mac
	LIB_MLX= -L $(MLX_DIR) -lmlx
	LIBS= -L libft/ -lft -L /usr/local/lib/ -lm $(LIB_MLX)
	FRAM_MLX= -framework OpenGL -framework AppKit
endif

INC= -I$(INC_PATH)/ -Ilibft/inc/ -Imlx/mlx_linux/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))


.PHONY: all clean fclean re local

all: $(NAME)
	@:

$(NAME): $(OBJ)
	@make -C libft
ifeq ($(LOCAL), t)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBS) $(FRAM_MLX)
else
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBS) $(FRAM_MLX)
endif

server: obj/init_socket.o obj/server.o obj/srv_connect_client.o\
	obj/srv_receive.o obj/srv_remove_client.o obj/srv_send_data.o
	make -C libft
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) -I includes -I libft/inc -o obj/server.o -c srcs/server.c
	$(CC) $(CFLAGS) -I includes -I libft/inc -o obj/srv_connect_client.o -c srcs/srv_connect_client.c
	$(CC) $(CFLAGS) -I includes -I libft/inc -o obj/srv_receive.o -c srcs/srv_receive.c
	$(CC) $(CFLAGS) -I includes -I libft/inc -o obj/srv_remove_client.o -c srcs/srv_remove_client.c
	$(CC) $(CFLAGS) -I includes -I libft/inc -o obj/srv_send_data.o -c srcs/srv_send_data.c
	$(CC) $(CFLAGS) -o server obj/server.o obj/srv_connect_client.o obj/srv_receive.o \
	obj/srv_remove_client.o obj/srv_send_data.o obj/init_socket.o -L libft -lft

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@make -C libft clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME) server

re: fclean all
