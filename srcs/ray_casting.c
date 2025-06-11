/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:58:38 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/11 15:22:29 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "libft.h"
#include <stdio.h>

void	add_inter(t_rt *rt, t_vect ray, t_inter *inter)
{
	int		i;
	double	delta;

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

void	is_it_touching(t_rt *rt, double x, double y)
{
	t_vect	ray;
	t_inter	*inter;

	ray = vec_add(rt->c_base.start, vec_mul(rt->c_base.pixel_x, x));
	ray = vec_add(ray, vec_mul(rt->c_base.pixel_y, y));
	ray = vec_sub(ray, rt->camera.position);
	inter = ft_calloc(rt->nb_object, sizeof(t_inter));
	if (!inter)
		printf("AAAAAAAAAA\n");
	add_inter(rt, ray, inter);
	// nous avons un tableau de toute les inter de sphere. 
	// il faut a present determiner la plus proche.
	// itere sur le tableau on garde le plus petit produit vectoriel positif
}

void	throwing_rays_through_the_wide_universe(t_rt *rt)
{
	int	i;
	int	j;

	i = -WIN_X / 2;
	while (i < WIN_X / 2)
	{
		j = -WIN_Y / 2;
		while (j < WIN_Y / 2)
		{
			is_it_touching(rt, i, j);
			j++;
		}
		i++;
	}
}
