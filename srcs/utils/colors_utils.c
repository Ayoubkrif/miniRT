/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 07:58:52 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/15 10:03:06 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb	mul_rgb(int c1, t_rgb c2)
{
	return ((t_rgb)
		{
			c2.r * ((c1 >> 16) & 255),
			c2.g * ((c1 >> 8) & 255),
			c2.b * (c1 & 255),
		});
}

t_rgb	color_mul(t_rgb	c1, t_rgb c2)
{
	return ((t_rgb)
		{
			c1.r * c2.r,
			c1.g * c2.g,
			c1.b * c2.b,
		});
}

t_rgb	color_k(t_rgb	c1, float k)
{
	return ((t_rgb)
		{
			c1.r * k,
			c1.g * k,
			c1.b * k,
		});
}

t_rgb	color_add(t_rgb	c1, t_rgb c2)
{
	return ((t_rgb)
		{
			c1.r + c2.r,
			c1.g + c2.g,
			c1.b + c2.b,
		});
}
