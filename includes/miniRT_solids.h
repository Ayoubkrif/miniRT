/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_solids.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:23:03 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/13 12:42:45 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_SOLIDS_H
# define MINIRT_SOLIDS_H

# include "math_utils.h"

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
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
	DISK_BOT,
	DISK
}	t_type;

typedef struct s_sp
{
	t_type	type;
	t_vect	center;
	float	diameter;
	t_rgb	color;
	float	reflexion;
	int		map;

	float	radius;
}	t_sp;

typedef struct s_pl
{
	t_type	type;
	t_vect	point;
	t_vect	normal_n;
	t_base	base;
	t_rgb	color;
	float	reflexion;
	int		map;

	double	d;
}	t_pl;

typedef struct s_cy
{
	t_type	type;
	t_vect	center;
	t_vect	axis_n;
	float	diameter;
	float	height;
	t_rgb	color;
	float	reflexion;
	int		map;

	t_base	base;
	float	radius;
	float	semi_height;
	t_vect	top;
	t_vect	bottom;
	double	dt;
	double	db;
	t_vect	topdi;
	t_vect	bottomdi;
}	t_cy;

typedef struct s_di
{
	t_type	type;
	t_vect	center;
	t_vect	normal_n;
	float	diameter;
	t_rgb	color;
	float	reflexion;
	int		map;

	t_base	base;
	float	radius;
	double	d;
}	t_di;

typedef struct s_co
{
	t_type	type;
	t_vect	center;
	t_vect	axis_n;
	float	diameter;
	float	height;
	t_rgb	color;
	float	reflexion;
	int		map;

	t_vect	apex;
	float	radius;
	float	theta;
	float	gamma;
}	t_co;

#endif
