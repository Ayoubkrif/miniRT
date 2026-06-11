/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:32:51 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/23 14:38:58 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"

void	ftoa(float n, char *res, int afterpoint);

void	put_sp(t_rt *rt)
{
	char	res[10];

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 160, WIN_Y - 20, 0xFFFFFF,
		" sphere");
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 230, WIN_Y - 20, 0xFFFFFF,
		" center :");
	ftoa(((t_sp *)rt->object[rt->menu - 1])->center.x, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 300, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_sp *)rt->object[rt->menu - 1])->center.y, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 350, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_sp *)rt->object[rt->menu - 1])->center.z, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 400, WIN_Y - 20, 0xFFFFFF, res);
}

void	put_pl(t_rt *rt)
{
	char	res[10];

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 160, WIN_Y - 20, 0xFFFFFF,
		" plane");
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 230, WIN_Y - 20, 0xFFFFFF,
		" point :");
	ftoa(((t_pl *)rt->object[rt->menu - 1])->point.x, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 300, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_pl *)rt->object[rt->menu - 1])->point.y, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 350, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_pl *)rt->object[rt->menu - 1])->point.z, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 400, WIN_Y - 20, 0xFFFFFF, res);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 500, WIN_Y - 20, 0xFFFFFF,
		" normal :");
	ftoa(((t_pl *)rt->object[rt->menu - 1])->normal_n.x, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 580, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_pl *)rt->object[rt->menu - 1])->normal_n.y, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 630, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_pl *)rt->object[rt->menu - 1])->normal_n.z, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 680, WIN_Y - 20, 0xFFFFFF, res);
}

void	put_cy(t_rt *rt)
{
	char	res[10];

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 160, WIN_Y - 20, 0xFFFFFF,
		" cylinder");
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 230, WIN_Y - 20, 0xFFFFFF,
		" center :");
	ftoa(((t_cy *)rt->object[rt->menu - 1])->center.x, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 300, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_cy *)rt->object[rt->menu - 1])->center.y, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 350, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_cy *)rt->object[rt->menu - 1])->center.z, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 400, WIN_Y - 20, 0xFFFFFF, res);
}

void	put_co(t_rt *rt)
{
	char	res[10];

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 160, WIN_Y - 20, 0xFFFFFF,
		" cone");
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 230, WIN_Y - 20, 0xFFFFFF,
		" apex :");
	ftoa(((t_co *)rt->object[rt->menu - 1])->apex.x, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 300, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_co *)rt->object[rt->menu - 1])->apex.y, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 350, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(((t_co *)rt->object[rt->menu - 1])->apex.z, res, 1);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 400, WIN_Y - 20, 0xFFFFFF, res);
}
