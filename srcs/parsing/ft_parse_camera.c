/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:49:21 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 00:40:56 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// !!! Should there be any limits on the view point coordinates? Don't think so
static int	ft_validate_camera(t_c camera)
{
	if (camera.view.f_error == 1)
		return (1);
	if (camera.vector.f_error == 1)
		return (1);
	if (camera.vector.elem1 < -1 || camera.vector.elem1 > 1)
		return (1);
	if (camera.vector.elem2 < -1 || camera.vector.elem2 > 1)
		return (1);
	if (camera.vector.elem3 < -1 || camera.vector.elem3 > 1)
		return (1);
	if (camera.fov < 0 || camera.fov > 180)
		return (1);
	return (0);
}

static t_array_float	get_right(t_array_float forward)
{
	t_array_float	temp;
	t_array_float	right;

	temp.f_error = 0;
	if (forward.elem1 == 0
		&& (forward.elem2 == 1 || forward.elem2 == -1)
		&& forward.elem3 == 0)
	{
		temp.elem1 = 1;
		temp.elem2 = 0;
		temp.elem3 = 0;
	}
	else
	{
		temp.elem1 = 0;
		temp.elem2 = 1;
		temp.elem3 = 0;
	}
	right = v_cross_product(temp, forward);
	return (right);
}

static t_array_float	origin_vector(void)
{
	t_array_float	arr;

	arr.elem1 = 0;
	arr.elem2 = 0;
	arr.elem3 = 0;
	return (arr);
}

/*
 * The look_at function creates the matrix that converts world coordinates
 * into camera coordinates. This is a 4x4 matrix because we need an extra
 * row with the translation values (the 3x3 part is the rotation) and we
 * add one last column to facilitate matrix multiplication (checking if the
 * last element is 1 is a good strategy to make sure it's normalized).
 * The matrix:
 * - Row 1: right axis, which would be the x-axis from the camera (x, y, z, 0)
 * - Row 2: up axis, which would be the y-axis from the camera (x, y, z, 0)
 * - Row 3: forward axis, which would be the z-axis from the camera and
 * should be pointing into the camera (x, y, z, 0)
 * - Row 4: camera origin, which is the translation values
 * 
 * How to compute the forward axis?
 * Being that this is going from the camera back, we can use the direction
 * of the vector that goes in the opposite direction of cam_dir and passes 
 * through the origin. So, camera direction - camera origin.
 * 
 * How to compute the right axis?
 * We already have the forward axis and we know that the cross product of
 * 2 vectors gives us a 3rd vector which is perpendicular to both of them.
 * By convention, we use the (0,1,0) vector for that. However, there is
 * one case where this creates a problem: if the forward is (0,1,0) or
 * (0, -1, 0). In that case, we will make the temp vector to be (1,0,0).
 * 
 * How to compute the up axis?
 * Just do the cross product of the 2 known axis to get a 3rd vector that
 * will be perpendicular to both forward and right.
 */
static t_c	*look_at(t_c *camera)
{
	t_array_float	forward;
	t_array_float	right;
	t_array_float	up;

	forward = v_normalize(v_subtract(origin_vector(), camera->vector));
	right = v_normalize(get_right(forward));
	up = v_normalize(v_cross_product(forward, right));
	camera->cam_to_world[0][0] = right.elem1;
	camera->cam_to_world[0][1] = right.elem2;
	camera->cam_to_world[0][2] = right.elem3;
	camera->cam_to_world[0][3] = 0;
	camera->cam_to_world[1][0] = up.elem1;
	camera->cam_to_world[1][1] = up.elem2;
	camera->cam_to_world[1][2] = up.elem3;
	camera->cam_to_world[1][3] = 0;
	camera->cam_to_world[2][0] = forward.elem1;
	camera->cam_to_world[2][1] = forward.elem2;
	camera->cam_to_world[2][2] = forward.elem3;
	camera->cam_to_world[2][3] = 0;
	camera->cam_to_world[3][0] = camera->view.elem1;
	camera->cam_to_world[3][1] = camera->view.elem2;
	camera->cam_to_world[3][2] = camera->view.elem3;
	camera->cam_to_world[3][3] = 1;
	return (camera);
}

/* do ft_split and then treat each element */
int	ft_parse_camera(char *line, t_elem *elements)
{
	int		i;
	t_c		camera;
	char	**line_in_pieces;

	i = -1;
	if (elements->has_camera > 0)
		return (ft_errors(ERR_N_CAMERA));
	elements->has_camera += 1;
	line_in_pieces = ft_split(line, ' ');
	while (line_in_pieces[++i] != NULL)
	{
		if (i == 0 && ft_strcmp(line_in_pieces[i], "C") != 0)
			break ;
		if (i == 1)
			camera.view = ft_parse_3float(line_in_pieces[i]);
		if (i == 2)
			camera.vector = ft_parse_3float(line_in_pieces[i]);
		if (i == 3)
			camera.fov = ft_parse_int(line_in_pieces[i]);
	}
	ft_free_arrays(line_in_pieces);
	if (i > 4 || ft_validate_camera(camera) == 1)
		return (ft_errors(ERR_CAMERA_ARGS));
	elements->camera = *look_at(&camera);
	return (0);
}
