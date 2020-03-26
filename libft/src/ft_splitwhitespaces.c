/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:11:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/04/08 20:14:11 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str)
{
	int nb;

	nb = 0;
	while (*str)
	{
		if (*str == '\t' || *str == '\n' || *str == '\r'
					|| *str == '\v' || *str == ' ')
			str++;
		else
		{
			nb++;
			while (*str != '\t' && *str != '\n' && *str != '\r'
					&& *str != '\v' && *str != ' ' && *str != '\0')
				str++;
		}
	}
	return (nb);
}

static int	ft_count_c(char const *str)
{
	int nb;

	nb = 0;
	while (*str != '\t' && *str != '\n' && *str != '\r'
		&& *str != '\v' && *str != ' ' && *str != '\0')
	{
		nb++;
		str++;
	}
	return (nb);
}

char		**ft_splitwhitespaces(char const *s)
{
	int		j;
	int		k;
	int		nb;
	char	**tab;

	j = 0;
	k = 0;
	nb = ft_count_words(s);
	if (!s || !(tab = (char**)malloc(sizeof(char*) * (nb + 1))))
		return (NULL);
	while (j < nb)
	{
		while (!(*s != '\t' && *s != '\n' && *s != '\r'
			&& *s != '\v' && *s != ' ' && *s != '\0'))
			s++;
		if (!(tab[j] = (char*)malloc(sizeof(char) * (ft_count_c(s) + 1))))
			return (NULL);
		while (*s != '\t' && *s != '\n' && *s != '\r'
			&& *s != '\v' && *s != ' ' && *s != '\0')
			tab[j][k++] = *(s++);
		tab[j++][k] = '\0';
		k = 0;
	}
	tab[j] = 0;
	return (tab);
}
