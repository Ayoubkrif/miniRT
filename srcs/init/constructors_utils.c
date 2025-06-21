/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:52:36 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/21 13:19:58 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "define.h"

static char	*get_next_number(char *str)
{
	if (*str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		str++;
	}
	return (str);
}

int	fill_rgb(char *str, t_rgb *color, char *error)
{
	char	*cursor;

	if (!str)
		return (print_error(ARGS, error));
	cursor = str;
	color->r = (float)ft_atoi(cursor) / 255;
	if (color->r > 1 || color->r < 0)
		return (print_error(COLOR, error));
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (print_error(ARGS, error));
	cursor++;
	color->g = (float)ft_atoi(cursor) / 255;
	if (color->g > 1 || color->g < 0)
		return (print_error(COLOR, error));
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (print_error(ARGS, error));
	cursor++;
	color->b = (float)ft_atoi(cursor) / 255;
	if (color->b > 1 || color->b < 0)
		return (print_error(COLOR, error));
	color->brightness = 1;
	return (0);
}

void	set_cy(t_cy *cy)
{
	cy->axis_n = get_normalized_vec(cy->axis_n);
	cy->base.h_normal = vec_prod(cy->axis_n, vec(0, 0, 1));
	if (vect_eq(cy->base.h_normal, (t_vect){0, 0, 0}))
		cy->base.h_normal = vec_prod(cy->axis_n, vec(0, 1, 0));
	cy->base.h_normal = get_normalized_vec(cy->base.h_normal);
	cy->base.v_normal = vec_prod(cy->base.h_normal, cy->axis_n);
	cy->color = color_mul(cy->color, (t_rgb){255, 255, 255, 1});
	cy->semi_height = cy->height / 2;
	cy->radius = cy->diameter / 2;
	cy->top = get_point(cy->center, cy->axis_n, cy->semi_height);
	cy->dt = -dot_prod(cy->top, cy->axis_n);
	cy->bottom = get_point(cy->center, vec_mul(cy->axis_n, -1),
			cy->semi_height);
	cy->db = -dot_prod(cy->bottom, cy->axis_n);
}

void	set_sp(t_sp *sp)
{
	sp->color = color_mul(sp->color, (t_rgb){255, 255, 255, 1});
	sp->radius = sp->diameter / 2;
}
