/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:14:19 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/23 12:48:06 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "utils.h"
#include "libft.h"
#include "vect.h"
#include "miniRT.h"

int	check_rt_format(char *name);

static char	*get_next_number(char *str)
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

int	fill_vec(char *str, t_vect *vec)
{
	char	*cursor;

	if (!str)
		return (1);
	cursor = str;
	vec->x = ft_atof(cursor);
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (1);
	cursor++;
	vec->y = ft_atof(cursor);
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (1);
	cursor++;
	vec->z = atof(cursor);
	return (0);
}

int	get_identifier(char *str, char **tok, t_rt *rt)
{
	if (!ft_strcmp(str, "C"))
		return (get_cam_info(tok, rt));
	if (!ft_strcmp(str, "A"))
		return (get_ambient_info(tok, rt));
	if (!ft_strcmp(str, "L"))
		return (get_light_info(tok, rt));
	if (!ft_strcmp(str, "sp"))
		return (get_sphere_info(tok, rt));
	if (!ft_strcmp(str, "cy"))
		return (get_cylinder_info(tok, rt));
	if (!ft_strcmp(str, "pl"))
		return (get_plane_info(tok, rt));
	if (!ft_strcmp(str, "co"))
		return (get_cone_info(tok, rt));
	return (dprintf(2, "unknown identifier \"%s\" \n", str), 1);
}

int	fill_scene(char *str, t_rt *rt)
{
	char	**tok;

	tok = ft_strtok(str, " \n\t");
	if (!tok)
	{
		perror("malloc");
		return (1);
	}
	if (get_identifier(tok[0], tok, rt))
	{
		free(tok);
		return (1);
	}
	free(tok);
	return (0);
}

void	get_scene_info(t_rt *rt, char **av)
{
	int		fd;
	char	*str;

	if (check_rt_format(av[1]))
		(print_error(FORMAT, NULL), exit_minirt(rt, 1));
	fd = open(av[1], O_RDONLY);
	if (fd == OPEN_FAILURE)
		(printf("Error\n"), perror("open"), exit_minirt(rt, 1));
	while (true)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (str[0] == '\n' || str[0] == '#')
		{
			free(str);
			continue ;
		}
		if (fill_scene(str, rt))
			(free(str), close(fd), exit_minirt(rt, 1));
		free(str);
	}
	close(fd);
}
