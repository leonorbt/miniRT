/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:59:33 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/20 20:40:46 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_array_float	get_cylinder_normal(t_array_float intersection, t_cy *cylinder)
{
	t_array_float	normal;
	t_array_float	inter_to_base;
	t_array_float	inter_in_axis;

	inter_to_base = v_subtract(intersection, cylinder->view);
	inter_in_axis = v_scale(cylinder->vector,
			v_dot_product(cylinder->vector, inter_to_base));
	normal = v_subtract(inter_to_base, inter_in_axis);
	return (v_normalize(normal));
}

/*
 * For the intersection to be within the height, it must be bellow the top
 * cap (dot product of intersect to top and axis must be )
 */
bool	check_height(float t, t_cy *cylinder, t_array_float ray_orig,
	t_ray *ray)
{
	t_array_float	intersection;
	t_array_float	top;

	if (t > ray->t)
		return (false);
	intersection = v_add(ray_orig, v_scale(ray->direction, t));
	top = v_add(cylinder->view, v_scale(cylinder->vector, cylinder->height));
	if (v_dot_product(cylinder->vector, v_subtract(intersection, top)) < 0
		&& v_dot_product(cylinder->vector,
			v_subtract(intersection, cylinder->view)) >= 0)
		return (true);
	else
		return (false);
}

/*
 * https://mrl.cs.nyu.edu/~dzorin/rend05/lecture2.pdf
 */
void	cylinder(t_array_float ray_orig, t_ray *ray, t_cy *cylinder)
{
	t_array_float	quadratic_params;
	float			t0;
	float			t1;
	t_array_float	ray_l_axis;
	t_array_float	orig_to_view_l_axis;

	ray_l_axis = v_cross_product(ray->direction, v_normalize(cylinder->vector));
	orig_to_view_l_axis = v_cross_product(v_subtract(ray_orig, cylinder->view), v_normalize(cylinder->vector));
	quadratic_params.elem1 = pow(v_length(ray_l_axis), 2);
	quadratic_params.elem2 = 2 * v_dot_product(ray_l_axis, orig_to_view_l_axis);
	quadratic_params.elem3 = pow(v_length(orig_to_view_l_axis), 2) - pow(cylinder->diameter / 2, 2);
	quadratic_function(quadratic_params, &t0, &t1);
	if (t0 > 0 && t0 < t1 && check_height(t0, cylinder, ray_orig, ray))
		ray->t = t0;
	else if (t1 > 0 && check_height(t1, cylinder, ray_orig, ray))
		ray->t = t1;
	else
		return ;
	ray->intersection = get_intersection(ray_orig, *ray);
	ray->normal = get_cylinder_normal(ray->intersection, cylinder);
	ray->color = cylinder->color;
}
