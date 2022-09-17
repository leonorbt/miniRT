/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:53:47 by aazevedo          #+#    #+#             */
/*   Updated: 2022/09/17 20:57:33 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	rgb_to_color(t_array_int rgb)
{
	if (rgb.elem1 > 255)
		rgb.elem1 = 255;
	if (rgb.elem2 > 255)
		rgb.elem2 = 255;
	if (rgb.elem3 > 255)
		rgb.elem3 = 255;
	return (rgb.elem1 << 16 | rgb.elem2 << 8 | rgb.elem3);
}

static void	my_mlx_pixel_put(t_mlx_img *img_data, int x, int y, t_array_int rgb)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length
			+ x * (img_data->bits_per_pixel / 8));
	*(unsigned int *) dst = rgb_to_color(rgb);
}

t_array_int	get_color(t_ray *ray, t_array_int back_light, t_elem elements)
{
	t_ray			shadow_ray;
	float			light_disp;
	float			adj_brightness;
	t_l				*light;
	t_array_int		light_add;
	t_array_int		base_light;
	int				i;
	int				j;

	light = elements.lights;
	base_light = color_ratio(light->color, 0);
	i = 0;
	while (light)
	{
		shadow_ray.direction = v_subtract(light->view, ray->intersection);
		shadow_ray.intersection = ray->intersection;
		shadow_ray.t = INFINITY;
		j = 0;
		light_disp = v_dot_product(ray->normal, v_normalize(shadow_ray.direction));
		if (light_disp > 0 && !in_shadow(light->view, &shadow_ray, &elements))
		{
			j = 1;
			adj_brightness = (light->brightness * light_disp * 1000.0)
				/ (4 * M_PI * pow(v_length(shadow_ray.direction), 2));
			light_add = color_multiply(light->color, color_ratio(ray->color, adj_brightness));
			base_light = color_add(base_light, light_add);
		}
		light = light->next;
		i++;
	}
	return (color_add(back_light, base_light));
}

void	create_img(int x, int y, t_mlx_img img, t_elem elements)
{
	t_ray			*ray;
	t_array_int		back_light;
	t_array_int		color;

	ray = (t_ray *) malloc(sizeof(t_ray));
	ray->direction = get_ray_dir(x, y, &elements);
	ray->t = INFINITY;
	back_light = color_ratio(elements.ambient_light.color,
			elements.ambient_light.ratio);
	if (ray_intersect(elements.camera.view, ray, &elements))
	{
		back_light = color_multiply(ray->color, back_light);
		color = get_color(ray, back_light, elements);
	}
	else
		color = color_ratio(back_light, 0);
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
			create_img(x, y, img, *window->elements);
			y++;
		}
		x++;
	}
	printf("End of image building\n");
	mlx_put_image_to_window(window->mlx, window->mlx_win, img.img, 0, 0);
}
