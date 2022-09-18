/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:59:33 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 21:15:45 by lbraz-te         ###   ########.fr       */
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

static void	ray_loop_objs(t_elem *elements, t_array_float ray_orig, t_ray *ray)
{
	t_obj	*obj;

	obj = elements->obj_list;
	while (obj != NULL)
	{
		if (obj->sphere != NULL)
			sphere(ray_orig, ray, obj->sphere);
		else if (obj->plane != NULL)
			plane(ray_orig, ray, obj->plane);
        else if (obj->cylinder != NULL)
		{
            cylinder(ray_orig, ray, obj->cylinder);
            caps(ray_orig, ray, obj->cylinder);
		}
		obj = obj->next;
	}
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

	dist = (v_length(ray->direction) * 1);
	ray->direction = v_subtract(ray->intersection, ray_orig);
	ray_loop_objs(elements, ray_orig, ray);
	dist2 = (v_length(v_subtract(ray_orig, ray->intersection)) * 1);
	if (dist > dist2 && pow(dist - dist2, 2) > 0.0001)
		return (true);
	return (false);
}

bool	ray_intersect(t_array_float ray_orig, t_ray *ray, t_elem *elements)
{
	ray_loop_objs(elements, ray_orig, ray);
	if (ray->t > 0 && ray->t != INFINITY)
		return (true);
	return (false);
}
