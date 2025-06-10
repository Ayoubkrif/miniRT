/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:01 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/10 16:29:00 by aykrifa          ###   ########.fr       */
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
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->type = SPHERE;
	if (fill_vec(tok[1], &sphere->center))
		return (1);
	if (!tok[2])
		return (1);
	sphere->diameter = ft_atoi(tok[2]);
	if (fill_rgb(tok[3], &sphere->color))
		return (1);
	rt->object[rt->nb_object] = (t_type *)sphere;
	rt->nb_object += 1;
	return (0);
}

int	get_cylinder_info(char **tok, t_rt *rt)
{
	t_cylinder	*cylander;

	cylander = malloc(sizeof(t_cylinder));
	cylander->type = CYLINDER;
	if (fill_vec(tok[1], &cylander->center))
		return (1);
	if (fill_vec(tok[2], &cylander->axis))
		return (1);
	if (!tok[3])
		return (1);
	cylander->diameter = ft_atoi(tok[3]);
	if (!tok[4])
		return (1);
	cylander->height = ft_atoi(tok[4]);
	if (fill_rgb(tok[5], &cylander->color))
		return (1);
	rt->object[rt->nb_object] = (t_type *)cylander;
	rt->nb_object += 1;
	return (0);
}

int	get_plane_info(char **tok, t_rt *rt)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	plane->type = PLANE;
	if (fill_vec(tok[1], &plane->point))
		return (1);
	if (fill_vec(tok[2], &plane->normal_v))
		return (1);
	if (fill_rgb(tok[3], &plane->color))
		return (1);
	rt->object[rt->nb_object] = (t_type *)plane;
	rt->nb_object += 1;
	return (0);
}
