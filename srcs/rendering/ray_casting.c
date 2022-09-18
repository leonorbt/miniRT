/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:59:33 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 19:47:44 by lbraz-te         ###   ########.fr       */
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

t_array_float	v_scale(t_array_float vector, float f)
{
	t_array_float	result;

	result.elem1 = vector.elem1 * f;
	result.elem2 = vector.elem2 * f;
	result.elem3 = vector.elem3 * f;
	result.f_error = vector.f_error;
	return (result);
}

t_array_float	v_add(t_array_float v1, t_array_float v2)
{
	t_array_float	result;

	result.elem1 = v1.elem1 + v2.elem1;
	result.elem2 = v1.elem2 + v2.elem2;
	result.elem3 = v1.elem3 + v2.elem3;
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
	t_cy	*cylinders;

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
	cylinders = elements->cylinders;
	while (cylinders != NULL)
	{
		cylinder(ray_orig, ray, cylinders);
		cylinders = cylinders->next;
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
	t_cy	*cylinders;

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
	i = 0;
	cylinders = elements->cylinders;
	while (i < elements->n_cylinder)
	{
		cylinder(ray_orig, ray, cylinders);
		cylinders = cylinders->next;
		i++;
	}
	if (ray->t > 0 && ray->t != INFINITY)
		return (true);
	return (false);
}
