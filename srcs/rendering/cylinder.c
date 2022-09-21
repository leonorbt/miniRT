/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:59:33 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/21 01:07:59 by lbraz-te         ###   ########.fr       */
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
 * Any point on the surface of a cylinder must be within radius of the axis.
 * The cross product of 2 vectors is a 3rd vector that is orthogonal
 * to the first 2 vectors.
 * 
 * 1. Let's create a vector that goes from the surface point to the cylinder
 * base center (or any other point on the axis, doesn't really matter)
 * 2. The cross product between the vector in 1 and the axis is perpendicular to
 * both. Visually, it would be the vector going from the axis to the surface point
 * and parallel to the caps --> length should be equal to the radius
 * r = || (P - C) * cy ||, being r the radius, P a point on the surface,
 * C the cylinder cap center and cy the cylinder axis
 * 3. If we substitute the P by the ray parametric function (P = O + tD, 
 * being P a point, O the origin, t what we want to find and D the direction),
 * we get:
 * 		a = (D * cy) ^2
 * 		b = 2 * (D * cy) * ((O - C) * cy)
 * 		c = ((O - C) * cy) ^2
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
