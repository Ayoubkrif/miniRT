/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:52:36 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/09 08:54:31 by cbordeau         ###   ########.fr       */
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
	color->x = ft_atoi(cursor);
	if (color->x > 255)
		return (dprintf(2, "value to hight :\'%d\'\n", color->x), 1);
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (dprintf(2, "no first coma :\'%s\'\n", str), 1);
	cursor++;
	color->y = ft_atoi(cursor);
	if (color->y > 255)
		return (dprintf(2, "value to hight :\'%d\'\n", color->y), 1);
	cursor = get_next_number(cursor);
	if (*cursor != ',')
		return (dprintf(2, "no second coma :\'%s\'\n", str), 1);
	cursor++;
	color->z = ft_atoi(cursor);
	if (color->z > 255)
		return (dprintf(2, "value to hight :\'%d\'\n", color->z), 1);
	return (0);
}
