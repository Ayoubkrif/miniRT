/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_type.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:27:28 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/13 12:28:56 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPE_H
# define MINIRT_TYPE_H

# include "miniRT_solids.h"

typedef struct s_mlx
{
	void	*disp;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_screen
{
	t_vect	pix_x;
	t_vect	pix_y;
	t_vect	center;
}	t_screen;

typedef struct s_cam
{
	t_vect		position;
	t_vect		direction_n;
	float		fov;

	t_base		base;
	t_screen	screen;
}	t_cam;

typedef struct s_ambient
{
	t_rgb	color;
}	t_ambient;

typedef struct s_light
{
	t_vect	position;
	t_rgb	color;
}	t_light;

typedef struct s_bump
{
	void		*bump[10];
	char		*bump_name[10];
	int			nb_bump;
}	t_bump;

typedef struct s_texture
{
	void		*texture[10];
	char		*texture_name[10];
	int			nb_texture;
}	t_texture;

typedef struct s_rt
{
	t_mlx		mlx;
	t_cam		camera;
	t_light		light[20];
	int			nb_light;
	t_ambient	ambient;
	int			nb_object;
	t_type		*object[20];
	int			menu;
	t_bump		bump;
	t_texture	texture;
}	t_rt;

#endif
