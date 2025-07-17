/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:01:20 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/17 09:33:37 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"

void	put_sp(t_rt *rt);
void	put_pl(t_rt *rt);
void	put_cy(t_rt *rt);
void	put_co(t_rt *rt);
void	ftoa(float n, char *res, int afterpoint);

void	put_cam(t_rt *rt)
{
	char	res[10];

	mlx_string_put(rt->mlx.disp, rt->mlx.win, 160, WIN_Y - 20, 0xFFFFFF,
		" camera");
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 230, WIN_Y - 20, 0xFFFFFF,
		" position :");
	ftoa(rt->camera.position.x, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 300, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(rt->camera.position.y, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 350, WIN_Y - 20, 0xFFFFFF, res);
	ftoa(rt->camera.position.z, res, 4);
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 400, WIN_Y - 20, 0xFFFFFF, res);
}

void	put_string(t_rt *rt)
{
	mlx_string_put(rt->mlx.disp, rt->mlx.win, 50, WIN_Y - 20, 0xFFFFFF,
		" selected object :");
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
		if (*rt->object[rt->menu - 1] == CONE)
			put_co(rt);
	}
}

// void	put_light(t_rt *rt)
// {
//
// }
