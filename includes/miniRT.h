/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:17:37 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/09 11:18:04 by aykrifa          ###   ########.fr       */
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

typedef enum e_type
{
	NONE = 0,
	CYLINDER,
	SPHERE,
	PLANE
}	t_type;

typedef struct s_rgb
{
	int	x;
	int	y;
	int	z;
}	t_rgb;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	float	fov;
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
	// t_rgb	color;
}	t_light;

typedef struct s_sphere
{
	t_type	type;
	t_vec3	center;
	float	diameter;
	t_rgb	color;
}	t_sphere;

typedef struct s_plane
{
	t_type	type;
	t_vec3	point;
	t_vec3	normal_v;
	t_rgb	color;
}	t_plane;

typedef struct s_cylinder
{
	t_type	type;
	t_vec3	center;
	t_vec3	axis;
	float	diameter;
	float	height;
	t_rgb	color;
}	t_cylinder;

typedef struct s_rt
{
	t_mlx		mlx;
	t_camera	camera;
	t_light		light;
	t_ambient	ambiant;
	int			nb_object;
	t_type		*object[10];
	t_type		*cam_obj[10];
}	t_rt;

void	check_args(int argc);
int		fill_vec(char *str, t_vec3 *vec);
int		fill_rgb(char *str, t_rgb *color);
int		get_cam_info(char **tok, t_rt *rt);
int		get_light_info(char **tok, t_rt *rt);
int		get_ambient_info(char **tok, t_rt *rt);
int		get_sphere_info(char **tok, t_rt *rt);
int		get_cylinder_info(char **tok, t_rt *rt);
int		get_plane_info(char **tok, t_rt *rt);

#endif
