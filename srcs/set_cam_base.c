/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cam_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:00:46 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/18 15:26:42 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "vect.h"
#include <math.h>

void	set_cam_base(t_cam *cam)
{
	cam->screen.center = get_point_t(cam->position, cam->direction_n, 1);
	cam->screen.pix_x = get_point_t((t_vect){0, 0, 0}, cam->base.h_normal,
			tan(to_rad(cam->fov / 2)) / 960);
	cam->screen.pix_y = get_point_t((t_vect){0, 0, 0}, cam->base.v_normal,
			norm(cam->screen.pix_x));
}

void	set_base(t_base *base, t_vect direction_n)
{
	base->h_normal = cross(direction_n, (t_vect){0, 0, 1});
	if (vect_nul(&base->h_normal))
		base->h_normal = cross(direction_n, (t_vect){0, -1, 0});
	normalize_to(&base->h_normal);
	base->v_normal = cross(base->h_normal, direction_n);
}
