/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_from.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:40 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/22 13:23:08 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "miniRT.h"
#include "vect.h"
#include "math_utils.h"

t_rgb	reflect_phong(t_rt *rt, t_vect ray, t_phong *phong, int precision)
{
	t_rgb	lights;
	t_rgb	reflected;
	float	reflexion;

	reflexion = phong->inter_ray.obj->reflexion;
	reflected = (t_rgb){0, 0, 0};
	lights = (t_rgb){0, 0, 0};
	if (reflexion > EPSILON && precision)
		reflected = cast_ray_from(rt, phong->reflected,
				vec_add(phong->hit_ray,
					vec_mul(phong->reflected, EPSILON)), precision - 1);
	if (!(reflexion > 1 - EPSILON && precision))
		blin_phong(rt, ray, phong, &lights);
	lights = color_add(color_k(rt->ambient.color, rt->ka), lights);
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
	bump_texture(&phong.inter_ray, &phong.normal_n, &phong.solid_color,
		&phong.hit_ray);
	phong.dot_normal_ray = -dot(ray, phong.normal_n);
	if (phong.dot_normal_ray < 0)
	{
		phong.normal_n = vec_mul(phong.normal_n, -1);
		phong.dot_normal_ray *= -1;
	}
	phong.reflected = vec_sub(vec_mul(phong.normal_n, 2 * phong.dot_normal_ray),
			vec_mul(ray, -1));
	return (reflect_phong(rt, ray, &phong, precision));
}
