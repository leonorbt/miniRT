/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:41:18 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/22 22:50:26 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_in_circle(int x, int y, t_sp sphere)
{
	int	part_x;
	int	part_y;
	int	part_radius;

	part_x = pow(x - sphere.center.elem1, 2);
	part_y = pow(y - sphere.center.elem2, 2);
	part_radius = pow(sphere.diameter / 2, 2);
	if (part_x + part_y <= part_radius)
		return (1);
	else
		return (0);
}
