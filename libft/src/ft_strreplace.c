/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:02:36 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/04/29 22:12:38 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strreplace(char *src, char *toput, int n)
{
	char	*newstr;
	int		i;

	i = -1;
	newstr = (char*)malloc(sizeof(char) * (ft_strlen(src) - 2 +
				ft_strlen(toput)) + 1);
	while (++i < n)
		newstr[i] = *(src)++;
	src += 2;
	while (*toput)
		newstr[i++] = *(toput)++;
	while (*src)
		newstr[i++] = *(src)++;
	newstr[i] = 0;
	return (newstr);
}
