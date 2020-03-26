/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 02:57:26 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/20 07:14:29 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		tab_realloc(char ***tab)
{
	char	**ret;
	int		j;
	int		i;

	j = 0;
	i = 0;
	ret = NULL;
	while (tab && *tab && (*tab)[i])
		i++;
	if (!(ret = (char**)malloc(sizeof(char*) * (i + 2))))
		return (-1);
	while (tab && *tab && (*tab)[j])
	{
		ret[j] = (*tab)[j];
		(*tab)[j] = NULL;
		j++;
	}
	ret[j] = 0;
	ret[j + 1] = 0;
	if (tab)
		free_tab(tab);
	*tab = ret;
	return (i);
}
