# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/22 02:45:47 by mpivet-p          #+#    #+#              #
#    Updated: 2020/08/05 17:38:31 by mpivet-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= wolf3d
CC= gcc
CFLAGS= -Wall -Wextra -Werror -g

INC_PATH= includes/
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

INC= -I includes/ -I libft/inc/ -I mlx/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIBS= -L libft/ -lft -L /usr/local/lib/ -lmlx -lm
MLX= -framework OpenGL -framework AppKit

.PHONY: all clean fclean re local

all: $(NAME)
	@:

$(NAME): $(OBJ)
	@make -C libft
ifeq ($(LOCAL), t)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) -L libft/ -lft -L mlx/ -lmlx -lm $(MLX)
else
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBS) $(MLX)
endif

server: obj/init_socket.o obj/init_socket.o obj/server.o
	make -C libft
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) -I includes -I libft/inc -o obj/server.o -c srcs/server.c
	$(CC) $(CFLAGS) -o server obj/server.o obj/init_socket.o -L libft -lft

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
