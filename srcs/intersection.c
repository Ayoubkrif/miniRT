/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:01:11 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/12 15:04:46 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "libft.h"
#include "vect.h"
#include <assert.h>
#include <stdio.h>

void	push_inter(t_rt *rt, t_vect ray, t_inter *inter, t_rgb color, double t)
{
	int	i;

	i = 0;
	while (inter[i].init)
		i++;
	printf("%d\n", i);
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
	a = dot_prod(ray, ray);
	assert(a != 0);
	b = 2 * dot_prod(ray, vec_sub(camera, sp->center));
	c = p2(vec_norm(vec_sub(camera, sp->center))) - p2(sp->diameter / 2);
	delta = delta_2nd(a, b, c);
	// printf("ray is %f, %f, %f\n", ray.x, ray.y, ray.z);
	// printf("camera is %f, %f, %f\n", camera.x, camera.y, camera.z);
	// printf("center is %f, %f, %f\n", sp->center.x, sp->center.y, sp->center.z);
	// printf("a = %f, b = %f, c = %f, d = %f\n", a, b, c, delta);
	if (delta <= 0)
		return ;
	push_inter(rt, ray, inter, sp->color, (-b + sqrt(delta)) / (2 * a));
	push_inter(rt, ray, inter, sp->color, (-b - sqrt(delta)) / (2 * a));
}

void	inter_cylinder(t_rt *rt, t_vect ray, t_inter *inter, t_cylinder *cy)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vect	camera;
	t_vect	ortho_ray;
	t_vect	ortho_cam_center;

	camera = rt->camera.position;
	ortho_ray = vec_sub(ray, vec_mul(cy->axis, dot_prod(ray, cy->axis)));
	ortho_cam_center = vec_sub(camera, cy->center);
	ortho_cam_center = vec_sub(ortho_cam_center, vec_mul(cy->axis, dot_prod(ortho_cam_center, cy->axis)));

	a = dot_prod(ortho_ray, ortho_ray);
	assert(a != 0);
	b = 2 *  dot_prod(ortho_cam_center, ortho_ray);
	c = dot_prod(ortho_cam_center, ortho_cam_center) - p2(cy->diameter / 2);
	delta = delta_2nd(a, b, c);
	if (delta <= 0)
		return ;
	if (dot_prod(cy->axis, vec_sub(camera, get_point_d(camera, ray, -b + sqrt(delta) / (2 * a)))) <= cy->height / 2)
		push_inter(rt, ray, inter, cy->color, (-b + sqrt(delta)) / (2 * a));
	if (dot_prod(cy->axis, vec_sub(camera, get_point_d(camera, ray, -b - sqrt(delta) / (2 * a)))) <= cy->height / 2)
		push_inter(rt, ray, inter, cy->color, (-b - sqrt(delta)) / (2 * a));
}

void	inter_plane(t_rt *rt, t_vect ray, t_inter *inter, t_plane *pl)
{
	(void)rt, (void)ray, (void)inter, (void)pl;
	printf("je suis une fonction qui ne fait rien\n");
}
