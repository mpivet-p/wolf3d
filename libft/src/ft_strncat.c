/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:02:05 by mpivet-p          #+#    #+#             */
/*   Updated: 2018/11/17 14:05:20 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s1[i] == '\0' && s2[j] && (size_t)j < n)
	{
		s1[i] = s2[j];
		s1[i + 1] = '\0';
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}
