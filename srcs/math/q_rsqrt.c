/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_rsqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:35:46 by aykrifa           #+#    #+#             */
/*   Updated: 2025/07/14 09:37:58 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#define THREE_HALFS 1.5

double	double_q_rsqrt(double number)
{
	int64_t	i;
	double	x2;
	double	y;

	x2 = number * 0.5;
	y = number;
	i = *(int64_t *)&y;
	i = 0x5fe6ec85e7de30da - (i >> 1);
	y = *(double *)&i;
	y = y * (THREE_HALFS - (x2 * y * y));
	return (y);
}
