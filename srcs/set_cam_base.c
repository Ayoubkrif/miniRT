/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cam_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:00:46 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/16 21:12:40 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include <stdlib.h>
#include "vect.h"

void	set_cam_base(t_cam *cam)
{
	cam->direction = get_normalized_vec(cam->direction);
	// assert(vec_norm(cam->direction));
	cam->base.h_normal = vec_prod(cam->direction, vec(0, 0, 1));
	// assert((vec_norm(cam->base.h_normal)));
	cam->base.v_normal = vec_prod(cam->base.h_normal, cam->direction);
	cam->screen.center = get_point(cam->position, cam->direction, 1);
	cam->screen.pix_x = get_point(vec(0, 0, 0), cam->base.h_normal,
			tan(to_rad(cam->fov / 2)) / 960);
	cam->screen.pix_y = get_point(vec(0, 0, 0), cam->base.v_normal,
			vec_norm(cam->screen.pix_x));
	// assert(vec_norm(cam->screen.pix_y) == vec_norm(cam->screen.pix_x) || 1);
}
