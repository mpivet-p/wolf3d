/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 11:33:28 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/24 16:54:31 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define MAX_CLIENTS	16
# define WLF_PORT		4221
# define SRV_BUFF		1024

typedef struct	s_client
{
	in_addr_t	addr;
	t_vector	player_pos;
	int32_t		sockfd;
	char		player_name[17];
	int8_t		connection_status;
	char		gap_0;
}				t_client;

#endif
