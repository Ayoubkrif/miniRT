/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:52:36 by cbordeau          #+#    #+#             */
/*   Updated: 2025/07/13 13:30:19 by aykrifa          ###   ########.fr       */
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
	color->r = (float)ft_atoi(cursor);
	// if (color->r > 1 || color->r < 0)
	// 	return (print_error(COLOR, error));
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (print_error(ARGS, error));
	cursor++;
	color->g = (float)ft_atoi(cursor);
	// if (color->g > 1 || color->g < 0)
	// 	return (print_error(COLOR, error));
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (print_error(ARGS, error));
	cursor++;
	color->b = (float)ft_atoi(cursor);
	// if (color->b > 1 || color->b < 0)
	// 	return (print_error(COLOR, error));
	return (0);
}
