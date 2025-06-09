/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:08:05 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/09 08:48:01 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "vect.h"
#include "utils.h"

void	get_scene_info(t_rt *rt, char **av);

void	init_mini_rt(t_rt *rt, char **av)
{
	ft_memset(rt, 0, sizeof(t_rt));
	get_scene_info(rt, av);
}

void	free_rt(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->nb_object)
	{
		free(rt->object[i]);
		i++;
	}
}

int	main(int ac, char *av[])
{
	t_rt	rt;

	check_args(ac);
	rt.nb_object = 0;
	init_mini_rt(&rt, av);
	printf("camera =======\nposition   :%f,%f,%f\ndirection  :%f,%f,%f\nfov        :%f\n",
		rt.camera.position.x, rt.camera.position.y, rt.camera.position.z,
		rt.camera.direction.x, rt.camera.direction.y, rt.camera.direction.z,
		rt.camera.fov);

	printf("light =======\nposition   :%f,%f,%f\nbrightness :%f\n",
		rt.light.position.x, rt.light.position.y, rt.light.position.z, rt.light.brightness);

	printf("ambient =======\nlightning  :%f\ncolor      :%d,%d,%d\n",
		rt.ambiant.lighting, rt.ambiant.color.x, rt.ambiant.color.y, rt.ambiant.color.z);

	printf("plane =======\npoint      :%f,%f,%f\nnormal_v   :%f,%f,%f\ncolor      :%d,%d,%d\n",
		((t_plane *)rt.object[0])->point.x, ((t_plane *)rt.object[0])->point.y,
		((t_plane *)rt.object[0])->point.z,
		((t_plane *)rt.object[0])->normal_v.x,((t_plane *)rt.object[0])->normal_v.y,
		((t_plane *)rt.object[0])->normal_v.z,
		((t_plane *)rt.object[0])->color.x, ((t_plane *)rt.object[0])->color.y,
		((t_plane *)rt.object[0])->color.z);

	printf("sphere =======\npoint      :%f,%f,%f\ndiameter   :%f\ncolor      :%d,%d,%d\n",
		((t_sphere *)rt.object[1])->center.x,((t_sphere *)rt.object[1])->center.y,
		((t_sphere *)rt.object[1])->center.z,
		((t_sphere *)rt.object[1])->diameter,
		((t_sphere *)rt.object[1])->color.x, ((t_sphere *)rt.object[1])->color.y,
		((t_sphere *)rt.object[1])->color.z);

	printf("cylander =======\ncenter     :%f,%f,%f\naxis       :%f,%f,%f\ndiameter   :%f\nheight     :%f\ncolor      :%d,%d,%d\n",
		((t_cylinder *)rt.object[2])->center.x,((t_cylinder *)rt.object[2])->center.y,
		((t_cylinder *)rt.object[2])->center.z,
		((t_cylinder *)rt.object[2])->axis.x,((t_cylinder *)rt.object[2])->axis.y,
		((t_cylinder *)rt.object[2])->axis.z,
		((t_cylinder *)rt.object[2])->diameter,((t_cylinder *)rt.object[2])->height,
		((t_cylinder *)rt.object[2])->color.x, ((t_cylinder *)rt.object[2])->color.y,
		((t_cylinder *)rt.object[2])->color.z);
	free_rt(&rt);
	return (0);
}
