/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:58:38 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/16 17:14:57 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "mlx.h"

void	add_inter(t_rt *rt, t_vect ray)
{
	int		i;

	i = 0;
	while (rt->object[i])
	{
		if (*rt->object[i] == SPHERE)
			inter_sphere(rt, ray, (t_sp *)rt->object[i]);
		else if (*rt->object[i] == CYLINDER)
			inter_cylinder(rt, ray, (t_cy *)rt->object[i]);
		else if (*rt->object[i] == PLANE)
			inter_plane(rt, ray, (t_pl *)rt->object[i]);
		i++;
	}
}

t_rgb		shaker_ambiant_solid(t_rt *rt, t_rgb color)
{
	return ((t_rgb)
		{
			color.r * rt->ambiant.color.r * rt->ambiant.color.brightness,
			color.g * rt->ambiant.color.g * rt->ambiant.color.brightness,
			color.b * rt->ambiant.color.b * rt->ambiant.color.brightness, 1
		});
}

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	t_vect	ray;
	t_cam	*cam;

	cam = &rt->camera;
	// assert((x < 960 && x >= -960) && (y < 540 && y >= -540));
	ray = vec_add(vec_mul(cam->screen.pix_x, x),
			vec_mul(cam->screen.pix_y, y));
	ray = vec_add(cam->screen.center, ray);
	ray = vec_sub(ray, cam->position);
	// assert((vec_norm(ray)));
	rt->inter = (t_inter){-1, (t_rgb){0, 0, 0, 1}};
	add_inter(rt, ray);
	return (shaker_ambiant_solid(rt, rt->inter.color));
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
	mlx_put_image_to_window(rt->mlx.disp, rt->mlx.win, rt->mlx.img, 0, 0);
}
			/*color = shaker_ambiant_solid(rt, is_it_touching(rt, (double)i, -(double)j));*/
			/*my_mlx_pixel_put(rt, i, j, color);*/
/*int		shaker_ambiant_solid(t_rt *rt, t_rgb color)*/
/*{*/
/*	int		final_color;*/
/*	t_rgb	light_color;*/
/**/
/*	final_color = (((int)(color.r * 255 * rt->ambiant) << 16))*/
/*		| (((int)(color.g * 255) << 8))*/
/*		| ((int)(color.b * 255));*/
/*}*/
