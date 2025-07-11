/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:31:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/11 11:53:54 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb	get_sp_checkerboard(t_vect point, t_sp *sp)
{
	int	theta;
	int	phi;
	t_vect	p;

	p = vec_sub(point, sp->center);
	phi = (int)floor(10 * atan(p.x / p.y) / (PI));
	theta = (int)floor(10 * acos(p.z / sp->radius) / (PI));
	if ((theta + phi) % 2)
		return ((t_rgb){0, 0, 0});
	else
		return ((t_rgb){255, 255, 255});
}
