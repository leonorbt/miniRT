/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_view_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:18:18 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/31 22:53:09 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
The goal here is to create the matrix that will be printed on the screen.
It will take into account the camera location (view point coordinates) and
the direction it is looking at (orientation vector).
Each ray will then be going from the camera location into each point of the
matrix.
there are infinite matrixes, as the rays cross infinite parallell plans
 */
void	view_matrix(t_elem elements)
{
	int	matrix_center_x;
	int	matrix_center_y;
	int	matrix_center_z;

	matrix_center_x = elements.camera.view.elem1 + elements.camera.vector.elem1;
	matrix_center_y = elements.camera.view.elem2 + elements.camera.vector.elem2;
	matrix_center_z = elements.camera.view.elem3 + elements.camera.vector.elem3;
	
}