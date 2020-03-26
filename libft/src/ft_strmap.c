/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:19:46 by mpivet-p          #+#    #+#             */
/*   Updated: 2018/11/13 12:25:51 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	char	*result;
	int		i;

	i = 0;
	str = (char*)s;
	if (!s)
		return (NULL);
	while (str[i])
		i++;
	if (!(result = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = f(str[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
