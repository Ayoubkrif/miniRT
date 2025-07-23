/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:52:14 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/23 11:01:51 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>
#include "miniRT_type.h"
#include "miniRT.h"

int	fill_texture(t_rt *rt, t_obj *obj, char *tok)
{
	tok += 2;
	if (!ft_strcmp(tok, "checker"))
		obj->map += 1;
	else
	{
		obj->texture.img = mlx_xpm_file_to_image(rt->mlx.disp, tok,
				&obj->texture.width, &obj->texture.height);
		if (!obj->texture.img)
			return (perror("open"), 1);
		obj->map += 2;
	}
	return (0);
}

int	fill_bump(t_rt *rt, t_obj *obj, char *tok)
{
	tok += 2;
	obj->bump.img = mlx_xpm_file_to_image(rt->mlx.disp, tok,
			&obj->bump.width, &obj->bump.height);
	if (!obj->bump.img)
		return (perror("open"), 1);
	obj->map += 4;
	return (0);
}

void	init_obj(t_obj *obj, t_type mode)
{
	obj->type = mode;
	obj->reflexion = 0;
	obj->map = 0;
	obj->texture.img = NULL;
	obj->bump.img = NULL;
	obj->u_offset = 0;
	obj->v_offset = 0;
}

int	obj_bonus(t_rt *rt, t_obj *obj, char **tok)
{
	int	i;

	i = -1;
	while (tok[i] && i < 3)
	{
		if (!ft_strncmp("r:", tok[i], 2) && !obj->reflexion)
			obj->reflexion = ft_atof(tok[i] + 2);
		if (obj->reflexion < 0 || obj->reflexion > 1)
			return (printf("Wrong range for reflexion\n"), 1);
		if (!ft_strncmp("t:", tok[i], 2) && !obj->texture.img)
		{
			if (fill_texture(rt, obj, tok[i]))
				return (printf("Error on texture\n"), 1);
		}
		if (!ft_strncmp("b:", tok[i], 2) && !obj->bump.img)
		{
			if (fill_bump(rt, obj, tok[i]))
				return (printf("Error on bump\n"), 1);
		}
		i++;
	}
	if (tok[i])
		return (printf("Too many argument, remove : %s\n", tok[i]), 1);
	return (0);
}
