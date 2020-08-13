/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_remove_client.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:04:43 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/13 15:05:44 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "server.h"

void	remove_client(t_client *clients, struct sockaddr_in *sin, int *nbr)
{
	int	id;

	id = 0;
	ft_putstr("wolf server: Client disconnected\n");
	while (id < *nbr)
	{
		if (clients[id].sin.sin_addr.s_addr == sin->sin_addr.s_addr
				&& clients[id].sin.sin_port == sin->sin_port)
		{
			ft_memmove(&(clients[id]), &(clients[id + 1])
					, sizeof(t_client) * (*nbr - id));
			*nbr = *nbr - 1;
			return ;
		}
		id++;
	}
	ft_putstr_fd("Wolf server: player to remove not found!\n", STDERR_FILENO);
}
