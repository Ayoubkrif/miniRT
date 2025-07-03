/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:01:20 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/03 09:49:17 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include <string.h>
#include <stdio.h>

void ftoa(float n, char* res, int afterpoint);

void	put_cam(t_rt *rt)
{
	char res[10];

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 160, WIN_Y - 20, 0xFFFFFF, " camera");
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 230, WIN_Y - 20, 0xFFFFFF, " position :");
	ftoa(rt->camera.position.x, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 300, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(rt->camera.position.y, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 350, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(rt->camera.position.z, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 400, WIN_Y - 20, 0xFFFFFF, res);
}

// void	put_light(t_rt *rt)
// {
//
// }

void	put_sp(t_rt *rt)
{
	char res[10];

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 160, WIN_Y - 20, 0xFFFFFF, " sphere");

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 230, WIN_Y - 20, 0xFFFFFF, " center :");
	ftoa(((t_sp *)rt->object[rt->menu - 1])->center.x, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 300, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_sp *)rt->object[rt->menu - 1])->center.y, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 350, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_sp *)rt->object[rt->menu - 1])->center.z, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 400, WIN_Y - 20, 0xFFFFFF, res);
}

void	put_pl(t_rt *rt)
{
	char res[10];

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 160, WIN_Y - 20, 0xFFFFFF, " plane");

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 230, WIN_Y - 20, 0xFFFFFF, " point :");
	ftoa(((t_pl *)rt->object[rt->menu - 1])->point.x, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 300, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_pl *)rt->object[rt->menu - 1])->point.y, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 350, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_pl *)rt->object[rt->menu - 1])->point.z, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 400, WIN_Y - 20, 0xFFFFFF, res);

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 500, WIN_Y - 20, 0xFFFFFF, " normal :");
	ftoa(((t_pl *)rt->object[rt->menu - 1])->normal_n.x, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 580, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_pl *)rt->object[rt->menu - 1])->normal_n.y, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 630, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_pl *)rt->object[rt->menu - 1])->normal_n.z, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 680, WIN_Y - 20, 0xFFFFFF, res);
}

void	put_cy(t_rt *rt)
{
	char res[10];

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 160, WIN_Y - 20, 0xFFFFFF, " cylinder");
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 230, WIN_Y - 20, 0xFFFFFF, " center :");
	ftoa(((t_cy *)rt->object[rt->menu - 1])->center.x, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 300, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_cy *)rt->object[rt->menu - 1])->center.y, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 350, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_cy *)rt->object[rt->menu - 1])->center.z, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 400, WIN_Y - 20, 0xFFFFFF, res);
}

void	put_string(t_rt *rt)
{
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 50, WIN_Y - 20, 0xFFFFFF, " selected object :");
	if (rt->menu == 0)
		put_cam(rt);
	else
	{
		if (*rt->object[rt->menu - 1] == PLANE)
			put_pl(rt);
		if (*rt->object[rt->menu - 1] == SPHERE)
			put_sp(rt);
		if (*rt->object[rt->menu - 1] == CYLINDER)
			put_cy(rt);
	}
}
