/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:08:05 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/05 15:04:32 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"
#include "miniRT.h"
#include "vect.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void	fall(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*get_next_number(char *str)
{
	if (*str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			str++;
		}
	}
	return (str);
}

int	fill_vec(char *str, t_vec3 *vec)
{
	char	*cursor;

	if (!str)
		return (1);
	cursor = str;
	vec->x = atof(cursor);
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (dprintf(2, "no first coma :\'%s\'\n", str), 1);
	cursor++;
	vec->y = atof(cursor);
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (dprintf(2, "no second coma :\'%s\'\n", str), 1);
	cursor++;
	vec->z = atof(cursor);
	return (0);
}

int	get_cam_info(char **tok, t_rt *rt)
{
	if (fill_vec(tok[1], &rt->camera.position))
		return (1);
	if (fill_vec(tok[2], &rt->camera.direction))
		return (1);
	if (!tok[3])
		return (1);
	rt->camera.fov = ft_atoi(tok[3]);
	return (0);
}

int	get_identifier(char *str, char **tok, t_rt *rt)
{
	if (!ft_strcmp(str, "C"))
		return (get_cam_info(tok, rt));
	if (!ft_strcmp(str, "A"))
		return (0);
	if (!ft_strcmp(str, "L"))
		return (0);
	if (!ft_strcmp(str, "sp"))
		return (0);
	if (!ft_strcmp(str, "cy"))
		return (0);
	if (!ft_strcmp(str, "pl"))
		return (0);
	return (dprintf(2, "unknown identifier \"%s\" ", str), 1);
}

int	fill_scene(char *str, t_rt *rt)
{
	char	**tok;

	tok = ft_split(str, ' ');
	if (!tok)
	{
		perror("malloc");
		return (1);
	}
	if (get_identifier(tok[0], tok, rt))
	{
		fall(tok);
		return (1);
	}
	fall(tok);
	return (0);
}

void	get_scene_info(t_rt *rt, char **av)
{
	int		fd;
	char	*str;

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
		if (str[0] == '\n')
		{
			free(str);
			continue ;
		}
		if (fill_scene(str, rt))
		{
			dprintf(2, "%s wrong format", str);
			free(str);
			exit(1);
		}
		free(str);
	}
	close(fd);
}

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
