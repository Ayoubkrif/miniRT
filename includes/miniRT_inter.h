/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_inter.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:23:31 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/17 09:02:56 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_INTER_H
# define MINIRT_INTER_H

# include "miniRT_type.h"

typedef struct s_inter
{
	t_obj	*obj;
	double	t;
	t_type	mode;
}	t_inter;

void	window_cast(t_rt *rt);
t_inter	nearest_inter(t_rt *rt, t_vect ray, t_vect	start);

void	inter_sphere(t_vect ray, t_sp *sp, t_inter *inter, t_vect start);
void	inter_cylinder(t_vect ray, t_cy*cy, t_inter *inter, t_vect start);
void	inter_disk(t_vect ray, t_cy *cy, t_inter *inter, t_vect start);
void	inter_plane(t_vect ray, t_pl *pl, t_inter *inter, t_vect start);
void	inter_cone(t_vect ray, t_co *co, t_inter *inter, t_vect start);
#endif
