/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:14:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/11 15:40:02 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_opts	get_options(int argc, char **argv, char *allowed)
{
	t_opts	ret;
	int		j;
	int		i;

	j = 1;
	ret = 0;
	while (j < argc && argv[j][0] == '-')
	{
		i = 1;
		while (argv[j][i])
		{
			if (argv[j][0] != '-' || (argv[j][0] == '-'
						&& argv[j][1] == '-' && argv[j][2] == 0))
				return (ret);
			if (!ft_strchr(allowed, argv[j][i]))
				return ((t_opts)argv[j][i] | 1ULL << 63);
			if (argv[j][i] >= 97 && argv[j][i] <= 122)
				ret = ret | (1ULL << (argv[j][i] - 97));
			if (argv[j][i] >= 65 && argv[j][i] <= 90)
				ret = ret | (1ULL << ((argv[j][i] - 65) + 32));
			i++;
		}
		j++;
	}
	return (ret);
}
