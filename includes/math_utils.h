/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:28:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/11 13:48:26 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "vect.h"
# include <math.h>

double	to_deg(double angle);
double	to_rad(double angle);

double	delta_2nd(double a, double b, double c);

# define PI 3.1415929

#endif
