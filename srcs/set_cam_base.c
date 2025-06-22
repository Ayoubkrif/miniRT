/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cam_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:00:46 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/22 13:27:17 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include <stdlib.h>
#include "vect.h"

void	set_cam_base(t_cam *cam)
{
	set_base(&cam->base, cam->direction_n);
	cam->screen.center = get_point(cam->position, cam->direction_n, 1);
	cam->screen.pix_x = get_point(vec(0, 0, 0), cam->base.h_normal,
			tan(to_rad(cam->fov / 2)) / 960);
	cam->screen.pix_y = get_point(vec(0, 0, 0), cam->base.v_normal,
			vec_norm(cam->screen.pix_x));
}

void	set_base(t_base *base, t_vect direction_n)
{
	direction_n = get_normalized_vec(direction_n);
	base->h_normal = vec_prod(direction_n, vec(0, 0, 1));
	base->v_normal = vec_prod(base->h_normal, direction_n);
}
