/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:15:17 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 17:30:36 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_array_int	color_ratio(t_array_int color, float ratio)
{
	t_array_int	result;

	result.elem1 = color.elem1 * ratio;
	result.elem2 = color.elem2 * ratio;
	result.elem3 = color.elem3 * ratio;
	result.f_error = color.f_error;
	return (result);
}

t_array_int	color_multiply(t_array_int color1, t_array_int color2)
{
	t_array_int	result;
	float		a;
	float		b;

	a = (float) color1.elem1 / 255;
	b = (float) color2.elem1 / 255;
	result.elem1 = a * b * 255;
	a = (float) color1.elem2 / 255;
	b = (float) color2.elem2 / 255;
	result.elem2 = a * b * 255;
	a = (float) color1.elem3 / 255;
	b = (float) color2.elem3 / 255;
	result.elem3 = a * b * 255;
	return (result);
}

t_array_int	color_add(t_array_int color, t_array_int color2)
{
	t_array_int	result;

	result.elem1 = color.elem1 + color2.elem1;
	result.elem2 = color.elem2 + color2.elem2;
	result.elem3 = color.elem3 + color2.elem3;
	result.f_error = color.f_error;
	return (result);
}

int	rgb_to_color(t_array_int rgb)
{
	if (rgb.elem1 > 255)
		rgb.elem1 = 255;
	if (rgb.elem2 > 255)
		rgb.elem2 = 255;
	if (rgb.elem3 > 255)
		rgb.elem3 = 255;
	return (rgb.elem1 << 16 | rgb.elem2 << 8 | rgb.elem3);
}
