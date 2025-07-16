/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:01 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/16 12:07:04 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "define.h"
#include "libft.h"
#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>

int	sp_bonus(t_rt *rt, t_sp *sp, char **tok);
int	cy_bonus(t_rt *rt, t_cy *cy, char **tok);
int	co_bonus(t_rt *rt, t_co *co, char **tok);
int	pl_bonus(t_rt *rt, t_pl *pl, char **tok);

int	get_sphere_info(char **tok, t_rt *rt)
{
	t_sp	*sp;

	sp = malloc(sizeof(t_sp));
	if (!sp)
		return (print_error(MALLOC, "sphere"));
	sp->type = SPHERE;
	rt->object[rt->nb_object] = (t_type *)sp;
	rt->nb_object += 1;
	if (fill_vec(tok[1], &sp->center))
		return (print_error(ARGS, "sphere center"));
	if (!tok[2])
		return (print_error(ARGS, "sphere diameter"));
	sp->diameter = atof(tok[2]);
	if (fill_int_color(tok[3], &sp->color, "sphere"))
		return (1);
	if (sp_bonus(rt, sp, tok))
		return (printf("Error bonus\n"), 1);
	set_sp(sp);
	return (0);
}

int	get_cylinder_info(char **tok, t_rt *rt)
{
	t_cy	*cy;

	cy = malloc(sizeof(t_cy));
	if (!cy)
		return (print_error(MALLOC, "cylinder"));
	cy->type = CYLINDER;
	rt->object[rt->nb_object] = (t_type *)cy;
	rt->nb_object += 1;
	if (fill_vec(tok[1], &cy->center))
		return (print_error(ARGS, "cylinder center"));
	if (fill_vec(tok[2], &cy->axis_n))
		return (print_error(ARGS, "cylinder axis"));
	if (cy->axis_n.x < -1 || cy->axis_n.x > 1 || cy->axis_n.y < -1
		|| cy->axis_n.y > 1 || cy->axis_n.z < -1 || cy->axis_n.z > 1)
		return (print_error(VECT_NORM, "cylinder axis"));
	if (vect_nul(&cy->axis_n))
		return (print_error(VECT_NULL, "cylinder axis"));
	if (!tok[3])
		return (print_error(ARGS, "cylinder diameter"));
	cy->diameter = atof(tok[3]);
	if (!tok[4])
		return (print_error(ARGS, "cylinder height"));
	cy->height = atof(tok[4]);
	if (fill_int_color(tok[5], &cy->color, "cylinder"))
		return (1);
	if (cy_bonus(rt, cy, tok))
		return (printf("Error bonus\n"), 1);
	cy->axis_n = normalize(cy->axis_n);
	set_cy(cy);
	return (0);
}

int	get_plane_info(char **tok, t_rt *rt)
{
	t_pl	*pl;

	pl = malloc(sizeof(t_pl));
	if (!pl)
		return (print_error(MALLOC, "plane"));
	pl->type = PLANE;
	rt->object[rt->nb_object] = (t_type *)pl;
	rt->nb_object += 1;
	if (fill_vec(tok[1], &pl->point))
		return (print_error(ARGS, "plane point"));
	if (fill_vec(tok[2], &pl->normal_n))
		return (print_error(ARGS, "plane normal"));
	if (pl->normal_n.x < -1 || pl->normal_n.x > 1
		|| pl->normal_n.y < -1 || pl->normal_n.y > 1
		|| pl->normal_n.z < -1 || pl->normal_n.z > 1)
		return (print_error(VECT_NORM, "plane normal"));
	if (vect_nul(&pl->normal_n))
		return (print_error(VECT_NULL, "plane normal"));
	if (fill_int_color(tok[3], &pl->color, "plane"))
		return (1);
	if (pl_bonus(rt, pl, tok))
		return (printf("Error bonus\n"), 1);
	pl->normal_n = normalize(pl->normal_n);
	set_pl(pl);
	return (0);
}

int	get_cone_info(char **tok, t_rt *rt)
{
	t_co	*co;

	co = malloc(sizeof(t_co));
	if (!co)
		return (print_error(MALLOC, "cone"));
	co->type = CONE;
	rt->object[rt->nb_object] = (t_type *)co;
	rt->nb_object += 1;
	if (fill_vec(tok[1], &co->apex))
		return (print_error(ARGS, "cone apex"));
	if (fill_vec(tok[2], &co->axis_n))
		return (print_error(ARGS, "cone axis"));
	if (co->axis_n.x < -1 || co->axis_n.x > 1 || co->axis_n.y < -1
		|| co->axis_n.y > 1 || co->axis_n.z < -1 || co->axis_n.z > 1)
		return (print_error(VECT_NORM, "cone axis"));
	if (vect_nul(&co->axis_n))
		return (print_error(VECT_NULL, "cone axis"));
	if (!tok[3])
		return (print_error(ARGS, "cone diameter"));
	co->diameter = atof(tok[3]);
	if (!tok[4])
		return (print_error(ARGS, "cone height"));
	co->height = atof(tok[4]);
	if (fill_int_color(tok[5], &co->color, "cone"))
		return (1);
	if (co_bonus(rt, co, tok))
		normalize_to(&co->axis_n);
	set_co(co);
	return (0);
}
