/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:13:31 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/15 19:32:49 by cbordeau         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "utils.h"

int	exit_minirt(t_rt *rt)
{
	free_rt(rt);
	mlx_destroy_image(rt->mlx.disp, rt->mlx.img);
	mlx_destroy_window(rt->mlx.disp, rt->mlx.win);
	mlx_destroy_display(rt->mlx.disp);
	free(rt->mlx.disp);
	free(rt->inter);
	exit(0);
}
