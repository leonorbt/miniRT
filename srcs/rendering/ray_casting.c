/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:59:33 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/17 17:36:34 by lbraz-te         ###   ########.fr       */
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
	t_array_float	result;

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

/*
 * A plane can be defined by a point and the normal.
 * All vectors that lie on the plane are perpendicular to the normal, that is,
 * their dot product with the normal is 0. As we can compute a vector as a
 * difference between 2 points, we know that (P - Po) * n = 0 will describe
 * all the points on the plane, being P any point, Po a point on the plane and
 * n the normal.
 * 
 * If we replace P with the parametric function (P = O + tD), we can find all
 * points on the plane that intersect with the ray.
 * 
 * Important: we can divide by 0 and when the ray is parallel to the plane the
 * denominator will be 0, so we only calculate t if the denominator is bigger
 * than 0
 */
void	plane(t_array_float ray_orig, t_ray *ray, t_pl *plane)
{
	t_array_float	temp;
	float			num;
	float			den;
	float			t;

	temp = v_subtract(plane->view, ray_orig);
	num = v_dot_product(temp, plane->vector);
	den = v_dot_product(ray->direction, plane->vector);
	if (pow(den, 2) < 0.001)
		return ;
	t = num / den;
	if (t > 0 && t <= ray->t)
		ray->t = t;
	else
		return ;
	ray->intersection = get_intersection(ray_orig, *ray);
	ray->normal = v_normalize(plane->vector);
	ray->color = plane->color;
}

/*
 * This is considering that the first sphere is in shadow because it is
 * using as an intersection point the "bottom" of the sphere and then
 * finding the "top" of the sphere has an object that creates the shadow
 */
bool	in_shadow(t_array_float ray_orig, t_ray *ray, t_elem *elements)
{
	float	dist;
	float	dist2;
	int		i;
	t_sp	*spheres;
	t_pl	*planes;

	i = 0;
	dist = (v_length(ray->direction) * 1);
	spheres = elements->spheres;
	ray->direction = v_subtract(ray->intersection, ray_orig);
	while (i < elements->n_sphere)
	{
		sphere(ray_orig, ray, spheres);
		spheres = spheres->next;
		i++;
	}
	i = 0;
	planes = elements->planes;
	while (i < elements->n_plane)
	{
		plane(ray_orig, ray, planes);
		planes = planes->next;
		i++;
	}
	dist2 = (v_length(v_subtract(ray_orig, ray->intersection)) * 1);
	if (dist > dist2 && pow(dist - dist2, 2) > 0.0001)
		return (true);
	return (false);
}

bool	ray_intersect(t_array_float ray_orig, t_ray *ray, t_elem *elements)
{
	int		i;
	t_sp	*spheres;
	t_pl	*planes;
	bool	temp;

	i = 0;
	spheres = elements->spheres;
	while (i < elements->n_sphere)
	{
		sphere(ray_orig, ray, spheres);
		spheres = spheres->next;
		i++;
	}
	i = 0;
	planes = elements->planes;
	while (i < elements->n_plane)
	{
		plane(ray_orig, ray, planes);
		planes = planes->next;
		i++;
	}
	if (ray->t > 0 && ray->t != INFINITY)
		temp = true;
	else
		temp = false;
	return (temp);
}
