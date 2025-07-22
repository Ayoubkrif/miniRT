/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:26:14 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/22 13:35:03 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	ft_isisspace(int c)
{
	return ((c <= 13 && c >= 9) || c == ' ');
}

int	ft_isdigit(int c)
{
	return (c <= '9' && c >= '0');
}

int	int_len(char *nb)
{
	int	i;

	i = 0;
	while (nb[i] >= '0' && nb[i] <= '9')
		i++;
	return (i);
}

float	convert_nb(float to_convert, float precision)
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
	while (ft_isisspace(nptr[i]))
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
