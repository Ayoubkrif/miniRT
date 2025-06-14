/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:00:10 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/14 07:39:29 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_X && y >= 0 && y < WIN_Y)
	{
		dst = rt->mlx.addr + (y * rt->mlx.line_length
				+ x * (rt->mlx.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_a_pixel(t_rt *rt, int x, int y, t_rgb color)
{
	my_mlx_pixel_put(rt, x, y,
		((color.r << 16))
		| ((color.g << 8))
		| (color.b));
}
