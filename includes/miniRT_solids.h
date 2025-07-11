/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_solids.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:23:03 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/11 11:29:40 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_SOLIDS_H
# define MINIRT_SOLIDS_H

# include "math_utils.h"

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}	t_rgb;

typedef struct s_base
{
	t_vect	h_normal;
	t_vect	v_normal;
}	t_base;

typedef enum e_type
{
	NONE = 0,
	CYLINDER,
	SPHERE,
	PLANE,
	CONE,
	DISK_TOP,
	DISK_BOT
}	t_type;

typedef struct s_sp
{
	t_type	type;
	t_vect	center;
	double	diameter;
	t_rgb	color;
	double	reflexion;

	double	radius;
}	t_sp;

typedef struct s_pl
{
	t_type	type;
	t_vect	point;
	t_vect	normal_n;
	t_rgb	color;
	double	reflexion;

	double	d;
}	t_pl;

typedef struct s_cy
{
	t_type	type;
	t_vect	center;
	t_vect	axis_n;
	double	diameter;
	double	height;
	t_rgb	color;
	double	reflexion;

	t_base	base;
	double	radius;
	double	semi_height;
	t_vect	top;
	t_vect	bottom;
	double	dt;
	double	db;
}	t_cy;

typedef struct s_co
{
	t_type	type;
	t_vect	center;
	t_vect	axis_n;
	double	diameter;
	double	height;
	t_rgb	color;
	double	reflexion;

	t_vect	apex;
	double	radius;
	double	k;
}	t_co;

#endif
