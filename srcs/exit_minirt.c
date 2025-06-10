/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:13:31 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/10 13:22:41 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "miniRT.h"
#include "mlx.h"
#include "vect.h"
#include "utils.h"

int	exit_minirt(t_rt *rt)
{
	free_rt(rt);
	mlx_destroy_image(rt->mlx.disp, rt->mlx.img);
	mlx_destroy_window(rt->mlx.disp, rt->mlx.win);
	mlx_destroy_display(rt->mlx.disp);
	free(rt->mlx.disp);
	exit(0);
}
