/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:28:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/13 19:04:56 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "vect.h"
# include <math.h>

#define EPSILON 0.00001

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sq_delta;
	double	root;
}	t_quadratic;

# define PI 3.14

double	to_deg(double angle);
double	to_rad(double angle);
double	p2(double x);
double	absd(double value);

int		delta_2nd(t_quadratic *quad);

int		double_eq(double d1, double d2);

#endif
