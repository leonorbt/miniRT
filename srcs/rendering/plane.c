/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:10:25 by aazevedo          #+#    #+#             */
/*   Updated: 2022/09/18 01:14:55 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
