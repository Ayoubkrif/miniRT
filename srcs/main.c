/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:08:05 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/10 13:22:28 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
// #include "mlx_int.h"
#include "mlx.h"
#include "vect.h"
#include "utils.h"
#include "define.h"
#include <stdio.h>

void	get_scene_info(t_rt *rt, char **av);

void	init_mini_rt(t_rt *rt, char **av)
{
	ft_memset(rt, 0, sizeof(t_rt));
	get_scene_info(rt, av);
	rt->mlx.disp = mlx_init();
	if (!rt->mlx.disp)
		(printf("init failed\n"), exit(1));
	rt->mlx.win = mlx_new_window(rt->mlx.disp, 1920, 1080, "MiniRT");
	if (!rt->mlx.win)
		(printf("win failed\n"), exit(1));
	rt->mlx.img = mlx_new_image(rt->mlx.disp, 1920, 1080);
	if (!rt->mlx.img)
		(printf("img failed\n"), exit(1));
	// rt->mlx.addr = mlx_get_data_addr(rt->mlx.img,
	// 		&rt->mlx.bits_per_pixel, &rt->mlx.line_lenght, &rt->mlx.endian);
}

void	free_rt(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->nb_object)
	{
		free(rt->object[i]);
		i++;
	}
}

void	alloc_camera_scene(t_type *obj[], t_type *to_dup[])
{
	int	i;

	i = 0;
	while (obj[i])
	{
		if (*obj[i] == PLANE)
			to_dup[i] = malloc(sizeof(t_plane));
		if (*obj[i] == SPHERE)
			to_dup[i] = malloc(sizeof(t_sphere));
		if (*obj[i] == CYLINDER)
			to_dup[i] = malloc(sizeof(t_cylinder));
		i++;
	}
}

void	set_cam_obj(t_rt *rt)
{
	static int	dup = 0;

	if (!dup)
	{
		alloc_camera_scene(rt->object, rt->cam_obj);
		dup++;
	}
}

int	main(int ac, char *av[])
{
	t_rt	rt;

	check_args(ac);
	rt.nb_object = 0;
	init_mini_rt(&rt, av);
	printf("camera =======\nposition   :%f,%f,%f\ndirection  :%f,%f,%f\nfov        :%f\n",
		rt.camera.position.x, rt.camera.position.y, rt.camera.position.z,
		rt.camera.direction.x, rt.camera.direction.y, rt.camera.direction.z,
		rt.camera.fov);
	printf("light =======\nposition   :%f,%f,%f\nbrightness :%f\n",
		rt.light.position.x, rt.light.position.y, rt.light.position.z, rt.light.brightness);
	printf("ambient =======\nlightning  :%f\ncolor      :%d,%d,%d\n",
		rt.ambiant.lighting, rt.ambiant.color.x, rt.ambiant.color.y, rt.ambiant.color.z);
	int		i;

	i = 0;
	while (rt.object[i])
	{
		if (*rt.object[i] == PLANE)
		{
			printf("plane =======\npoint      :%f,%f,%f\nnormal_v   :%f,%f,%f\ncolor      :%d,%d,%d\n",
				((t_plane *)rt.object[i])->point.x, ((t_plane *)rt.object[i])->point.y,
				((t_plane *)rt.object[i])->point.z,
				((t_plane *)rt.object[i])->normal_v.x,((t_plane *)rt.object[i])->normal_v.y,
				((t_plane *)rt.object[i])->normal_v.z,
				((t_plane *)rt.object[i])->color.x, ((t_plane *)rt.object[i])->color.y,
				((t_plane *)rt.object[i])->color.z);
		}
		if (*rt.object[i] == SPHERE)
		{
			printf("sphere =======\npoint      :%f,%f,%f\ndiameter   :%f\ncolor      :%d,%d,%d\n",
				((t_sphere *)rt.object[i])->center.x,((t_sphere *)rt.object[i])->center.y,
				((t_sphere *)rt.object[i])->center.z,
				((t_sphere *)rt.object[i])->diameter,
				((t_sphere *)rt.object[i])->color.x, ((t_sphere *)rt.object[i])->color.y,
				((t_sphere *)rt.object[i])->color.z);
		}
		if (*rt.object[i] == CYLINDER)
		{
			printf("cylinder =======\ncenter     :%f,%f,%f\naxis       :%f,%f,%f\ndiameter   :%f\nheight     :%f\ncolor      :%d,%d,%d\n",
				((t_cylinder *)rt.object[i])->center.x,((t_cylinder *)rt.object[i])->center.y,
				((t_cylinder *)rt.object[i])->center.z,
				((t_cylinder *)rt.object[i])->axis.x,((t_cylinder *)rt.object[i])->axis.y,
				((t_cylinder *)rt.object[i])->axis.z,
				((t_cylinder *)rt.object[i])->diameter,((t_cylinder *)rt.object[i])->height,
				((t_cylinder *)rt.object[i])->color.x, ((t_cylinder *)rt.object[i])->color.y,
				((t_cylinder *)rt.object[i])->color.z);
		}
		i++;
	}
	set_cam_obj(&rt);
	mlx_hook(rt.mlx.win, EVENT_KEY_PRESS, 1L << 0, key_hook, &rt);
	mlx_hook(rt.mlx.win, EVENT_DESTROY, 1L << 0, exit_minirt, &rt);
	mlx_loop(rt.mlx.disp);
	// free_rt(&rt);
	return (0);
}
