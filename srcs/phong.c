/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:40 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/22 12:47:51 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "miniRT.h"
#include "define.h"
#include "vect.h"
#include "math_utils.h"
#include <math.h>

typedef struct s_phong
{
	t_inter	inter_ray;
	int		solid_color;
	t_vect	hit_ray;
	t_vect	normal_n;
	t_vect	reflected;
	double	dot_normal_light;
	double	dot_normal_ray;
}	t_phong;

#define N_REFLECTION 5

void	add_lights(t_rgb *light_color, t_rgb diffuse, t_rgb specular)
{
	*light_color = color_add(*light_color, color_add(diffuse, specular));
}

t_rgb	diffuse_color(t_phong *phong, t_light light)
{
	float	kd;

	kd = KD * fabs(phong->dot_normal_light);
	return (color_k(light.color, kd));
}

t_rgb	specular_color(t_phong *phong, t_light light, t_vect h)
{
	float	ks;

	ks = KS * fabs(pow(dot(phong->normal_n, h), ALPHA_S));
	return (color_k(light.color, ks));
}

void	blin_phong(t_rt *rt, t_vect ray, t_phong *phong, t_rgb *lights)
{
	int		i;
	t_vect	ray_obj_n;
	t_vect	hit_light;
	t_inter	inter;
	t_vect	h;

	i = 0;
	while (i < rt->nb_light)
	{
		ray_obj_n = normalize(vec_sub(phong->hit_ray, rt->light[i].position));
		inter = nearest_inter(rt, ray_obj_n, rt->light[i].position);
		hit_light = get_point(rt->light[i].position, ray_obj_n, inter.t);
		if (vect_eq(&phong->hit_ray, &hit_light))
		{
			phong->dot_normal_light = dot(vec_mul(ray_obj_n, -1), phong->normal_n);
			if (phong->dot_normal_light > 0)
			{
				h = normalize(vec_add(ray_obj_n, ray));
				add_lights(lights, diffuse_color(phong, rt->light[i]), specular_color(phong, rt->light[i], h));
			}
		}
		i++;
	}
}

t_rgb	cast_ray_from(t_rt *rt, t_vect ray, t_vect from, int precision);

t_rgb	reflect_phong(t_rt *rt, t_vect ray, t_phong *phong, int precision)
{
	t_rgb	lights;
	t_rgb	reflected;
	float	reflexion;

	reflexion = phong->inter_ray.obj->reflexion;
	reflected = (t_rgb){0, 0, 0};
	lights = (t_rgb){0, 0, 0};
	if (reflexion > EPSILON && precision)
		reflected = cast_ray_from(rt, phong->reflected, vec_add(phong->hit_ray, vec_mul(phong->reflected, EPSILON)), precision - 1);
	if (!(reflexion > 1 - EPSILON && precision))
		blin_phong(rt, ray, phong, &lights);
	lights = color_add(rt->ambient.color, lights);
	return (
		color_add(
			color_k(mul_rgb(phong->solid_color, lights), 1 - reflexion)
			, color_k(reflected, reflexion)));
}

t_rgb	cast_ray_from(t_rt *rt, t_vect ray, t_vect from, int precision)
{
	t_phong	phong;

	normalize_to(&ray);
	phong.inter_ray = nearest_inter(rt, ray, from);
	if (!phong.inter_ray.obj)
		return ((t_rgb){0, 0, 0});
	phong.hit_ray = get_point(from, ray, phong.inter_ray.t);
	bump_texture(&phong.inter_ray, &phong.normal_n, &phong.solid_color, &phong.hit_ray);
	phong.dot_normal_ray = -dot(ray, phong.normal_n);
	if (phong.dot_normal_ray < 0)
	{
		phong.normal_n = vec_mul(phong.normal_n, -1);
		phong.dot_normal_ray *= -1;
	}
	phong.reflected = vec_sub(vec_mul(phong.normal_n, 2 * phong.dot_normal_ray), vec_mul(ray, -1));
	return (reflect_phong(rt, ray, &phong, precision));
}

t_rgb	is_it_touching(t_rt *rt, double x, double y)
{
	return (cast_ray_from(rt, ray_from_camera_to_objects(rt->camera, x, y), rt->camera.position, N_REFLECTION));
}
