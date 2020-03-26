//HEADER
#include "libft.h"

void	ft_tabdel(char ***array)
{
	size_t	i;
	char	**ptr;

	i = 0;
	if (array && *array)
	{
		ptr = *array;
		array = NULL;
		while (ptr[i])
		{
			ft_strdel(&(ptr[i]));
			i++;
		}
		free(ptr);
	}
}
