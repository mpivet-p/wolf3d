/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_remove_client.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:04:43 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/12 11:01:40 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "server.h"

void	remove_client(t_client *clients, in_addr_t address, int *nbr)
{
	int	id;

	id = 0;
	ft_putstr("wolf server: Client disconnected\n");
	while (id < *nbr && clients[id].sin.sin_addr.s_addr != address)
		id++;
	if (id < *nbr)
	{
		ft_memmove(&(clients[id]), &(clients[id + 1])
				, sizeof(t_client) * (MAX_CLIENTS - id));
		(*nbr)--;
	}
}
