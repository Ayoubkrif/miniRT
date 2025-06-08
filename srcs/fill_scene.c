/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:14:19 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/08 19:42:58 by cbordeau         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "vect.h"
#include "miniRT.h"

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
