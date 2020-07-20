/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:45:50 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/20 15:45:52 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

int		print_and_quit(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
