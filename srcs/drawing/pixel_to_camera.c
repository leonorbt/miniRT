/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_to_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:47:29 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/12 01:06:55 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/*
 * Both the raster and the NDC are in 2D
 * The goal here is to transform the pixel coordinates
 * (x: 0 -> width, y: 0 -> height) into a Normalized Device Coordinate
 * ranging from 0 to 1.
 * We are summing 0.5 both to the pixel_x and pixel_y because we want the
 * center of the pixel
 */
t_array_float	ft_raster_ndc(int pixel_x, int pixel_y)
{
	t_array_float	ndc;

	ndc.elem1 = (pixel_x + 0.5) / WINDOW_WIDTH;
	ndc.elem2 = 1 - ((pixel_y + 0.5) / WINDOW_HEIGHT);
	ndc.elem3 = 0;
	ndc.f_error = 0;
	return (ndc);
}

/*
 * Convert pixel coordinates into camera coordinates:
 1. Raster to NDC, which makes X and Y defined in [0,1]
 2. NDC to canvas
	- The tagent of an angle is the ratio between the opposite and the adjacent.
	If we imagine a triangle that starts at the eye/camera,
	goes to half of the screen (adjacent), crosses the screen (opposite, which is
	half of the canvas width) and then returns to the eye/camera (hypotenuse),
	with an angle of FOV/2. If we get the tagent of that angle (convert to radians
	at pi = 180º), we are getting the ratio between half of the canvas width and
	the distance to screen. If we assume the distance to be 1, than we have 
	half of the width of the canvas. So 2 * Angle = canvas width
	- We can get the height of the canvas using the width and the aspect ratio of
	the window in pixels
	- We know that we can transform the canvas into NDC by adding half the canvas
	width (or height, if y) to shift the origin to 0 and dividing by the canvas
	width (or height, if y), to make the max at 1. Following that, we can transform
	in canvas with angle * (2x - 1), being that angle is half of the canvas width.
	- This should make the coordinates vary between -1 and 1
 */

t_array_float	ft_pixel_to_canvas(int pixel_x, int pixel_y, t_elem *elements)
{
	t_array_float	ndc;
	float			angle;
	float			aspect_ratio;
	t_array_float	canvas;

	ndc = ft_raster_ndc(pixel_x, pixel_y);
	angle = tan((elements->camera.fov / 2) * M_PI / 180);
	canvas.elem1 = angle * (ndc.elem1 * 2 - 1);
	aspect_ratio = WINDOW_HEIGHT / WINDOW_WIDTH;
	canvas.elem2 = angle * aspect_ratio * (ndc.elem2 * 2 - 1);
	canvas.elem3 = 1;
	canvas.f_error = 0;
	return (canvas);
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
 */
matrix	look_at(t_array_float cam_origin, t_array_float cam_dir)
{
	t_array_float forward;
	
	forward = v_normalize(v_subtract(cam_origin, cam_dir));
}