/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:10:23 by aazevedo          #+#    #+#             */
/*   Updated: 2022/09/18 17:21:20 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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

void	quadratic_function(t_array_float params, float *t0, float *t1)
{
	float	discriminant;

	discriminant = pow(params.elem2, 2) - 4 * params.elem1 * params.elem3;
	*t0 = (-params.elem2 - sqrt(discriminant)) / (2 * params.elem1);
	*t1 = (-params.elem2 + sqrt(discriminant)) / (2 * params.elem1);
}

void	sphere(t_array_float ray_orig, t_ray *ray, t_sp *sphere)
{
	t_array_float	temp;
	t_array_float	quadratic_params;
	float			t0;
	float			t1;

	temp = v_subtract(ray_orig, sphere->center);
	quadratic_params.elem1 = pow(v_length(ray->direction), 2);
	quadratic_params.elem2 = 2 * v_dot_product(temp, ray->direction);
	quadratic_params.elem3 = pow(v_length(temp), 2)
		- pow(sphere->diameter / 2, 2);
	quadratic_params.f_error = 0;
	quadratic_function(quadratic_params, &t0, &t1);
	if (t0 > 0 && t0 < t1 && t0 <= ray->t)
		ray->t = t0;
	else if (t1 > 0 && t1 <= ray->t)
		ray->t = t1;
	else
		return ;
	ray->intersection = get_intersection(ray_orig, *ray);
	ray->normal = v_normalize(v_subtract(ray->intersection,
				sphere->center));
	ray->color = sphere->color;
}
