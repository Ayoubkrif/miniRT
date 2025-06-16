/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:00:10 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/16 20:56:23 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <assert.h>

void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color)
{
	char	*dst;

	assert(x >= 0 && x < WIN_X && y >= 0 && y < WIN_Y);
	if (x >= 0 && x < WIN_X && y >= 0 && y < WIN_Y)
	{
		dst = rt->mlx.addr + (y * rt->mlx.line_length
				+ x * (rt->mlx.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_a_pixel(t_rt *rt, int x, int y, t_rgb color)
{
	int	final_color;

	final_color = (((int)(color.r * 255) << 16))
		| (((int)(color.g * 255) << 8))
		| ((int)(color.b * 255));
	my_mlx_pixel_put(rt, x, y, final_color);
}
