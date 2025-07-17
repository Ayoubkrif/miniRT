/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:02:04 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/17 08:36:40 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"

void	vec_add_to(t_vect *u, t_vect *v)
{
	u->x += v->x;
	u->y += v->y;
	u->z += v->z;
}

void	vec_sub_to(t_vect *u, t_vect *v)
{
	u->x -= v->x;
	u->y -= v->y;
	u->z -= v->z;
}

void	vec_mul_to(t_vect *u, double k)
{
	u->x *= k;
	u->y *= k;
	u->z *= k;
}

void	normalize_to(t_vect *u)
{
	double	temp;

	temp = 1 / norm(*u);
	vec_mul_to(u, temp);
}

void	op_to(t_vect *u)
{
	u->x *= -1;
	u->y *= -1;
	u->z *= -1;
}
