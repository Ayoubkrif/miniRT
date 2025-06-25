/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:25:35 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/25 13:46:26 by aykrifa          ###   ########.fr       */
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

	// quad->second_root = (-quad->b - root) / (2 * quad->a);

int	delta_2nd(t_quadratic *quad)
{
	quad->delta = p2(quad->b) - (4 * quad->a * quad->c);
	if (quad->delta <= 0)
		return (0);
	quad->sq_delta = sqrt(quad->delta);
	if (quad->a > 0)
	{
		if (quad->b > quad->sq_delta && quad->b > -quad->sq_delta)
			return (0);
		else if (quad->b < quad->sq_delta && quad->b > -quad->sq_delta)
			return (quad->root = (-quad->b + quad->sq_delta) / (2 * quad->a), 1);
		return (quad->root = (-quad->b - quad->sq_delta) / (2 * quad->a), 1);
	}
	if (quad->b < quad->sq_delta && quad->b < -quad->sq_delta)
		return (0);
	else if (quad->b > quad->sq_delta && quad->b < -quad->sq_delta)
		return (quad->root = (-quad->b + quad->sq_delta) / (2 * quad->a), 1);
	return (quad->root = (-quad->b - quad->sq_delta) / (2 * quad->a), 1);
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
