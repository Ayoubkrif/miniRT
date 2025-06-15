/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:58:38 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/15 19:37:07 by cbordeau         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>
#include <string.h>

t_inter	best_intersection(t_rt *rt, t_inter *inter)
{
	t_inter	ret_val;
	int		i;
	double	dot;
	double	last_dot;

	ret_val = (t_inter){(t_vect){0, 0, 0}, (t_rgb){0, 0, 0}, 0};
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
	return (ret_val);
}

void	add_inter(t_rt *rt, t_vect ray, t_inter *inter)
{
	int		i;

	i = 0;
	while (rt->object[i])
	{
		if (*rt->object[i] == SPHERE)
			inter_sphere(rt, ray, inter, (t_sp *)rt->object[i]);
		else if (*rt->object[i] == CYLINDER)
			inter_cylinder(rt, ray, inter, (t_cy *)rt->object[i]);
		else if (*rt->object[i] == PLANE)
			inter_plane(rt, ray, inter, (t_pl *)rt->object[i]);
		i++;
	}
}

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	t_vect	ray;
	// t_inter	*inter;
	t_cam	*cam;

	cam = &rt->camera;
	assert((x < 960 && x >= -960) && (y < 540 && y >= -540));
	ray = vec_add(vec_mul(cam->screen.pix_x, x),
			vec_mul(cam->screen.pix_y, y));
	ray = vec_add(cam->screen.center, ray);
	ray = vec_sub(ray, cam->position);
	assert((vec_norm(ray)));
	ft_memset(rt->inter, 0, (rt->nb_object * 2 + 1) * sizeof(t_inter));
	// inter = calloc(2 * (rt->nb_object) + 1, sizeof(t_inter));
	// if (!inter)
	// 	printf("AAAAAAAAAA\n");
	add_inter(rt, ray, rt->inter);
	return (best_intersection(rt, rt->inter).color);
}

void	throwing_rays_through_the_wide_universe(t_rt *rt)
{
	int	i;
	int	j;

	i = -960;
	while (i < 960)
	{
		j = -539;
		while (j < 541)
		{
			put_a_pixel(rt, i + 960, j + 540,
				is_it_touching(rt, (double)i, -(double)j));
			j++;
		}
		i++;
	}
	/*printf("rayons envoyes !\n");*/
	mlx_put_image_to_window(rt->mlx.disp, rt->mlx.win, rt->mlx.img, 0, 0);
}
