/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_to_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:47:29 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/08 00:50:51 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
 * The goal of this file is to transform the the pixel coordinates
 * (x: 0 -> width, y: 0 -> height) into camera coordinates
 * (x: -1 -> 1, y: -1 -> 1). The camera coordinates correspond to the 2d plane
 * which is drawn and has the camera in the center (no z coordinate)
 */
int	ft_pixel_to_canvas(int pixel_x, int pixel_y, t_window *window)
{
	int	ndc_x;
	int	ndc_y;

	ndc_x = pixel_x / WINDOW_WIDTH;
	ndc_y = 1 - pixel_y / WINDOW_HEIGHT;
}