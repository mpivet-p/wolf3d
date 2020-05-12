//HEADER

#include "wolf.h"
#include "libft.h"

int		print_and_quit(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
