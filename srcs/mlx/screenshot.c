/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by aykrifa           #+#    #+#             */
/*   Updated: 2026/06/14 15:18:37 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_int.h"
#include <stdio.h>

void	save_ppm(t_rt *rt)
{
	static int		n = 0;
	t_img			*img;
	FILE			*fp;
	int				x;
	int				y;
	unsigned int	color;
	unsigned char	px[3];
	char			name[32];

	snprintf(name, sizeof(name), "screenshot_%03d.ppm", n++);
	img = (t_img *)rt->mlx.img;
	fp = fopen(name, "wb");
	if (!fp)
		return (perror("screenshot"));
	fprintf(fp, "P6\n%d %d\n255\n", WIN_X, WIN_Y);
	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			color = *(unsigned int *)(img->data + y * img->size_line
					+ x * (img->bpp / 8));
			px[0] = (color >> 16) & 0xFF;
			px[1] = (color >> 8) & 0xFF;
			px[2] = color & 0xFF;
			fwrite(px, 1, 3, fp);
			x++;
		}
		y++;
	}
	fclose(fp);
	printf("screenshot saved: %s\n", name);
}
