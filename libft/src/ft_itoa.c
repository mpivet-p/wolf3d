/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:34:21 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/04/27 16:10:08 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char			*result;
	unsigned int	nb;
	int				i;

	i = ft_base_size(n, 10);
	if (n < 0)
		nb = n * -1;
	else
		nb = n;
	result = (char*)malloc(sizeof(char) * i + 1);
	result[i--] = 0;
	while (nb > 0)
	{
		result[i] = nb % 10 + 48;
		nb = nb / 10;
		i--;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
