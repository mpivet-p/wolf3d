/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:01:32 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/20 15:38:32 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <limits.h>
#include <math.h>

static int8_t	char_to_double(char *str, double *num)
{
	int64_t	tmp;
	double	decimal;
	int8_t	ret;
	char	**tab;

	ret = SUCCESS;
	if ((tab = ft_strsplit(str, '.')) == NULL)
		return (FAILURE);
	if (ft_tablen(tab) <= 2 && ft_atol(tab[0], &tmp) == SUCCESS
			&& tmp < 100 && tmp >= 0)
	{
		*num = tmp;
		if (ft_tablen(tab) == 2 && ft_atol(tab[1], &tmp) == SUCCESS
				&& tmp < INT_MAX)
		{
			decimal = tmp / pow(10, (int)log(tmp) + 1);
			*num += (decimal > 0) ? decimal : 0;
		}
		else
			ret = FAILURE;
	}
	else
		ret = FAILURE;
	free_tab(&tab);
	return (ret);
}

int8_t			set_new_sprite(
		t_core *wolf, char **prp, char **files, int *tex_i)
{
	t_sprite	*sprt;
	int8_t		ret;
	int			tex_num;

	ret = SUCCESS;
	sprt = &(wolf->world.sprites[wolf->world.sprt_nbr]);
	if ((tex_num = register_new_texture(wolf, prp, files, tex_i)) == FAILURE)
		return (FAILURE);
	sprt->tex_id = tex_num;
	if (char_to_double(prp[2], &(sprt->x)) != SUCCESS)
		ret = FAILURE;
	if (ret == SUCCESS && char_to_double(prp[3], &(sprt->y)) != SUCCESS)
		ret = FAILURE;
	if (ret == SUCCESS)
		wolf->world.sprt_nbr++;
	return (ret);
}
