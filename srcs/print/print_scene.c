/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:46:08 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/03 10:07:36 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "utils.h"

void	print_solids(t_rt *rt)
{
	(void)rt;
	printf("light =======\nposition   :%f,%f,%f\nbrightness :%f\ncolor    :%f%f%f\n",
		rt->light[0].position.x, rt->light[0].position.y, rt->light[0].position.z, rt->light[0].color.brightness
		, rt->light[0].color.r * 255, rt->light[0].color.g * 255, rt->light[0].color.b * 255);
	printf("light =======\nposition   :%f,%f,%f\nbrightness :%f\ncolor    :%f%f%f\n",
		rt->light[1].position.x, rt->light[1].position.y, rt->light[1].position.z, rt->light[1].color.brightness
		, rt->light[1].color.r * 255, rt->light[1].color.g * 255, rt->light[1].color.b * 255);
	// printf("ambient =======\nlightning  :%f\ncolor      :%.f,%.f,%.f\n",
	// 	rt->ambiant.color.brightness, rt->ambiant.color.r * 255, rt->ambiant.color.g * 255, rt->ambiant.color.b * 255);
	// if (rt->menu == 0)
	// {
	// 	printf("camera =======\nposition   :%f,%f,%f\ndirection  :%f,%f,%f\nfov        :%f\n",
	// 		rt->camera.position.x, rt->camera.position.y, rt->camera.position.z,
	// 		rt->camera.direction_n.x, rt->camera.direction_n.y, rt->camera.direction_n.z,
	// 		rt->camera.fov);
	// }
/*	else
	{
		if (*rt->object[rt->menu.obj - 1] == PLANE)
		{
			printf("plane =======\npoint      :%f,%f,%f\nnormal_v   :%f,%f,%f\ncolor      :%d,%d,%d\n",
				((t_pl *)rt->object[rt->menu.obj - 1])->point.x, ((t_pl *)rt->object[rt->menu.obj - 1])->point.y,
				((t_pl *)rt->object[rt->menu.obj - 1])->point.z,
				((t_pl *)rt->object[rt->menu.obj - 1])->normal.x,((t_pl *)rt->object[rt->menu.obj - 1])->normal.y,
				((t_pl *)rt->object[rt->menu.obj - 1])->normal.z,
				((t_pl *)rt->object[rt->menu.obj - 1])->color.r, ((t_pl *)rt->object[rt->menu.obj - 1])->color.g,
				((t_pl *)rt->object[rt->menu.obj - 1])->color.b);
		}
		if (*rt->object[rt->menu.obj - 1] == SPHERE)
		{
			printf("sphere =======\npoint      :%f,%f,%f\ndiameter   :%f\ncolor      :%d,%d,%d\n",
				((t_sp *)rt->object[rt->menu.obj - 1])->center.x,((t_sp *)rt->object[rt->menu.obj - 1])->center.y,
				((t_sp *)rt->object[rt->menu.obj - 1])->center.z,
				((t_sp *)rt->object[rt->menu.obj - 1])->diameter,
				((t_sp *)rt->object[rt->menu.obj - 1])->color.r, ((t_sp *)rt->object[rt->menu.obj - 1])->color.g,
				((t_sp *)rt->object[rt->menu.obj - 1])->color.b);
		}
		if (*rt->object[rt->menu.obj - 1] == CYLINDER)
		{
			printf("cylinder =======\ncenter     :%f,%f,%f\naxis       :%f,%f,%f\ndiameter   :%f\nheight     :%f\ncolor      :%d,%d,%d\n",
				((t_cy *)rt->object[rt->menu.obj - 1])->center.x,((t_cy *)rt->object[rt->menu.obj - 1])->center.y,
				((t_cy *)rt->object[rt->menu.obj - 1])->center.z,
				((t_cy *)rt->object[rt->menu.obj - 1])->axis.x,((t_cy *)rt->object[rt->menu.obj - 1])->axis.y,
				((t_cy *)rt->object[rt->menu.obj - 1])->axis.z,
				((t_cy *)rt->object[rt->menu.obj - 1])->diameter,((t_cy *)rt->object[rt->menu.obj - 1])->height,
				((t_cy *)rt->object[rt->menu.obj - 1])->color.r, ((t_cy *)rt->object[rt->menu.obj - 1])->color.g,
				((t_cy *)rt->object[rt->menu.obj - 1])->color.b);
		}
	}*/
}

void	print_cam_base(t_rt *rt)
{
	t_cam	*cam;

	cam = &rt->camera;
	printf("cam_base =======\npixel_x     :%f,%f,%f\npixel_y       :%f,%f,%f\nstart   :%f,%f,%f\n",
			cam->screen.pix_x.x, cam->screen.pix_x.y, cam->screen.pix_x.z,
			cam->screen.pix_y.x, cam->screen.pix_y.y, cam->screen.pix_y.z,
			cam->screen.center.x, cam->screen.center.y, cam->screen.center.z);

}
