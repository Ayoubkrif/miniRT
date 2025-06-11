/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:01:11 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/11 15:14:55 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "libft.h"
#include <stdio.h>

void	push_inter(t_rt *rt, t_vect ray, t_inter *inter, t_rgb color, double t)
{
	int	i;

	i = 0;
	while (inter[i].init)
		i++;
	inter[i].init = 1;
	inter[i].color = color;
	inter[i].point = get_point_d(rt->camera.position, ray, t);
}

void	inter_sphere(t_rt *rt, t_vect ray, t_inter *inter, t_sphere *sp)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vect	camera;

	camera = rt->camera.position;
	a = pow(ray.x, 2) + pow(ray.y, 2), pow(ray.z, 2);
	b = 2 * (ray.x * (camera.x - sp->center.x)
		+ ray.y * (camera.y - sp->center.y)
		+ ray.z * (camera.z - sp->center.z));
	c = pow(camera.x - sp->center.x, 2) + pow(camera.y - sp->center.y, 2)
		+ pow(camera.z - sp->center.z, 2) - pow(sp->diameter / 2, 2);
	delta = delta_2nd(a, b, c);
	if (delta <= 0)
		return ;
	push_inter(rt, ray, inter, sp->color, ((-b + sqrt(delta)) / (2 * a)));
	push_inter(rt, ray, inter, sp->color, ((-b - sqrt(delta)) / (2 * a)));
}

void	inter_cylinder(t_rt *rt, t_vect ray, t_inter *inter, t_cylinder *cy)
{
	(void)rt, (void)ray, (void)cy;
	printf("je suis une fonction qui ne fait rien\n");
}

void	inter_plane(t_rt *rt, t_vect ray, t_inter *inter, t_plane *pl)
{
	(void)rt, (void)ray, (void)pl;
	printf("je suis une fonction qui ne fait rien\n");
}
