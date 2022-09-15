/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:53:47 by aazevedo          #+#    #+#             */
/*   Updated: 2022/09/15 19:10:36 by lbraz-te         ###   ########.fr       */
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

t_array_int	get_color(t_ray *ray, t_array_int back_light, t_elem elements)
{
	t_array_int		result;
	t_array_float	light_dir;
	float			light_dispersion_num;
	float			adj_brightness;

	result = color_add(ray->obj_color, back_light);
	light_dir = v_subtract(elements.light.view, ray->intersection);
	light_dispersion_num = v_dot_product(ray->normal, v_normalize(light_dir));
	if (light_dispersion_num > 0)
	{
		adj_brightness = (elements.light.brightness * light_dispersion_num)
			/ (M_PI * pow(v_length(light_dir), 2));
		result = color_add(result, color_ratio(elements.light.color, adj_brightness));
	}
	return (result);
}

void	create_img(int x, int y, t_mlx_img img, t_elem elements)
{
	t_ray			*ray;
	t_array_int		back_light;
	t_array_int		color;

	ray = (t_ray *) malloc(sizeof(t_ray));
	ray->direction = get_ray_dir(x, y, &elements);
	back_light = color_ratio(elements.ambient_light.color,
		elements.ambient_light.ratio);
	//cast_ray(elements.camera.view, ray_dir, elements, img);
	sphere(elements.camera.view, ray, &elements);
	if (ray->t > 0)
	{
		color = get_color(ray, back_light, elements);
	}
	else //doesn't hit anything or max depth (# secondary rays)
		color = back_light;
	my_mlx_pixel_put(&img, x, y, color);
	free(ray);
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
			//draw_core(x, y, img, *window->elements);
			create_img(x, y, img, *window->elements);
			y++;
		}
		x++;
	}
	printf("End of image building\n");
	mlx_put_image_to_window(window->mlx, window->mlx_win, img.img, 0, 0);
}
