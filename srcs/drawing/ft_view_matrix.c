/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_view_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:18:18 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/07 19:51:43 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
The goal here is to create the matrix that will be printed on the screen.
It will take into account the camera location (view point coordinates),
the direction it is looking at (orientation vector) and the FOV.
Each ray will then be going from the camera location into each point of the
matrix.
there are infinite matrixes, as the rays cross infinite parallell plans
 */
void	view_matrix(t_elem elements)
{
	/*
	1. Get the 3D plane. We have the normal vector (camera direction),
we can get the distance using 0.5width/tan(FOV/2), so we have a point and
we are able to define a 3D plane using a point and the normal vector
	2. Transform 2D coordinates in 3D plane. Check get_2D_plane function,
but I think the idea is to transform x (0 to width) into a ratio from
-1 to 1 and then multiply by horizontal FOV, to it will go from -0.5width
to 0.5width
	*/
}
