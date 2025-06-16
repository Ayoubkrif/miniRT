/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:58:38 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/16 13:05:38 by cbordeau         ###   ########.fr       */
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
	rt->inter = (t_inter){-1, (t_rgb){0, 0, 0}};
	add_inter(rt, ray);
	return (rt->inter.color);
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
