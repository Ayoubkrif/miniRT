/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:17:37 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/06 12:44:58 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "vect.h"

# define WIN_X	1920
# define WIN_Y	1080

typedef struct s_mlx
{
	void	*disp;
	void	*win;
	void	*img;
}	t_mlx;

typedef struct s_rgb
{
	int	x;
	int	y;
	int	z;
}	t_rgb;

typedef struct oject
{
	int	type;
}	t_object;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	int		fov;
}	t_camera;

typedef struct s_ambient
{
	float	lighting;
	t_rgb	color;
}	t_ambient;

typedef struct light
{
	t_vec3	position;
	float	brightness;
	t_rgb	color;
}	t_light;

typedef struct s_sphere
{
	int		type;
	t_vec3	center;
	float	diameter;
	t_rgb	color;
}	t_sphere;

typedef struct s_plane
{
	int		type;
	t_vec3	point;
	t_vec3	normal_v;
	t_rgb	color;
}	t_plane;

typedef struct s_cylinder
{
	int		type;
	t_vec3	center;
	t_vec3	axis;
	float	diameter;
	float	height;
	t_rgb	color;
}	t_cylander;

typedef struct s_rt
{
	t_mlx		mlx;
	t_camera	camera;
}	t_rt;

void	check_args(int argc);

#endif
