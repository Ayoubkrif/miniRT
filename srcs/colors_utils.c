/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 07:58:52 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/03 11:30:27 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb	color_mul(t_rgb	c1, t_rgb c2)
{
	return ((t_rgb)
		{
			c1.r * c2.r,
			c1.g * c2.g,
			c1.b * c2.b,
			c1.brightness * c2.brightness
		});
}

t_rgb	color_add(t_rgb	c1, t_rgb c2)
{
	return ((t_rgb)
		{
			(c1.r * c1.brightness) + (c2.r * c2.brightness),
			(c1.g * c1.brightness) + (c2.g * c2.brightness),
			(c1.b * c1.brightness) + (c2.b * c2.brightness),
			1
		});
}
