/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:08:05 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/11 17:43:20 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "mlx.h"
#include "define.h"
#include "math_utils.h"
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

int	main(int ac, char *av[])
{
	t_rt	rt;

	check_args(ac);
	rt.nb_object = 0;
	init_mini_rt(&rt, av);
	print_solids(&rt);
	set_cam_obj(&rt);
	print_cam_base(&rt);
	throwing_rays_through_the_wide_universe(&rt);
	mlx_put_image_to_window(rt.mlx.disp, rt.mlx.win, rt.mlx.img, 0, 0);
	mlx_hook(rt.mlx.win, EVENT_KEY_PRESS, 1L << 0, key_hook, &rt);
	mlx_hook(rt.mlx.win, EVENT_DESTROY, 1L << 0, exit_minirt, &rt);
	mlx_loop(rt.mlx.disp);
	return (0);
}
