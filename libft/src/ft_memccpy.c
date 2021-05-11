/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:58:21 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/04/27 16:14:00 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*dest;
	char	*str;
	int		i;

	dest = (char*)dst;
	str = (char*)src;
	i = 0;
	while (n)
	{
		dest[i] = str[i];
		if (str[i] == (char)c)
			return (dst +i + 1);
		i++;
		n--;
	}
	return (NULL);
}
