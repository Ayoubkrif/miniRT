/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:00:10 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/15 09:39:07 by cbordeau         ###   ########.fr       */
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
	int	final_color;

	if (color.r > 255)
		color.r = 255;
	else if (color.r < 0)
		color.r = 0;
	if (color.g > 255)
		color.g = 255;
	else if (color.g < 0)
		color.g = 0;
	if (color.b > 255)
		color.b = 255;
	else if (color.b < 0)
		color.b = 0;
	final_color = (((int)(color.r) << 16))
		| (((int)(color.g) << 8))
		| ((int)(color.b));
	my_mlx_pixel_put(rt, x, y, final_color);
}
