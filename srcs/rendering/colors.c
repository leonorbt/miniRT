/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:15:17 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/14 22:18:32 by lbraz-te         ###   ########.fr       */
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