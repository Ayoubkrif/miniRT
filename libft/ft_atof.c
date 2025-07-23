/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:26:14 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/23 11:00:51 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(char *nb)
{
	int	i;

	i = 0;
	while (ft_isdigit(nb[i]))
		i++;
	return (i);
}

static float	convert_nb(float to_convert, float precision)
{
	while (precision != 0)
	{
		to_convert *= 0.1;
		precision--;
	}
	return (to_convert);
}

float	ft_atof(const char *nptr)
{
	float	ipart;
	float	fpart;
	float	s;
	int		i;

	i = 0;
	s = 1;
	ipart = 0;
	fpart = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s = -s;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		ipart = ipart * 10 + nptr[i] - '0';
		i++;
	}
	if (nptr[i++] == '.')
		fpart = convert_nb(ft_atof(&nptr[i]), int_len((char *)&nptr[i]));
	return (s * (ipart + fpart));
}
