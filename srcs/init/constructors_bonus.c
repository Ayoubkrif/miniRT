/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:52:14 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/16 12:14:50 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "define.h"
#include "libft.h"
#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>

int	sp_bonus(t_rt *rt, t_sp *sp, char **tok)
{
	if (tok[4])
		sp->reflexion = atof(tok[4]);
	else
		return (print_error(REFLEXION, "sphere"));
	sp->texture.img = NULL;
	if (tok[5])
	{
		if (!ft_strcmp(tok[5], "checker"))
			sp->map = 0;
		else
		{
			sp->texture.img = mlx_xpm_file_to_image(rt->mlx.disp, tok[5], &sp->texture.width, &sp->texture.height);
			if (!sp->texture.img)
				printf("i dont have a xpm\n");
			sp->map = 1;
		}
	}
	else
		sp->map = -1;
	sp->bump.img = NULL;
	if (tok[6] && *tok[6] != '\n')
	{
		sp->bump.img = mlx_xpm_file_to_image(rt->mlx.disp, tok[6], &sp->bump.width, &sp->bump.height);
		if (!sp->texture.img)
			return (printf("i dont have a bump on sp\n"), 1);
	}
	return (0);
}

int	cy_bonus(t_rt *rt, t_cy *cy, char **tok)
{
	if (tok[6])
		cy->reflexion = atof(tok[6]);
	else
		return (print_error(REFLEXION, "cylinder"));
	cy->texture.img = NULL;
	if (tok[7])
	{
		if (!ft_strcmp(tok[7], "checker"))
			cy->map = 0;
		else
		{
			cy->texture.img = mlx_xpm_file_to_image(rt->mlx.disp, tok[7], &cy->texture.width, &cy->texture.height);
			cy->map = 1;
		}
	}
	else
		cy->map = -1;
	cy->bump.img = NULL;
	if (tok[8] && *tok[8] != '\n')
	{
		cy->bump.img = mlx_xpm_file_to_image(rt->mlx.disp, tok[8], &cy->bump.width, &cy->bump.height);
		if (!cy->texture.img)
			return (printf("i dont have a bump on cy\n"), 1);
	}
	return (0);
}

int	co_bonus(t_rt *rt, t_co *co, char **tok)
{
	if (tok[6])
		co->reflexion = atof(tok[6]);
	else
		return (print_error(REFLEXION, "cone"));
	co->texture.img = NULL;
	if (tok[7])
	{
		if (!ft_strcmp(tok[7], "checker"))
			co->map = 0;
		else
		{
			co->texture.img = mlx_xpm_file_to_image(rt->mlx.disp, tok[7], &co->texture.width, &co->texture.height);
			if (!co->texture.img)
				printf("i dont have a xpm\n");
			co->map = 1;
		}
	}
	else
		co->map = -1;
	co->bump.img = NULL;
	if (tok[8] && *tok[8] != '\n')
	{
		co->bump.img = mlx_xpm_file_to_image(rt->mlx.disp, tok[8], &co->bump.width, &co->bump.height);
		if (!co->texture.img)
			return (printf("i dont have a bump on co\n"), 1);
	}
	return (0);
}

int	pl_bonus(t_rt *rt, t_pl *pl, char **tok)
{
	if (tok[4])
		pl->reflexion = atof(tok[4]);
	else
		return (print_error(REFLEXION, "plane"));
	pl->texture.img = NULL;
	if (tok[5])
	{
		if (!ft_strcmp(tok[5], "checker"))
			pl->map = 0;
		else
		{
			pl->texture.img = mlx_xpm_file_to_image(rt->mlx.disp, tok[5], &pl->texture.width, &pl->texture.height);
			pl->map = 1;
		}
	}
	else
		pl->map = -1;
	pl->bump.img = NULL;
	if (tok[6] && *tok[6] != '\n')
	{
		printf("i am in\n");
		pl->bump.img = mlx_xpm_file_to_image(rt->mlx.disp, tok[6], &pl->bump.width, &pl->bump.height);
		if (!pl->texture.img)
			return (printf("i dont have a bump on pl\n"), 1);
	}
	return (0);
}
