/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <ayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:37:19 by aykrifa           #+#    #+#             */
/*   Updated: 2025/06/03 17:42:29 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	check_args(int argc)
{
	if (argc < 2)
	{
		dprintf(2, "Too few arguments\n");
		exit(1);
	}
	if (argc > 2)
	{
		dprintf(2, "Too much arguments\n");
		exit(1);
	}
}
