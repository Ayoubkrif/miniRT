/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:40 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/22 13:23:16 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "define.h"
#include "vect.h"
#include <math.h>

void	add_lights(t_rgb *light_color, t_rgb diffuse, t_rgb specular)
{
	*light_color = color_add(*light_color, color_add(diffuse, specular));
}

t_rgb	diffuse_color(t_light light, double dot_normal_light, float kd)
{
	return (color_k(light.color, kd * dot_normal_light));
}

t_rgb	specular_color(t_phong *phong, t_light light, t_vect h, float ks,
		float alpha_s)
{
	return (color_k(light.color,
			ks * fabs(pow(dot(phong->normal_n, h), alpha_s))));
}

void	blin_phong(t_rt *rt, t_vect ray, t_phong *phong, t_rgb *lights)
{
	int		i;
	t_vect	ray_obj_n;
	t_vect	hit_light;
	double	dot_normal_light;
	t_inter	inter;

	i = 0;
	while (i < rt->nb_light)
	{
		ray_obj_n = normalize(vec_sub(phong->hit_ray, rt->light[i].position));
		inter = nearest_inter(rt, ray_obj_n, rt->light[i].position);
		hit_light = get_point(rt->light[i].position, ray_obj_n, inter.t);
		if (vect_eq(&phong->hit_ray, &hit_light))
		{
			dot_normal_light = -dot(ray_obj_n, phong->normal_n);
			if (dot_normal_light > 0)
				add_lights(lights,
					diffuse_color(rt->light[i], dot_normal_light, rt->kd),
					specular_color(phong, rt->light[i],
						normalize(vec_add(ray_obj_n, ray)),
						rt->ks, rt->alpha_s));
		}
		i++;
	}
}
