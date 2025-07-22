/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <bordeau@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:58:01 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/22 13:04:47 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "define.h"
#include "miniRT_solids.h"
#include <stdlib.h>
#include <stdio.h>

int		obj_bonus(t_rt *rt, t_obj *obj, char **tok);
void	init_obj(t_obj *obj, t_type mode);
int		fill_normal(t_vect *vect, char *tok);

int	get_sphere_info(char **tok, t_rt *rt)
{
	t_sp	*sp;

	if (rt->nb_object >= MAX_OBJ)
		return (print_error(OBJ, "sphere"), 1);
	sp = malloc(sizeof(t_sp));
	if (!sp)
		return (print_error(MALLOC, "sphere"));
	init_obj((t_obj *)sp, SPHERE);
	rt->object[rt->nb_object] = (t_type *)sp;
	rt->nb_object += 1;
	if (fill_vec(tok[1], &sp->center))
		return (print_error(ARGS, "sphere center"));
	if (!tok[2])
		return (print_error(ARGS, "sphere diameter"));
	sp->diameter = ft_atof(tok[2]);
	if (fill_int_color(tok[3], &sp->color, "sphere"))
		return (1);
	if (obj_bonus(rt, (t_obj *)sp, tok + 4))
		return (print_error(BONUS, "sphere"), 1);
	set_sp(sp);
	return (0);
}

int	get_cylinder_info(char **tok, t_rt *rt)
{
	t_cy	*cy;

	if (rt->nb_object >= MAX_OBJ)
		return (print_error(OBJ, "cylinder"), 1);
	cy = malloc(sizeof(t_cy));
	if (!cy)
		return (print_error(MALLOC, "cylinder"));
	init_obj((t_obj *)cy, CYLINDER);
	rt->object[rt->nb_object] = (t_type *)cy;
	rt->nb_object += 1;
	if (fill_vec(tok[1], &cy->center))
		return (print_error(ARGS, "cylinder center"));
	if (fill_normal(&cy->axis_n, tok[2]))
		return (1);
	if (!tok[3])
		return (print_error(ARGS, "cylinder diameter"));
	cy->diameter = ft_atof(tok[3]);
	if (!tok[4])
		return (print_error(ARGS, "cylinder height"));
	cy->height = ft_atof(tok[4]);
	if (fill_int_color(tok[5], &cy->color, "cylinder"))
		return (1);
	if (obj_bonus(rt, (t_obj *)cy, tok + 6))
		return (print_error(BONUS, "cylinder"), 1);
	return (normalize_to(&cy->axis_n), set_cy(cy), 0);
}

int	get_plane_info(char **tok, t_rt *rt)
{
	t_pl	*pl;

	if (rt->nb_object >= MAX_OBJ)
		return (print_error(OBJ, "plane"), 1);
	pl = malloc(sizeof(t_pl));
	if (!pl)
		return (print_error(MALLOC, "plane"));
	init_obj((t_obj *)pl, PLANE);
	rt->object[rt->nb_object] = (t_type *)pl;
	rt->nb_object += 1;
	if (fill_vec(tok[1], &pl->point))
		return (print_error(ARGS, "plane point"));
	if (fill_normal(&pl->normal_n, tok[2]))
		return (1);
	if (fill_int_color(tok[3], &pl->color, "plane"))
		return (1);
	if (obj_bonus(rt, (t_obj *)pl, tok + 4))
		return (print_error(BONUS, "plane"), 1);
	pl->normal_n = normalize(pl->normal_n);
	set_pl(pl);
	return (0);
}

int	get_cone_info(char **tok, t_rt *rt)
{
	t_co	*co;

	if (rt->nb_object >= MAX_OBJ)
		return (print_error(OBJ, "cone"), 1);
	co = malloc(sizeof(t_co));
	if (!co)
		return (print_error(MALLOC, "cone"));
	init_obj((t_obj *)co, CONE);
	rt->object[rt->nb_object] = (t_type *)co;
	rt->nb_object += 1;
	if (fill_vec(tok[1], &co->apex))
		return (print_error(ARGS, "cone apex"));
	if (fill_normal(&co->axis_n, tok[2]))
		return (1);
	if (!tok[3])
		return (print_error(ARGS, "cone diameter"));
	co->diameter = ft_atof(tok[3]);
	if (!tok[4])
		return (print_error(ARGS, "cone height"));
	co->height = ft_atof(tok[4]);
	if (fill_int_color(tok[5], &co->color, "cone"))
		return (1);
	if (obj_bonus(rt, (t_obj *)co, tok + 6))
		return (print_error(BONUS, "cone"), 1);
	return (normalize_to(&co->axis_n), set_co(co), 0);
}
