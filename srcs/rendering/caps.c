/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:16:12 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 21:34:37 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	caps(t_array_float ray_orig, t_ray *ray, t_cy *cylinder)
{
	t_array_float	intersection;
	float			num;
	float			den;
	float			t;

	intersection = v_subtract(cylinder->view, ray_orig);
	num = v_dot_product(intersection, cylinder->vector);
	den = v_dot_product(ray->direction, cylinder->vector);
	if (pow(den, 2) < 0.001)
		return ;
	t = num / den;
	intersection = v_add(ray_orig, v_scale(ray->direction, t));
	num = v_length(v_subtract(intersection, cylinder->view));
	den = v_length(v_subtract(intersection, 
		v_add(cylinder->view, v_scale(cylinder->vector, cylinder->height))));
	if (t > 0 && t <= ray->t
		&& (num < cylinder->diameter / 2 || den < cylinder->diameter / 2))
		ray->t = t;
	else
		return ;
	ray->intersection = get_intersection(ray_orig, *ray);
	ray->normal = v_normalize(cylinder->vector);
	ray->color = cylinder->color;
}