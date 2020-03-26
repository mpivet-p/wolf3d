/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:58:19 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/11 15:39:44 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinsert(char *str, char *insertion, size_t location)
{
	char	*newstr;
	char	*tmp;
	char	*temp;
	size_t	len;

	temp = NULL;
	tmp = NULL;
	len = ft_strlen(str);
	newstr = ft_strsub(str, 0, location);
	tmp = ft_strjoin(newstr, insertion);
	free(newstr);
	newstr = tmp;
	temp = ft_strsub(str, location, len);
	tmp = ft_strjoin(newstr, temp);
	free(newstr);
	newstr = tmp;
	return (newstr);
}
