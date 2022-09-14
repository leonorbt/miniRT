/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_math.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 00:52:21 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/14 16:34:32 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	v_length(t_array_float vector)
{
	float			length;

	length = sqrt(pow(vector.elem1, 2) + pow(vector.elem2, 2)
			+ pow(vector.elem3, 2));
	return (length);
}

t_array_float	v_normalize(t_array_float vector)
{
	t_array_float	result;
	float			length;

	length = pow(vector.elem1, 2) + pow(vector.elem2, 2) + pow(vector.elem3, 2);
	if (length == 1 || length == 0)
		return (vector);
	result.elem1 = vector.elem1 / sqrt(length);
	result.elem2 = vector.elem2 / sqrt(length);
	result.elem3 = vector.elem3 / sqrt(length);
	result.f_error = 0;
	return (result);
}

t_array_float	v_subtract(t_array_float v1, t_array_float v2)
{
	t_array_float	result;

	result.elem1 = v1.elem1 - v2.elem1;
	result.elem2 = v1.elem2 - v2.elem2;
	result.elem3 = v1.elem3 - v2.elem3;
	result.f_error = 0;
	return (result);
}

t_array_float	v_cross_product(t_array_float v1, t_array_float v2)
{
	t_array_float	result;

	result.elem1 = v1.elem2 * v2.elem3 - v1.elem3 * v2.elem2;
	result.elem2 = v1.elem3 * v2.elem1 - v1.elem1 * v2.elem3;
	result.elem3 = v1.elem1 * v2.elem2 - v1.elem2 * v2.elem1;
	result.f_error = 0;
	return (result);
}

t_array_float	m_multiply(t_array_float vector, t_c cam)
{
	t_array_float	result;

	result.elem1 = vector.elem1 * cam.cam_to_world[0][0]
		+ vector.elem2 * cam.cam_to_world[1][0]
		+ vector.elem3 * cam.cam_to_world[2][0]
		+ cam.cam_to_world[3][0];
	result.elem2 = vector.elem1 * cam.cam_to_world[0][1]
		+ vector.elem2 * cam.cam_to_world[1][1]
		+ vector.elem3 * cam.cam_to_world[2][1]
		+ cam.cam_to_world[3][1];
	result.elem3 = vector.elem1 * cam.cam_to_world[0][2]
		+ vector.elem2 * cam.cam_to_world[1][2]
		+ vector.elem3 * cam.cam_to_world[2][2]
		+ cam.cam_to_world[3][2];
	result.f_error = 0;
	return (result);
}
