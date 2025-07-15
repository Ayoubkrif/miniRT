/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:58:38 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/15 09:44:27 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include <stdio.h>

t_rgb	is_it_touching(t_rt *rt, double x, double y);

t_inter	nearest_inter(t_rt *rt, t_vect ray, t_vect	start)
{
	int		i;
	t_inter	inter;

	i = 0;
	inter = (t_inter){-1, 0, NULL, NONE, 0, -1};
	while (rt->object[i])
	{
		if (*rt->object[i] == SPHERE)
			inter_sphere(ray, (t_sp *)rt->object[i], &inter, start);
		else if (*rt->object[i] == CYLINDER)
		{
			inter_cylinder(ray, (t_cy *)rt->object[i], &inter, start);
			inter_disk(ray, (t_cy *)rt->object[i], &inter, start);
		}
		else if (*rt->object[i] == CONE)
			inter_cone(ray, (t_co *)rt->object[i], &inter, start);
		else if (*rt->object[i] == PLANE)
			inter_plane(ray, (t_pl *)rt->object[i], &inter, start);
		i++;
	}
	return (inter);
}

void	window_cast(t_rt *rt)
{
	int	i;
	int	j;

	i = -WIN_X / 2;
	while (i < WIN_X / 2)
	{
		j = -WIN_Y / 2;
		while (j < WIN_Y / 2)
		{
			put_a_pixel(rt, i + (WIN_X / 2), j + (WIN_Y / 2),
				is_it_touching(rt, (double)i, -(double)j));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(rt->mlx.disp, rt->mlx.win, rt->mlx.img, 0, 0);
	put_string(rt);
}
