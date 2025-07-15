/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_solids.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:23:03 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/15 09:34:29 by cbordeau         ###   ########.fr       */
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

typedef struct s_texture
{
	void	*img;
	int		*width;
	int		*height;
}	t_texture;

typedef enum e_type
{
	NONE = 0,
	CYLINDER,
	SPHERE,
	PLANE,
	CONE,
	DISK_BOT,
	DISK_TOP,
	DISK
}	t_type;

typedef struct s_sp
{
	t_type		type;
	t_vect		center;
	float		diameter;
	int			color;
	float		reflexion;
	int			map;
	t_texture	texture;

	float		radius;
}	t_sp;

typedef struct s_pl
{
	t_type		type;
	t_vect		point;
	t_vect		normal_n;
	t_base		base;
	int			color;
	float		reflexion;
	int			map;
	t_texture	texture;

	double		d;
}	t_pl;

typedef struct s_cy
{
	t_type		type;
	t_vect		center;
	t_vect		axis_n;
	float		diameter;
	float		height;
	int			color;
	float		reflexion;
	int			map;
	t_texture	texture;

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
	t_vect		axis_n;
	float		diameter;
	float		height;
	int			color;
	float		reflexion;
	int			map;
	t_texture	texture;

	t_base		base;
	float		radius;
	float		theta;
	float		gamma;
	t_vect		center;
	float		d;

}	t_co;

#endif
