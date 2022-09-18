/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:59:33 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 01:11:45 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_array_float	get_intersection(t_array_float ray_orig, t_ray ray)
{
	t_array_float	result;

	result.elem1 = ray_orig.elem1 + ray.direction.elem1 * ray.t;
	result.elem2 = ray_orig.elem2 + ray.direction.elem2 * ray.t;
	result.elem3 = ray_orig.elem3 + ray.direction.elem3 * ray.t;
	result.f_error = 0;
	return (result);
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
	t_sp	*spheres;
	t_pl	*planes;

	dist = (v_length(ray->direction) * 1);
	ray->direction = v_subtract(ray->intersection, ray_orig);
	spheres = elements->spheres;
	while (spheres != NULL)
	{
		sphere(ray_orig, ray, spheres);
		spheres = spheres->next;
	}
	planes = elements->planes;
	while (planes != NULL)
	{
		plane(ray_orig, ray, planes);
		planes = planes->next;
	}
	dist2 = (v_length(v_subtract(ray_orig, ray->intersection)) * 1);
	if (dist > dist2 && pow(dist - dist2, 2) > 0.0001)
		return (true);
	return (false);
}

bool	ray_intersect(t_array_float ray_orig, t_ray *ray, t_elem *elements)
{
	t_sp	*spheres;
	t_pl	*planes;

	spheres = elements->spheres;
	while (spheres != NULL)
	{
		sphere(ray_orig, ray, spheres);
		spheres = spheres->next;
	}
	planes = elements->planes;
	while (planes != NULL)
	{
		plane(ray_orig, ray, planes);
		planes = planes->next;
	}
	if (ray->t > 0 && ray->t != INFINITY)
		return (true);
	return (false);
}
