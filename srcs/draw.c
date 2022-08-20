/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:53:47 by aazevedo          #+#    #+#             */
/*   Updated: 2022/08/20 13:53:48 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	my_mlx_pixel_put(t_mlx_img *img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length
			+ x * (img_data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw(t_window *window)
{
	t_mlx_img	img;

	img.img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_pixel_put(&img, 500, 200, 0xFFFFFF);
	my_mlx_pixel_put(&img, 501, 200, 0xFFFFFF);
	my_mlx_pixel_put(&img, 502, 200, 0xFFFFFF);
	my_mlx_pixel_put(&img, 503, 200, 0xFFFFFF);
	my_mlx_pixel_put(&img, 504, 200, 0xFFFFFF);
	my_mlx_pixel_put(&img, 505, 200, 0xFFFFFF);
	mlx_put_image_to_window(window->mlx, window->mlx_win, img.img, 0, 0);

	// window->elements
}
