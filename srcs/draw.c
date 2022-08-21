/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:53:47 by aazevedo          #+#    #+#             */
/*   Updated: 2022/08/21 22:33:47 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	rgb_to_color(t_array_int rgb)
{
	return (0 << 24 | rgb.elem1 << 16 | rgb.elem2 << 8 | rgb.elem3);
}

static void	my_mlx_pixel_put(t_mlx_img *img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length
			+ x * (img_data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

static int ft_in_circle(int x, int y, t_sp sphere)
{
	int	part_x;
	int	part_y;
	int	part_radius;

	part_x = pow(x - sphere.center.elem1, 2);
	part_y = pow(y - sphere.center.elem2, 2);
	part_radius = pow(sphere.diameter/2, 2);
	if (part_x + part_y <= part_radius)
		return (1);
	else
		return (0);
}

void	draw(t_window *window)
{
	int			x;
	int			y;
	t_mlx_img	img;

	x = 0;
	y = 0;
	img.img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	printf("Let's try to design the sphere\n");
	while (x < WINDOW_WIDTH)
	{
		while (y < WINDOW_HEIGHT)
		{
			if (ft_in_circle(x, y, *window->elements->spheres) == 1)
				my_mlx_pixel_put(&img, x, y, 
					rgb_to_color(window->elements->spheres->color));
			y++;
		}
		x++;
	}
	/*my_mlx_pixel_put(&img, 500, 200, 0xFFFFFF);
	my_mlx_pixel_put(&img, 501, 200, 0xFFFFFF);
	my_mlx_pixel_put(&img, 502, 200, 0xFFFFFF);
	my_mlx_pixel_put(&img, 503, 200, 0xFFFFFF);
	my_mlx_pixel_put(&img, 504, 200, 0xFFFFFF);
	my_mlx_pixel_put(&img, 505, 200, 0xFFFFFF);*/
	mlx_put_image_to_window(window->mlx, window->mlx_win, img.img, 0, 0);
	// window->elements
}
