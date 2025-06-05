/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:08:05 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/05 15:17:35 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "vect.h"
# include "utils.h"

void	get_scene_info(t_rt *rt, char **av);

void	init_mini_rt(t_rt *rt, char **av)
{
	ft_memset(rt, 0, sizeof(t_rt));
	get_scene_info(rt, av);
}

int	main(int ac, char *av[])
{
	t_rt	rt;

	check_args(ac);
	init_mini_rt(&rt, av);
	printf("camera =======\nposition  :%f,%f,%f\ndirection :%f,%f,%f\nfov : %d\n", 
		rt.camera.position.x, rt.camera.position.y, rt.camera.position.z,
		rt.camera.direction.x, rt.camera.direction.y, rt.camera.direction.z,
		rt.camera.fov);
	return (0);
}
