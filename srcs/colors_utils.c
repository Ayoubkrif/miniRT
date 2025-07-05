/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 07:58:52 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/05 09:37:15 by aykrifa          ###   ########.fr       */
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
