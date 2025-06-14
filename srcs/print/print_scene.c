/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:46:08 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/14 14:12:41 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "utils.h"
	/*printf("light =======\nposition   :%f,%f,%f\nbrightness :%f\n",*/
	/*	rt->light.position.x, rt->light.position.y, rt->light.position.z, rt->light.brightness);*/
	/*printf("ambient =======\nlightning  :%f\ncolor      :%d,%d,%d\n",*/
	/*	rt->ambiant.lighting, rt->ambiant.color.r, rt->ambiant.color.g, rt->ambiant.color.b);*/

void	print_solids(t_rt *rt)
{
	if (rt->menu.obj == 0)
	{
		printf("camera =======\nposition   :%f,%f,%f\ndirection  :%f,%f,%f\nfov        :%f\n",
			rt->camera.position.x, rt->camera.position.y, rt->camera.position.z,
			rt->camera.direction.x, rt->camera.direction.y, rt->camera.direction.z,
			rt->camera.fov);
	}
	else
	{
		if (*rt->object[rt->menu.obj - 1] == PLANE)
		{
			printf("plane =======\npoint      :%f,%f,%f\nnormal_v   :%f,%f,%f\ncolor      :%d,%d,%d\n",
				((t_plane *)rt->object[rt->menu.obj - 1])->point.x, ((t_plane *)rt->object[rt->menu.obj - 1])->point.y,
				((t_plane *)rt->object[rt->menu.obj - 1])->point.z,
				((t_plane *)rt->object[rt->menu.obj - 1])->normal.x,((t_plane *)rt->object[rt->menu.obj - 1])->normal.y,
				((t_plane *)rt->object[rt->menu.obj - 1])->normal.z,
				((t_plane *)rt->object[rt->menu.obj - 1])->color.r, ((t_plane *)rt->object[rt->menu.obj - 1])->color.g,
				((t_plane *)rt->object[rt->menu.obj - 1])->color.b);
		}
		if (*rt->object[rt->menu.obj - 1] == SPHERE)
		{
			printf("sphere =======\npoint      :%f,%f,%f\ndiameter   :%f\ncolor      :%d,%d,%d\n",
				((t_sphere *)rt->object[rt->menu.obj - 1])->center.x,((t_sphere *)rt->object[rt->menu.obj - 1])->center.y,
				((t_sphere *)rt->object[rt->menu.obj - 1])->center.z,
				((t_sphere *)rt->object[rt->menu.obj - 1])->diameter,
				((t_sphere *)rt->object[rt->menu.obj - 1])->color.r, ((t_sphere *)rt->object[rt->menu.obj - 1])->color.g,
				((t_sphere *)rt->object[rt->menu.obj - 1])->color.b);
		}
		if (*rt->object[rt->menu.obj - 1] == CYLINDER)
		{
			printf("cylinder =======\ncenter     :%f,%f,%f\naxis       :%f,%f,%f\ndiameter   :%f\nheight     :%f\ncolor      :%d,%d,%d\n",
				((t_cylinder *)rt->object[rt->menu.obj - 1])->center.x,((t_cylinder *)rt->object[rt->menu.obj - 1])->center.y,
				((t_cylinder *)rt->object[rt->menu.obj - 1])->center.z,
				((t_cylinder *)rt->object[rt->menu.obj - 1])->axis.x,((t_cylinder *)rt->object[rt->menu.obj - 1])->axis.y,
				((t_cylinder *)rt->object[rt->menu.obj - 1])->axis.z,
				((t_cylinder *)rt->object[rt->menu.obj - 1])->diameter,((t_cylinder *)rt->object[rt->menu.obj - 1])->height,
				((t_cylinder *)rt->object[rt->menu.obj - 1])->color.r, ((t_cylinder *)rt->object[rt->menu.obj - 1])->color.g,
				((t_cylinder *)rt->object[rt->menu.obj - 1])->color.b);
		}
	}
}

void	print_cam_base(t_rt *rt)
{
	printf("cam_base =======\npixel_x     :%f,%f,%f\npixel_y       :%f,%f,%f\nstart   :%f,%f,%f\n",
			rt->c_base.pixel_x.x, rt->c_base.pixel_x.y, rt->c_base.pixel_x.z,
			rt->c_base.pixel_y.x, rt->c_base.pixel_y.y, rt->c_base.pixel_y.z,
			rt->c_base.start.x, rt->c_base.start.y, rt->c_base.start.z);

}
