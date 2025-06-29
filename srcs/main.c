/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:08:05 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/29 21:55:56 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "mlx.h"
#include "define.h"
#include <stdio.h>

void	get_scene_info(t_rt *rt, char **av);

void	init_mini_rt(t_rt *rt, char **av)
{
	get_scene_info(rt, av);
	rt->mlx.disp = mlx_init();
	if (!rt->mlx.disp)
		(printf("init failed\n"), exit(1));
	rt->mlx.win = mlx_new_window(rt->mlx.disp, WIN_X, WIN_Y, "MiniRT");
	if (!rt->mlx.win)
		(printf("win failed\n"), exit(1));
	rt->mlx.img = mlx_new_image(rt->mlx.disp, WIN_X, WIN_Y);
	if (!rt->mlx.img)
		(printf("img failed\n"), exit(1));
	rt->mlx.addr = mlx_get_data_addr(rt->mlx.img, &rt->mlx.bits_per_pixel,
			&rt->mlx.line_length, &rt->mlx.endian);
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


int	select_solid(int button, int x, int y, t_rt *rt)
{
	t_vect	ray;
	t_type	*obj;
	int		i;

	if (button == 1)
	{
		if (x < WIN_X && x >= 0)
			x -= WIN_X / 2;
		else
			return (1);
		if (y < WIN_Y && y >= 0)
			y = -y + WIN_Y / 2;
		else
			return (1);
	}
	else
		return (1);
	ray = ray_from_camera_to_objects(rt->camera, x, y);
	obj = add_inter(rt, ray, rt->camera.position).obj;
	if (!obj)
		return (1);
	i = 0;
	while (rt->object[i] != obj)
		i++;
	rt->menu = i + 1;
	return (0);
}

int	main(int ac, char *av[])
{
	t_rt	rt;

	check_args(ac);
	ft_memset(&rt, 0, sizeof(t_rt));
	init_mini_rt(&rt, av);
	set_cam_base(&rt.camera);
	throwing_rays_through_the_wide_universe(&rt);
	mlx_hook(rt.mlx.win, EVENT_KEY_PRESS, 1L << 0, key_hook, &rt);
	mlx_hook(rt.mlx.win, EVENT_DESTROY, 1L << 0, exit_minirt, &rt);
	/*mlx_hook(rt.mlx.win, 4, 0, select_solid, &rt);*/
	/*mlx_hook(rt.mlx.win, EVENT_MOUSE_RELEASE, 1L << 0, select_solid, &rt);*/
	mlx_mouse_hook(rt.mlx.win, select_solid, &rt);
	mlx_loop(rt.mlx.disp);
	return (0);
}
