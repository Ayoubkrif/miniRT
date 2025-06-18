/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:25:35 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/18 12:42:16 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

#define EPSILON 0.0001

double	to_deg(double angle)
{
	return (angle * 360 / (2 * PI));
}

double	to_rad(double angle)
{
	return ((angle * 2 * PI) / 360);
}

double	delta_2nd(double a, double b, double c)
{
	return (p2(b) - (4 * a * c));
}

double	p2(double x)
{
	return (x * x);
}

int	double_eq(double d1, double d2)
{
	double	diff;

	diff = d1 - d2;
	if (fabs(diff) < EPSILON)
		return (1);
	return (0);
}
