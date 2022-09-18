/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:59:33 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 18:47:35 by lbraz-te         ###   ########.fr       */
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

t_array_float	v_scale(t_array_float vector, float f)
{
	t_array_float	result;

	result.elem1 = vector.elem1 * f;
	result.elem2 = vector.elem2 * f;
	result.elem3 = vector.elem3 * f;
	result.f_error = vector.f_error;
	return (result);
}

t_array_float	get_cylinder_normal(t_array_float intersection, t_cy *cylinder)
{
	t_array_float	normal;
	t_array_float	inter_to_base;
	t_array_float	inter_in_axis;

	inter_to_base = v_subtract(intersection, cylinder->view);
	inter_in_axis = v_scale(cylinder->vector, v_dot_product(cylinder->vector, inter_to_base));
	normal = v_subtract(inter_to_base, inter_in_axis);
	return (v_normalize(normal));
}

void	cylinder(t_array_float ray_orig, t_ray *ray, t_cy *cylinder)
{
	t_array_float	quadratic_params;
	float			t0;
	float			t1;
	t_array_float	temp;
	t_array_float	temp2;

	temp = v_subtract(ray->direction, v_scale(cylinder->vector, v_dot_product(ray->direction,cylinder->vector)));
	temp2 = v_subtract(v_subtract(ray_orig, cylinder->view), v_scale(cylinder->vector, v_dot_product(v_subtract(ray_orig, cylinder->view), cylinder->vector)));
	quadratic_params.elem1 = pow(v_length(temp), 2);
	quadratic_params.elem2 = 2 * v_dot_product(temp, temp2);
	quadratic_params.elem3 = pow(v_length(temp2), 2) - pow(cylinder->diameter / 2, 2);
	quadratic_function(quadratic_params, &t0, &t1);
	if (t0 > 0 && t0 < t1 && t0 <= ray->t)
		ray->t = t0;
	else if (t1 > 0 && t1 <= ray->t)
		ray->t = t1;
	else
		return ;
	ray->intersection = get_intersection(ray_orig, *ray);
	ray->normal = get_cylinder_normal(ray->intersection, cylinder);
	ray->color = cylinder->color;
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
	cylinder(ray_orig, ray, elements->cylinders);
	if (ray->t > 0 && ray->t != INFINITY)
		temp = true;
	else
		temp = false;
	return (temp);
}
