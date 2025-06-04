/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:17:37 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/03 21:34:48 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>

# define WIN_X	1920
# define WIN_Y	1080

# define OPEN_FAILURE -1

typedef struct s_mlx
{
	void	*disp;
	void	*win;
	void	*img;
}	t_mlx;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
}	t_camera;

typedef struct s_rt
{
	t_mlx		mlx;
	t_camera	camera;
}	t_rt;

void	check_args(int argc);

#endif
