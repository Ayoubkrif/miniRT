/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cam_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:00:46 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/17 15:27:26 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include <stdlib.h>
#include "vect.h"

void	set_cam_base(t_cam *cam)
{
	cam->direction_n = get_normalized_vec(cam->direction_n);
	// assert(vec_norm(cam->direction));
	cam->base.h_normal = vec_prod(cam->direction_n, vec(0, 0, 1));
	// assert((vec_norm(cam->base.h_normal)));
	cam->base.v_normal = vec_prod(cam->base.h_normal, cam->direction_n);
	cam->screen.center = get_point(cam->position, cam->direction_n, 1);
	cam->screen.pix_x = get_point(vec(0, 0, 0), cam->base.h_normal,
			tan(to_rad(cam->fov / 2)) / 960);
	cam->screen.pix_y = get_point(vec(0, 0, 0), cam->base.v_normal,
			vec_norm(cam->screen.pix_x));
	// assert(vec_norm(cam->screen.pix_y) == vec_norm(cam->screen.pix_x) || 1);
}
