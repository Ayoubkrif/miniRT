/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:49:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/22 13:53:09 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"
#include "math_utils.h"

int	vect_eq(t_vect u, t_vect v)
{
	return (double_eq(u.x, v.x) && double_eq(u.y, v.y) && double_eq(u.z, v.z));
}

int	vect_col(t_vect u, t_vect v)
{
	double	x_div;
	double	y_div;
	double	z_div;

	x_div = u.x / v.x;
	y_div = u.y / v.y;
	z_div = u.z / v.z;
	return (double_eq(x_div, y_div) && double_eq(x_div, z_div));
}
