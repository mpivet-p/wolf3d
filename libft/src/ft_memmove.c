/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:43:13 by mpivet-p          #+#    #+#             */
/*   Updated: 2018/11/11 21:38:00 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t					i;
	unsigned char			*dest;
	const unsigned char		*str;

	i = 0;
	dest = (unsigned char*)dst;
	str = (const unsigned char*)src;
	if (str < dest)
	{
		while (++i <= len)
			dest[len - i] = str[len - i];
	}
	else
	{
		while (len)
		{
			dest[i] = str[i];
			i++;
			len--;
		}
	}
	return (dst);
}
