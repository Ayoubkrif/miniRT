/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:28:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/17 17:00:36 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "vect.h"
# include <math.h>

# define PI 3.14

double	to_deg(double angle);
double	to_rad(double angle);
double	p2(double x);
double	absd(double value);

double	delta_2nd(double a, double b, double c);

int	double_eq(double d1, double d2);

#endif
