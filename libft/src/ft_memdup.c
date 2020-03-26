/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:04:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2018/11/12 15:33:09 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void const *content, size_t content_size)
{
	unsigned char	*str1;
	unsigned char	*str2;
	void			*new;

	if (!(new = ft_memalloc(sizeof(void) * content_size)))
		return (NULL);
	str1 = (unsigned char*)content;
	str2 = (unsigned char*)new;
	while (*str1)
		*(str2++) = *(str1++);
	return (new);
}
