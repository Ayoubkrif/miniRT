/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_type.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:27:28 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/23 12:44:53 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPE_H
# define MINIRT_TYPE_H

# include "define.h"
# include "miniRT_solids.h"

typedef struct s_mlx
{
	void	*disp;
	void	*win;
	void	*img;
	t_img	*addr;
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

typedef struct s_rt
{
	t_mlx		mlx;
	char		name;
	t_cam		camera;
	t_light		light[MAX_LIGHT];
	int			nb_light;
	t_ambient	ambient;
	int			nb_object;
	t_type		*object[MAX_OBJ];
	int			menu;
	int			n_cam;
}	t_rt;

#endif
