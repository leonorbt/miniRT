/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 22:54:28 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/20 23:07:06 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void debug_print(t_elem *elements)
{
	printf("In debug %d\n", elements->has_ambient);
	if (elements->has_ambient > 0)
		printf("Has ambient light: ratio %f, color %d | %d | %d\n",
			elements->ambient_light.ratio, 
			elements->ambient_light.color.elem1,
			elements->ambient_light.color.elem2,
			elements->ambient_light.color.elem3);
}