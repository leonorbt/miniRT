/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:16:12 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 23:56:07 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	bottom_cap(t_array_float ray_orig, t_ray *ray, t_cy *cylinder)
{
	t_array_float	intersection;
	float			num;
	float			den;
	float			t;
	float			dist;

	intersection = v_subtract(cylinder->view, ray_orig);
	num = v_dot_product(intersection, cylinder->vector);
	den = v_dot_product(ray->direction, cylinder->vector);
	if (pow(den, 2) < 0.001)
		return ;
	t = num / den;
	intersection = v_add(ray_orig, v_scale(ray->direction, t));
	dist = v_length(v_subtract(intersection, cylinder->view));
	if (t > 0 && t <= ray->t && dist < cylinder->diameter / 2)
	{
		ray->t = t;
	}
	else
		return ;
	ray->intersection = get_intersection(ray_orig, *ray);
	ray->normal = v_normalize(cylinder->vector);
	ray->color = cylinder->color;
}

void	top_cap(t_array_float ray_orig, t_ray *ray, t_cy *cylinder)
{
	t_array_float	intersection;
	t_array_float	top;
	float			num;
	float			den;
	float			t;

	top = v_add(cylinder->view, v_scale(cylinder->vector, cylinder->height));
	intersection = v_subtract(top, ray_orig);
	num = v_dot_product(intersection, cylinder->vector);
	den = v_dot_product(ray->direction, cylinder->vector);
	if (pow(den, 2) < 0.001)
		return ;
	t = num / den;
	intersection = v_add(ray_orig, v_scale(ray->direction, t));
	num = v_length(v_subtract(intersection, top));
	if (t > 0 && t <= ray->t && num < cylinder->diameter / 2)
	{
		ray->t = t;
	}
	else
		return ;
	ray->intersection = get_intersection(ray_orig, *ray);
	ray->normal = v_normalize(v_scale(cylinder->vector, -1));
	ray->color = cylinder->color;
}
