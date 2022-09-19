/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 01:26:33 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/19 23:49:28 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static bool	inside(t_array_float intersection, t_tr *triangle)
{
	t_array_float	normal_a;
	t_array_float	normal_b;
	t_array_float	normal_c;

	normal_a = v_cross_product(v_subtract(triangle->p2,
				intersection), v_subtract(triangle->p3, intersection));
	normal_b = v_cross_product(v_subtract(intersection,
				triangle->p1), v_subtract(triangle->p3, triangle->p1));
	normal_c = v_cross_product(v_subtract(triangle->p2,
				triangle->p1), v_subtract(intersection, triangle->p1));
	if (pow(0.5 * v_length(normal_a) + 0.5 * v_length(normal_b)
			+ 0.5 * v_length(normal_c) - triangle->area, 2) < 0.001)
		return (true);
	return (false);
}

void	triangle(t_array_float ray_orig, t_ray *ray, t_tr *triangle)
{
	t_array_float	temp;
	t_array_float	intersection;
	float			num;
	float			den;
	float			t;

	temp = v_subtract(triangle->p1, ray_orig);
	num = v_dot_product(temp, v_normalize(triangle->normal));
	den = v_dot_product(ray->direction, v_normalize(triangle->normal));
	if (pow(den, 2) < 0.001)
		return ;
	t = num / den;
	intersection = v_add(ray_orig, v_scale(ray->direction, t));
	if (t > 0 && t <= ray->t && inside(intersection, triangle))
		ray->t = t;
	else
		return ;
	ray->intersection = get_intersection(ray_orig, *ray);
	ray->normal = v_normalize(triangle->normal);
	ray->color = triangle->color;
}
