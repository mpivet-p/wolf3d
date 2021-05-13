from os import path
from random import randint, randrange
import numpy as np

def generate_map(line, col, player_x, player_y, nb_sprite):
	maze = np.zeros((line, col))
	maze[0,:] = 1
	maze[-1,:] = 1
	maze[:,0] = 1
	maze[:,-1] = 1

	draw = randint(1, int((line - 1) * (col - 1) / 3))
	for _ in range(draw):
		x_coord = randint(1, col - 2)
		y_coord = randint(1, line - 2)
		id_sprite = randint(1, nb_sprite)
		maze[y_coord,x_coord] = id_sprite

	s_maze = np.array2string(maze, separator=' ', formatter={'int':lambda x: int(x)})
	print(s_maze)
	s_maze = s_maze.replace('\n','')
	s_maze = s_maze.replace('[','')
	s_maze = s_maze.replace(".]",'\n')
	s_maze = s_maze.replace(" ",'')
	s_maze = s_maze.replace(".",' ')
	s_maze = s_maze.replace("]",'')
	print("\n", s_maze)
	return (s_maze[:-1])

def sprite_things():
	s ="1:textures/greystone.xpm\n"
	s +="2:textures/bluestone.xpm:textures/redbrick.xpm:textures/mossy.xpm:textures/purplestone.xpm\n"
	s +="3:textures/bluestone.xpm\n"
	s +="4:textures/redbrick.xpm\n"
	s +="5:textures/eagle.xpm\n"
	s +="6:textures/mossy.xpm\n"
	s +="7:textures/colorstone.xpm\n"
	s +="8:textures/purplestone.xpm\n"
	s +="9:textures/wood.xpm\n"
	s +="10:textures/pillar.xpm\n"
	s +="floor:textures/colorstone.xpm\n"
	s +="ceiling:textures/wood.xpm\n"
	s +="#sprite:texture path:x:y\n"
	s +="sprite:textures/pillar.xpm:5.2:10.2\n"
	s +="sprite:textures/pillar.xpm:5.0:10.0\n"
	s +="sprite:textures/greenlight.xpm:7.0:10.2\n"
	s +="sprite:textures/barrel.xpm:7.0:10.2\n"
	s +="player:textures/player.xpm"
	return (s)


if __name__ == "__main__":
	line = -1
	col = -1
	up_limit = 50
	while not isinstance(line, int) or not (line > 0 and line < up_limit):
		tmp = input("Give the number of lines of the maze:")
		if tmp != None:
			line = int(tmp)
		else:
			line = -1
	while not isinstance(col, int) or not (col > 0 and col < up_limit):
		tmp = input("Give the number of columns of the maze:")
		if tmp != None:
			col = int(tmp)
		else:
			col = -1
	
	player_x = -1
	player_y = -1
	while not isinstance(player_x, int) or not (player_x > 0 and player_x < col):
		tmp = input("Give the player x coordinates within the maze:")
		if tmp != None:
			player_x = int(tmp)
		else:
			player_x = -1
	while not isinstance(player_y, int) or not (player_y > 0 and player_y < line):
		tmp = input("Give the player y coordinates within the maze:")
		if tmp != None:
			player_y = int(tmp)
		else:
			player_y = -1
	
	id_map = 0
	while (path.exists(f"map_{id_map}.txt")):
		id_map += 1

	nb_sprite = 8
	with open(f"map_{id_map}.txt", "w+") as opened_file:
		opened_file.write(f"{col}x{line}\n")
		opened_file.write(f"{player_x:2d}x{player_y:2d}\n".replace(' ','0'))
		opened_file.write(generate_map(line, col, player_x, player_y, nb_sprite)+"\n")
		opened_file.write(sprite_things())
