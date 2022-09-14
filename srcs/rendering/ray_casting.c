/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:59:33 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/14 13:57:43 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/* My issue is here. Not sure why multiplying by 4 is fucking this up and the minus
 */
void	quadratic_function(t_array_float params, float *t0, float *t1)
{
	float	discriminant;

	discriminant = pow(params.elem2, 2) - 1 * params.elem1 * params.elem3;
	*t0 = (- params.elem2 - sqrt(discriminant)) / (2 * params.elem1);
	*t1 = (- params.elem2 + sqrt(discriminant)) / (2 * params.elem1);
	//printf("The discriminant is %f | t0 is %f | t1 is %f\n", discriminant, *t0, *t1);
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
float	sphere(t_array_float ray_orig, t_array_float ray_dir, t_elem *elements)
{
	t_array_float	temp;
	t_array_float	quadratic_params;
	float			t0;
	float			t1;

	temp = v_subtract(ray_orig, elements->spheres->center);
	quadratic_params.elem1 = pow(v_length(ray_dir), 2);
	quadratic_params.elem2 = 2 * v_dot_product(temp, ray_dir);
	quadratic_params.elem3 = pow(v_length(temp), 2)
		- pow(elements->spheres->diameter / 2, 2);
	quadratic_params.f_error = 0;
	quadratic_function(quadratic_params, &t0, &t1);
	if (t0 > 0 && t0 < t1)
		return (t0);
	if (t1 > 0)
		return (t1);
	return (-1.0);
}

/* Parametric function: Ray_Origin + t * Ray_Direction
 *
 * For now, let's just do 1 sphere. Baby steps
 * We are casting a ray and we want the first intersection between the ray and
 * the sphere surface, which corresponds to the smallest positive t.
 * 
 *
void	cast_ray(t_array_float ray_orig, t_array_float ray_dir,
	t_elem *elements, t_mlx_img img)
{
	if (sphere(ray_orig, ray_dir, elements) > 0)
		my_mlx_pixel_put(&img, x, y, elements.spheres->color);
} */
