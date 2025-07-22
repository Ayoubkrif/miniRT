/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_solids.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:23:03 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/22 11:09:08 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_SOLIDS_H
# define MINIRT_SOLIDS_H

# include "vect.h"
# include "mlx_int.h"

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

typedef struct s_texture
{
	t_img	*img;
	int		width;
	int		height;
}	t_texture;

typedef struct s_bump
{
	t_img	*img;
	int		width;
	int		height;
}	t_bump;

typedef enum e_type
{
	NONE = 0,
	CYLINDER,
	SPHERE,
	PLANE,
	CONE,
	DISK,
	DISK_BOT,
	DISK_TOP
}	t_type;

typedef struct s_obj
{
	t_type		type;
	t_vect		position;
	int			color;

	int			map;
	t_texture	texture;
	t_bump		bump;
	float		reflexion;
	float		u_offset;
	float		v_offset;
}	t_obj;

typedef struct s_sp
{
	t_type		type;
	t_vect		center;
	int			color;

	int			map;
	t_texture	texture;
	t_bump		bump;
	float		reflexion;
	float		u_offset;
	float		v_offset;

	float		diameter;

	float		radius;
}	t_sp;

typedef struct s_pl
{
	t_type		type;
	t_vect		point;
	int			color;

	int			map;
	t_texture	texture;
	t_bump		bump;
	float		reflexion;
	float		u_offset;
	float		v_offset;

	t_vect		normal_n;
	t_base		base;

	double		d;
}	t_pl;

typedef struct s_cy
{
	t_type		type;
	t_vect		center;
	int			color;

	int			map;
	t_texture	texture;
	t_bump		bump;
	float		reflexion;
	float		u_offset;
	float		v_offset;

	t_vect		axis_n;
	float		diameter;
	float		height;

	t_base		base;
	float		radius;
	float		semi_height;
	t_vect		top;
	t_vect		bottom;
	float		dt;
	float		db;
}	t_cy;

typedef struct s_co
{
	t_type		type;
	t_vect		apex;
	int			color;

	int			map;
	t_texture	texture;
	t_bump		bump;
	float		reflexion;
	float		u_offset;
	float		v_offset;

	t_vect		axis_n;
	float		diameter;
	float		height;

	t_base		base;
	float		radius;
	float		theta;
	float		gamma;
	t_vect		center;
	float		d;

}	t_co;

#endif
