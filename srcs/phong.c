/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:40 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/17 09:34:15 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "miniRT.h"
#include "define.h"
#include "vect.h"

typedef struct s_phong
{
	t_inter	inter_ray;
	int		solid_color;
	t_vect	light_obj_n;
	t_inter	inter_light;
	t_vect	point_ray;
	t_vect	point_light;
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

t_rgb	blin_phong(t_rt *rt, t_vect ray, t_phong *phong)
{
	int		i;
	t_rgb	lights_color;
	t_rgb	diffuse;
	t_rgb	specular;
	t_vect	h;

	lights_color = (t_rgb){0, 0, 0};
	i = 0;
	while (i < rt->nb_light)
	{
		phong->light_obj_n = normalize(vec_sub(phong->point_ray, rt->light[i].position));
		phong->inter_light = nearest_inter(rt, phong->light_obj_n, rt->light[i].position);
		phong->point_light = get_point(rt->light[i].position, phong->light_obj_n, phong->inter_light.t);
		if (vect_eq(&phong->point_ray, &phong->point_light))
		{
			phong->dot_normal_light = dot(vec_mul(phong->light_obj_n, -1), phong->normal_n);
			if (phong->dot_normal_light > 0)
			{
				diffuse = diffuse_color(phong, rt->light[i]);
				h = normalize(vec_add(phong->light_obj_n, ray));
				specular = specular_color(phong, rt->light[i], h);
				add_lights(&lights_color, diffuse, specular);
			}
		}
		i++;
	}
	return (lights_color);
}

t_rgb	cast_ray_from(t_rt *rt, t_vect ray, t_vect from, int precision);

t_rgb	reflect_phong(t_rt *rt, t_vect ray, t_phong *phong, int precision)
{
	int		r;
	int		l;
	t_rgb	lights;
	t_rgb	reflected;

	l = 1;
	r = 1;
	reflected = (t_rgb){0, 0, 0};
	lights = (t_rgb){0, 0, 0};
	if (phong->inter_ray.obj->reflexion > EPSILON && precision)
		reflected = cast_ray_from(rt, phong->reflected, vec_add(phong->point_ray, vec_mul(phong->reflected, EPSILON)), precision - 1);
	else
		r = 0;
	if (!(phong->inter_ray.obj->reflexion > 1 - EPSILON && precision))
		lights = blin_phong(rt, ray, phong);
	else
		l = 0;
	lights = color_add(rt->ambient.color, lights);
	if (l && r)
		return (color_add(color_k(mul_rgb(phong->solid_color, lights), 1 - phong->inter_ray.obj->reflexion), color_k(reflected, phong->inter_ray.obj->reflexion)));
	else if (!r && l)
		return (mul_rgb(phong->solid_color, lights));
	else if (r && !l)
		return (reflected);
	else
		return ((t_rgb){0, 0, 0});
}

t_rgb	cast_ray_from(t_rt *rt, t_vect ray, t_vect from, int precision)
{
	t_phong	phong;

	normalize_to(&ray);
	phong.inter_ray = nearest_inter(rt, ray, from);
	if (!phong.inter_ray.obj)
		return ((t_rgb){0, 0, 0});
	phong.point_ray = get_point(from, ray, phong.inter_ray.t);
	get_color_normal(&phong.inter_ray, &phong.normal_n, &phong.solid_color, &phong.point_ray);
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
