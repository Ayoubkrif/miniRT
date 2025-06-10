/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:08:05 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/10 19:25:52 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "mlx.h"
#include "define.h"
#include "math_utils.h"
#include <stdio.h>
#include <math.h>

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

void	set_cam_base(t_rt *rt)
{
	rt->c_base.h_dir = vec_prod(rt->camera.direction, vec(0, 0, 1));
	rt->c_base.v_dir = vec_prod(rt->camera.direction, rt->c_base.h_dir);
	rt->c_base.start = get_point(rt->camera.position, rt->camera.direction, 1);
	rt->c_base.pixel_x = get_point(vec(0, 0, 0), rt->c_base.h_dir, tan(to_rad(45)) / 960);
	rt->c_base.pixel_y = get_point(vec(0, 0, 0), rt->c_base.v_dir, vec_norm(rt->c_base.pixel_x));
}

void	set_cam_obj(t_rt *rt)
{
	static int	dup = 0;

	if (!dup)
	{
		alloc_camera_scene(rt->object, rt->cam_obj);
		dup++;
	}
	set_cam_base(rt);
}

int	main(int ac, char *av[])
{
	t_rt	rt;

	check_args(ac);
	rt.nb_object = 0;
	init_mini_rt(&rt, av);
	print_solids(&rt);
	set_cam_obj(&rt);
	print_cam_base(&rt);
	mlx_hook(rt.mlx.win, EVENT_KEY_PRESS, 1L << 0, key_hook, &rt);
	mlx_hook(rt.mlx.win, EVENT_DESTROY, 1L << 0, exit_minirt, &rt);
	mlx_loop(rt.mlx.disp);
	return (0);
}
