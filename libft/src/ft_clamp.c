/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 11:14:49 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/08/11 01:08:30 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_clamp(double value, double low, double high)
{
	if (value > low)
	{
		if (value < high)
			return (value);
		return (high);
	}
	return (low);
}
