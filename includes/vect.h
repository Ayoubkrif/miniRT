/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:10:35 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/13 19:11:49 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT_H
# define VECT_H

typedef struct s_vect
{
	double	x;
	double	y;
	double	z;
}	t_vect;

t_vect	vec_add(t_vect u, t_vect v);
t_vect	vec_sub(t_vect u, t_vect v);
t_vect	vec_mul(t_vect u, double k);
t_vect	cross(t_vect u, t_vect v);
t_vect	normalize(t_vect u);
t_vect	op(t_vect u);

double	dot(t_vect u, t_vect v);
double	norm(t_vect u);
int		vect_eq(t_vect *u, t_vect *v);
int		vect_nul(t_vect *u);
int		vect_col(t_vect u, t_vect v);

t_vect	get_point_t(t_vect start, t_vect dir, double norm);
t_vect	get_point(t_vect start, t_vect dir, double t);

void	vec_add_to(t_vect *u, t_vect *v);
void	vec_sub_to(t_vect *u, t_vect *v);
void	vec_mul_to(t_vect *u, double k);
void	normalize_to(t_vect *u);
void	op_to(t_vect *u);

#endif
