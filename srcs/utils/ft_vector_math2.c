/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_math2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 00:52:21 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/13 22:32:30 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

float	v_dot_product(t_array_float v1, t_array_float v2)
{
	float	result;

	result = v1.elem1 * v2.elem1 + v1.elem2 * v2.elem2 + v1.elem3 * v2.elem3;
	return (result);
}
