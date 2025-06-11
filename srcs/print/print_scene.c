/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:46:08 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/10 18:50:24 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "utils.h"

void	print_solids(t_rt *rt)
{
	int		i;

	i = 0;
	printf("camera =======\nposition   :%f,%f,%f\ndirection  :%f,%f,%f\nfov        :%f\n",
		rt->camera.position.x, rt->camera.position.y, rt->camera.position.z,
		rt->camera.direction.x, rt->camera.direction.y, rt->camera.direction.z,
		rt->camera.fov);
	printf("light =======\nposition   :%f,%f,%f\nbrightness :%f\n",
		rt->light.position.x, rt->light.position.y, rt->light.position.z, rt->light.brightness);
	printf("ambient =======\nlightning  :%f\ncolor      :%d,%d,%d\n",
		rt->ambiant.lighting, rt->ambiant.color.x, rt->ambiant.color.y, rt->ambiant.color.z);
	while (rt->object[i])
	{
		if (*rt->object[i] == PLANE)
		{
			printf("plane =======\npoint      :%f,%f,%f\nnormal_v   :%f,%f,%f\ncolor      :%d,%d,%d\n",
				((t_plane *)rt->object[i])->point.x, ((t_plane *)rt->object[i])->point.y,
				((t_plane *)rt->object[i])->point.z,
				((t_plane *)rt->object[i])->normal_v.x,((t_plane *)rt->object[i])->normal_v.y,
				((t_plane *)rt->object[i])->normal_v.z,
				((t_plane *)rt->object[i])->color.x, ((t_plane *)rt->object[i])->color.y,
				((t_plane *)rt->object[i])->color.z);
		}
		if (*rt->object[i] == SPHERE)
		{
			printf("sphere =======\npoint      :%f,%f,%f\ndiameter   :%f\ncolor      :%d,%d,%d\n",
				((t_sphere *)rt->object[i])->center.x,((t_sphere *)rt->object[i])->center.y,
				((t_sphere *)rt->object[i])->center.z,
				((t_sphere *)rt->object[i])->diameter,
				((t_sphere *)rt->object[i])->color.x, ((t_sphere *)rt->object[i])->color.y,
				((t_sphere *)rt->object[i])->color.z);
		}
		if (*rt->object[i] == CYLINDER)
		{
			printf("cylinder =======\ncenter     :%f,%f,%f\naxis       :%f,%f,%f\ndiameter   :%f\nheight     :%f\ncolor      :%d,%d,%d\n",
				((t_cylinder *)rt->object[i])->center.x,((t_cylinder *)rt->object[i])->center.y,
				((t_cylinder *)rt->object[i])->center.z,
				((t_cylinder *)rt->object[i])->axis.x,((t_cylinder *)rt->object[i])->axis.y,
				((t_cylinder *)rt->object[i])->axis.z,
				((t_cylinder *)rt->object[i])->diameter,((t_cylinder *)rt->object[i])->height,
				((t_cylinder *)rt->object[i])->color.x, ((t_cylinder *)rt->object[i])->color.y,
				((t_cylinder *)rt->object[i])->color.z);
		}
		i++;
	}
}

void	print_cam_base(t_rt *rt)
{
	printf("cam_base =======\npixel_x     :%f,%f,%f\npixel_y       :%f,%f,%f\nstart   :%f,%f,%f\n",
			rt->c_base.pixel_x.x, rt->c_base.pixel_x.y, rt->c_base.pixel_x.z,
			rt->c_base.pixel_y.x, rt->c_base.pixel_y.y, rt->c_base.pixel_y.z,
			rt->c_base.start.x, rt->c_base.start.y, rt->c_base.start.z);

}
