/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:07:12 by cbordeau          #+#    #+#             */
/*   Updated: 2025/06/10 11:17:51 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "miniRT.h"
#include "mlx.h"
#include "vect.h"
#include "utils.h"
#include "define.h"

int	key_hook(int keycode, t_rt *rt)
{
	if (keycode == KEY_ESC)
		exit_minirt(rt);
	return (0);
}
