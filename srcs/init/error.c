/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:24:40 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/21 12:40:36 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	print_error(char *message, char *complement)
{
	printf("Error\n");
	if (complement)
		printf("%s %s\n", message, complement);
	else
		printf("%s\n", message);
	return (1);
}
