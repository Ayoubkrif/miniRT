/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:17:37 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/05 14:45:36 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include "vect.h"

# define WIN_X	1920
# define WIN_Y	1080

# define OPEN_FAILURE -1

typedef struct s_mlx
{
	void	*disp;
	void	*win;
	void	*img;
}	t_mlx;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	int		fov;
}	t_camera;

typedef struct s_rt
{
	t_mlx		mlx;
	t_camera	camera;
}	t_rt;

void	check_args(int argc);

#endif
