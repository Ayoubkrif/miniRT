/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:08:05 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/23 12:51:00 by aykrifa          ###   ########.fr       */
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
	rt->mlx.disp = mlx_init();
	if (!rt->mlx.disp)
		(printf("init failed\n"), exit(1));
	rt->mlx.win = mlx_new_window(rt->mlx.disp, WIN_X, WIN_Y, "MiniRT");
	if (!rt->mlx.win)
		(printf("win failed\n"), exit(1));
	rt->mlx.img = mlx_new_image(rt->mlx.disp, WIN_X, WIN_Y);
	if (!rt->mlx.img)
		(printf("img failed\n"), exit(1));
	get_scene_info(rt, av);
	if (!rt->n_cam)
	{
		print_error(F_CAM, NULL);
		exit_minirt(rt, 1);
	}
}

void	free_rt(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->nb_object)
	{
		if (((t_obj *)rt->object[i])->bump.img)
			mlx_destroy_image(rt->mlx.disp, ((t_obj *)rt->object[i])->bump.img);
		if (((t_obj *)rt->object[i])->texture.img)
			mlx_destroy_image(rt->mlx.disp,
				((t_obj *)rt->object[i])->texture.img);
		free(rt->object[i]);
		i++;
	}
	free(rt->asset_root);
}

int	main(int ac, char *av[])
{
	t_rt	rt;

	check_args(ac);
	ft_memset(&rt, 0, sizeof(t_rt));
	init_mini_rt(&rt, av);
	set_base(&rt.camera.base, rt.camera.direction_n);
	set_cam_base(&rt.camera);
	window_cast(&rt);
	mlx_hook(rt.mlx.win, EVENT_KEY_PRESS, 1L << 0, key_hook, &rt);
	mlx_hook(rt.mlx.win, EVENT_DESTROY, 1L << 0, exit_minirt, &rt);
	mlx_mouse_hook(rt.mlx.win, select_solid, &rt);
	mlx_loop(rt.mlx.disp);
	return (0);
}
