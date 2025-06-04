/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 19:10:35 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/04 19:11:49 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT_H
# define VECT_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	cross_product(t_vec3 vec1, t_vec3 vec2);
t_vec3	vect_add(t_vec3 u, t_vec3 v);

#endif
