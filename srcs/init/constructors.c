/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:01 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/16 13:20:12 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "miniRT.h"
#include <stdlib.h>

int	get_cam_info(char **tok, t_rt *rt)
{
	if (fill_vec(tok[1], &rt->camera.position))
		return (1);
	if (fill_vec(tok[2], &rt->camera.direction))
		return (1);
	if (!tok[3])
		return (1);
	rt->camera.fov = ft_atoi(tok[3]);
	return (0);
}

int	get_light_info(char **tok, t_rt *rt)
{
	if (fill_vec(tok[1], &rt->light.position))
		return (1);
	if (!tok[2])
		return (1);
	rt->light.brightness = ft_atoi(tok[2]);
	return (0);
}

int	get_ambient_info(char **tok, t_rt *rt)
{
	if (!tok[1])
		return (1);
	rt->ambiant.lighting = ft_atoi(tok[1]);
	if (fill_rgb(tok[2], &rt->ambiant.color))
		return (1);
	return (0);
}

int	get_sphere_info(char **tok, t_rt *rt)
{
	t_sp	*sphere;

	sphere = malloc(sizeof(t_sp));
	sphere->type = SPHERE;
	if (fill_vec(tok[1], &sphere->center))
		return (1);
	if (!tok[2])
		return (1);
	sphere->diameter = ft_atoi(tok[2]);
	sphere->radius = sphere->diameter / 2;
	if (fill_rgb(tok[3], &sphere->color))
		return (1);
	rt->object[rt->nb_object] = (t_type *)sphere;
	rt->nb_object += 1;
	return (0);
}

int	get_cylinder_info(char **tok, t_rt *rt)
{
	t_cy	*cy;

	cy = malloc(sizeof(t_cy));
	cy->type = CYLINDER;
	if (fill_vec(tok[1], &cy->center))
		return (1);
	if (fill_vec(tok[2], &cy->axis))
		return (1);
	if (!tok[3])
		return (1);
	cy->diameter = ft_atoi(tok[3]);
	cy->radius = cy->diameter / 2;
	if (!tok[4])
		return (1);
	cy->height = ft_atoi(tok[4]);
	if (fill_rgb(tok[5], &cy->color))
		return (1);
	rt->object[rt->nb_object] = (t_type *)cy;
	rt->nb_object += 1;
	cy->top = get_point(cy->center,cy->axis, cy->height / 2);
	cy->dt = -dot_prod(cy->top, cy->axis);
	cy->bottom = get_point(cy->center, vec_mul(cy->axis, -1), cy->height / 2);
	cy->db = -dot_prod(cy->bottom, cy->axis);
	return (0);
}

int	get_plane_info(char **tok, t_rt *rt)
{
	t_pl	*pl;

	pl = malloc(sizeof(t_pl));
	pl->type = PLANE;
	if (fill_vec(tok[1], &pl->point))
		return (1);
	if (fill_vec(tok[2], &pl->normal))
		return (1);
	if (fill_rgb(tok[3], &pl->color))
		return (1);
	rt->object[rt->nb_object] = (t_type *)pl;
	rt->nb_object += 1;
	pl->d = -dot_prod(pl->point, pl->normal);
	return (0);
}
