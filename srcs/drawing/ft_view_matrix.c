/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_view_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:18:18 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/30 22:38:33 by lbraz-te         ###   ########.fr       */
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
	t_c	camera;
	int	matrix[x][y];

	camera = elements.camera;
	camera.view * camera.vector;
}