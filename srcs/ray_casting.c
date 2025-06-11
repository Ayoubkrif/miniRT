/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:58:38 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/11 19:55:42 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "libft.h"
#include <stdio.h>

t_inter	best_intersection(t_rt *rt, t_inter *inter)
{
	t_inter	ret_val;
	int		i;
	double	dot;
	double	last_dot;

	ret_val = (t_inter){(t_vect){0,0,0}, (t_rgb){0,0,0}, 0};
	i = 0;
	while (inter[i].init)
	{
		dot = dot_prod(rt->camera.direction, inter[i].point);
		if (dot > 0 && (!ret_val.init || dot < last_dot))
		{
			last_dot = dot;
			ret_val = inter[i];
		}
		i++;
	}
	free(inter);
	return (ret_val);
}

void	add_inter(t_rt *rt, t_vect ray, t_inter *inter)
{
	int		i;

	i = 0;
	while (rt->object[i])
	{
		if (*rt->object[i] == SPHERE)
			inter_sphere(rt, ray, inter, (t_sphere *)rt->object[i]);
		else if (*rt->object[i] == CYLINDER)
			inter_cylinder(rt, ray, inter, (t_cylinder *)rt->object[i]);
		else if (*rt->object[i] == PLANE)
			inter_plane(rt, ray, inter, (t_plane *)rt->object[i]);
		i++;
	}
}

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	t_vect	ray;
	t_inter	*inter;

	assert((x < 960 && x >= -960) && (y < 540 && y >= -540));
	ray = vec_add(vec_mul(rt->c_base.pixel_x, x), vec_mul(rt->c_base.pixel_y, y));
	ray = vec_add(rt->c_base.start, ray);
	ray = vec_sub(ray, rt->camera.position);
	inter = calloc(2 * (rt->nb_object) + 1, sizeof(t_inter));
	if (!inter)
		printf("AAAAAAAAAA\n");
	add_inter(rt, ray, inter);
	return (best_intersection(rt, inter).color);
}

void	throwing_rays_through_the_wide_universe(t_rt *rt)
{
	int	i;
	int	j;

	i = -960;
	while (i < 960)
	{
		j = -540;
		while (j < 540)
		{
			put_a_pixel(rt, i + 960, j + 540, is_it_touching(rt, (double)i, (double)j));
			j++;
		}
		i++;
	}
	printf("rayons envoyes !\n");
}
