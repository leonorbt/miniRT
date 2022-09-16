/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:59:33 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/16 14:34:27 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	quadratic_function(t_array_float params, float *t0, float *t1)
{
	float	discriminant;

	discriminant = pow(params.elem2, 2) - 4 * params.elem1 * params.elem3;
	*t0 = (-params.elem2 - sqrt(discriminant)) / (2 * params.elem1);
	*t1 = (-params.elem2 + sqrt(discriminant)) / (2 * params.elem1);
}

static t_array_float	get_intersection(t_array_float ray_orig, t_ray ray)
{
	t_array_float result;

	result.elem1 = ray_orig.elem1 + ray.direction.elem1 * ray.t;
	result.elem2 = ray_orig.elem2 + ray.direction.elem2 * ray.t;
	result.elem3 = ray_orig.elem3 + ray.direction.elem3 * ray.t;
	result.f_error = 0;
	return (result);
}

/* !!! Test if the camera is within a sphere (should only see the sphere)
 *
 * How do we do this?
 * 1. We know that all points on the surface of the sphere are at radius^2
 * distance of the center, that is (P - C)^2 - r^2 = 0, being P a point, C the
 * center and r the radius
 * 2. We can define all the points on the ray with the parametric function,
 * that is P = O + tD, being P a point, O the origin, t what we want to find
 * and D the direction
 * 3. If we replace the P on 1. with the parametric function, we have a quadratic
 * equation and we can find t.
 * 		a = D^2 --> this should be 1 because it's normalized
 * 		b = 2 * D * (O - C)
 * 		c = |O - C|^2 - r^2 
 * (to avoid using O and C, we created a temp that is O - C)
 */
void	sphere(t_array_float ray_orig, t_ray *ray, t_elem *elements)
{
	t_array_float	temp;
	t_array_float	quadratic_params;
	float			t0;
	float			t1;

	temp = v_subtract(ray_orig, elements->spheres->center);
	quadratic_params.elem1 = pow(v_length(ray->direction), 2);
	quadratic_params.elem2 = 2 * v_dot_product(temp, ray->direction);
	quadratic_params.elem3 = pow(v_length(temp), 2)
		- pow(elements->spheres->diameter / 2, 2);
	quadratic_params.f_error = 0;
	quadratic_function(quadratic_params, &t0, &t1);
	if (t0 > 0 && t0 < t1)
		ray->t = t0;
	else if (t1 > 0)
		ray->t = t1;
	else
		ray->t = 0;
	ray->intersection = get_intersection(ray_orig, *ray);
	ray->normal = v_normalize(v_subtract(ray->intersection,
		elements->spheres->center));
	ray->obj_color = elements->spheres->color;
}
