#include "miniRT.h"
#include "math_utils.h"
#include "libft.h"
#include "vect.h"
#include <assert.h>
#include <stdio.h>

void	push_inter(t_rt *rt, t_vect ray, t_inter *inter, t_rgb color, double t)
{
	int	i;

	i = 0;
	while (inter[i].init)
		i++;
	inter[i].init = 1;
	inter[i].color = color;
	inter[i].point = get_point_d(rt->camera.position, ray, t);
}


void	inter_cylinder(t_rt *rt, t_vect ray, t_inter *inter, t_cylinder *cy)
{
	(void)inter;
	/*double	a;*/
	/*double	b;*/
	/*double	c;*/
	/*double	delta;*/
	t_vect	camera;
	t_vect	n;
	double	dist;

	camera = rt->camera.position;
	n = vec_prod(ray, cy->axis);
	if (!n.x && !n.y && !n.z)
		return ;
	dist = fabs(dot_prod(n, vec_sub(cy->center, camera))) / vec_norm(n);
}
