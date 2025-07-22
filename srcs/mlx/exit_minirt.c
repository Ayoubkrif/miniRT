/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:13:31 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/22 09:59:30 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"

int	exit_minirt(t_rt *rt, int code)
{
	free_rt(rt);
	mlx_destroy_image(rt->mlx.disp, rt->mlx.img);
	mlx_destroy_window(rt->mlx.disp, rt->mlx.win);
	mlx_destroy_display(rt->mlx.disp);
	free(rt->mlx.disp);
	exit(code);
}
