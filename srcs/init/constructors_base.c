/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:18:10 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/13 16:00:38 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "define.h"
#include <stdlib.h>

int	get_cam_info(char **tok, t_rt *rt)
{
	static int	nb = 0;

	if (nb == 1)
		return (print_error(CAM, NULL));
	else
		nb = 1;
	if (fill_vec(tok[1], &rt->camera.position))
		return (print_error(ARGS, "camera position"));
	if (fill_vec(tok[2], &rt->camera.direction_n))
		return (print_error(ARGS, "camera direction"));
	if (rt->camera.direction_n.x < -1 || rt->camera.direction_n.x > 1
		|| rt->camera.direction_n.y < -1 || rt->camera.direction_n.y > 1
		|| rt->camera.direction_n.z < -1 || rt->camera.direction_n.z > 1)
		return (print_error(VECT_NORM, "camera direction"));
	if (vect_eq(rt->camera.direction_n, vec(0, 0, 0)))
		return (print_error(VECT_NULL, "camera direction"));
	if (!tok[3])
		return (print_error(ARGS, "camera fov"));
	rt->camera.fov = ft_atoi(tok[3]);
	if (rt->camera.fov < 0 || rt->camera.fov > 180)
		return (print_error(FOV, "camera"));
	rt->camera.direction_n = normalize(rt->camera.direction_n);
	return (0);
}

int	get_light_info(char **tok, t_rt *rt)
{
	float	brightness;

	if (rt->nb_light > 20)
		return (print_error(LIGHT, NULL));
	if (fill_vec(tok[1], &rt->light[rt->nb_light].position))
		return (print_error(ARGS, "light position"));
	if (!tok[2])
		return (print_error(ARGS, "light grightness"));
	if (fill_rgb(tok[3], &rt->light[rt->nb_light].color, "light"))
		return (1);
	brightness = atof(tok[2]);
	if (brightness < 0 || brightness > 1)
		return (print_error(BRIGHTNESS, "light"));
	brightness /= 255;
	rt->light[rt->nb_light].color = color_k(rt->light[rt->nb_light].color, brightness);
	rt->nb_light += 1;
	return (0);
}

int	get_ambient_info(char **tok, t_rt *rt)
{
	static int	nb = 0;
	float		brightness;

	if (nb == 1)
		return (print_error(AMBIENT, NULL));
	else
		nb = 1;
	if (!tok[1])
		return (print_error(ARGS, "ambient color"));
	if (fill_rgb(tok[2], &rt->ambient.color, "ambient"))
		return (1);
	brightness = atof(tok[1]) * KA;
	if (brightness < 0 || brightness > 1)
		return (print_error(BRIGHTNESS, "ambient"));
	brightness /= 255;
	rt->ambient.color = color_k(rt->ambient.color, brightness);
	return (0);
}
