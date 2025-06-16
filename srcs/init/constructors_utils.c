/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:52:36 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/16 16:17:39 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "vect.h"
#include "miniRT.h"
#include <stdlib.h>

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

int	fill_rgb(char *str, t_rgb *color)
{
	char	*cursor;

	if (!str)
		return (1);
	cursor = str;
	color->r = (float)ft_atoi(cursor) / 255;
	if (color->r > 1)
		return (dprintf(2, "value to hight :\'%d\'\n", ft_atoi(cursor)), 1);
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (dprintf(2, "no first coma :\'%s\'\n", str), 1);
	cursor++;
	color->g = (float)ft_atoi(cursor) / 255;
	if (color->g > 1)
		return (dprintf(2, "value to hight :\'%d\'\n", ft_atoi(cursor)), 1);
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (dprintf(2, "no second coma :\'%s\'\n", str), 1);
	cursor++;
	color->b = (float)ft_atoi(cursor) / 255;
	if (color->b > 1)
		return (dprintf(2, "value to hight :\'%d\'\n", ft_atoi(cursor)), 1);
	color->brightness = 1;
	return (0);
}
