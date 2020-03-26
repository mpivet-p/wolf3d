/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:22:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2018/11/13 15:05:29 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!s)
		return (NULL);
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	while (s[j])
		j++;
	while (j > i && (s[j] == 32 || s[j] == 10 || s[j] == 9 || s[j] == 0))
		j--;
	j++;
	if (!(str = (char*)malloc(sizeof(char) * (j - i + 1))))
		return (NULL);
	while (s[i] && i < j)
		str[k++] = s[i++];
	str[k] = '\0';
	return (str);
}
