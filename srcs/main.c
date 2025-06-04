/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:08:05 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/04 15:46:14 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "miniRT.h"
#include <fcntl.h>

void	fill_scene(char *str)
{
	char	*cursor;

	(void)str;
	(void)cursor;
}

void	get_scene_info(t_rt *rt, char **av)
{
	int		fd;
	char	*str;
	int		camera;
	int		ambiant;
	int		light;

	(void)rt;
	(void)camera, (void)ambiant, (void)light;
	camera = 0;
	ambiant = 0;
	light = 0;
	fd = open(av[1], O_RDONLY);
	if (fd == OPEN_FAILURE)
	{
		perror("open");
		exit(1);
	}
	while (true)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		fill_scene(str);
		free(str);
	}
}

void	init_miniRT(t_rt *rt, char **av)
{
	ft_memset(rt, 0, sizeof(t_rt));
	get_scene_info(rt, av);
}

int	main(int ac, char *av[])
{
	t_rt	rt;

	check_args(ac);
	init_miniRT(&rt, av);
	return (0);
}
