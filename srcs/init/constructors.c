/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:01 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/19 09:07:59 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "miniRT.h"
#include <stdlib.h>


#define KA 0.2
#define KD 0.9


int	get_cam_info(char **tok, t_rt *rt)
{
	if (fill_vec(tok[1], &rt->camera.position))
		return (1);
	if (fill_vec(tok[2], &rt->camera.direction_n))
		return (1);
	if (!tok[3])
		return (1);
	rt->camera.fov = ft_atoi(tok[3]);
	rt->camera.direction_n = get_normalized_vec(rt->camera.direction_n);
	return (0);
}

int	get_light_info(char **tok, t_rt *rt)
{
	if (fill_vec(tok[1], &rt->light.position))
		return (1);
	if (!tok[2])
		return (1);
	if (fill_rgb(tok[3], &rt->light.color))
		return (1);
	rt->light.color.brightness = atof(tok[2]) * KD;
	return (0);
}

int	get_ambient_info(char **tok, t_rt *rt)
{
	if (!tok[1])
		return (1);
	if (fill_rgb(tok[2], &rt->ambiant.color))
		return (1);
	rt->ambiant.color.brightness = atof(tok[1]) * KA;
	return (0);
}

int	get_sphere_info(char **tok, t_rt *rt)
{
	t_sp	*sp;

	sp = malloc(sizeof(t_sp));
	sp->type = SPHERE;
	if (fill_vec(tok[1], &sp->center))
		return (1);
	if (!tok[2])
		return (1);
	sp->diameter = atof(tok[2]);
	if (fill_rgb(tok[3], &sp->color))
		return (1);
	sp->color = color_mul(sp->color, (t_rgb){255, 255, 255, 1});
	rt->object[rt->nb_object] = (t_type *)sp;
	rt->nb_object += 1;
	sp->radius = sp->diameter / 2;
	return (0);
}

int	get_cylinder_info(char **tok, t_rt *rt)
{
	t_cy	*cy;

	cy = malloc(sizeof(t_cy));
	cy->type = CYLINDER;
	if (fill_vec(tok[1], &cy->center))
		return (1);
	if (fill_vec(tok[2], &cy->axis_n))
		return (1);
	if (!tok[3])
		return (1);
	cy->diameter = atof(tok[3]);
	if (!tok[4])
		return (1);
	cy->height = atof(tok[4]);
	if (fill_rgb(tok[5], &cy->color))
		return (1);
	cy->color = color_mul(cy->color, (t_rgb){255, 255, 255, 1});
	rt->object[rt->nb_object] = (t_type *)cy;
	rt->nb_object += 1;
	cy->semi_height = cy->height / 2;
	cy->radius = cy->diameter / 2;
	cy->axis_n = get_normalized_vec(cy->axis_n);
	cy->top = get_point(cy->center, cy->axis_n, cy->semi_height);
	cy->dt = -dot_prod(cy->top, cy->axis_n);
	cy->bottom = get_point(cy->center, vec_mul(cy->axis_n, -1), cy->semi_height);
	cy->db = -dot_prod(cy->bottom, cy->axis_n);
	return (0);
}

int	get_plane_info(char **tok, t_rt *rt)
{
	t_pl	*pl;

	pl = malloc(sizeof(t_pl));
	pl->type = PLANE;
	if (fill_vec(tok[1], &pl->point))
		return (1);
	if (fill_vec(tok[2], &pl->normal_n))
		return (1);
	if (fill_rgb(tok[3], &pl->color))
		return (1);
	pl->color = color_mul(pl->color, (t_rgb){255, 255, 255, 1});
	rt->object[rt->nb_object] = (t_type *)pl;
	rt->nb_object += 1;
	pl->normal_n = get_normalized_vec(pl->normal_n);
	pl->d = -dot_prod(pl->point, pl->normal_n);
	return (0);
}
