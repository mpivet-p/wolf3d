/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_receive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:09:47 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/12 12:15:08 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf.h"

int8_t	receive(int socket, char *buffer, struct sockaddr_in *csin, int *len)
{
	size_t	sinsize;

	ft_bzero(csin, sizeof(*csin));
	sinsize = sizeof(*csin);
	if ((*len = recvfrom(socket, buffer, SRV_BUFF
					, 0, (struct sockaddr*)csin, (socklen_t*)&sinsize)) < 0)
	{
		ft_putstr_fd("wolf server: recvfrom error\n", STDERR_FILENO);
		return (FAILURE);
	}
	buffer[*len] = 0;
	return (SUCCESS);
}
