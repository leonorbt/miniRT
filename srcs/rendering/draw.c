/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:53:47 by aazevedo          #+#    #+#             */
/*   Updated: 2022/09/13 17:49:43 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	rgb_to_color(t_array_int rgb)
{
	return (0 << 24 | rgb.elem1 << 16 | rgb.elem2 << 8 | rgb.elem3);
}

static void	my_mlx_pixel_put(t_mlx_img *img_data, int x, int y, t_array_int rgb)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length
			+ x * (img_data->bits_per_pixel / 8));
	*(unsigned int *) dst = rgb_to_color(rgb);
}

static void	draw_core(int x, int y, t_mlx_img img, t_elem elements)
{
	if (ft_in_circle(x, y, *elements.spheres) == 1)
		my_mlx_pixel_put(&img, x, y, elements.spheres->color);
}

void	create_img(int x, int y, t_mlx_img img, t_elem elements)
{
	t_array_float	ray_dir;
	(void) img;

	ray_dir = get_ray_dir(x, y, &elements);
}

void	draw(t_window *window)
{
	int			x;
	int			y;
	t_mlx_img	img;

	x = 0;
	img.img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			draw_core(x, y, img, *window->elements);
			//create_img(x, y, img, *window->elements);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(window->mlx, window->mlx_win, img.img, 0, 0);
}
