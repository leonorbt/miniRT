/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:53:47 by aazevedo          #+#    #+#             */
/*   Updated: 2022/09/18 17:44:31 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	my_mlx_pixel_put(t_mlx_img *img_data, int x, int y, t_array_int rgb)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length
			+ x * (img_data->bits_per_pixel / 8));
	*(unsigned int *) dst = rgb_to_color(rgb);
}

static t_array_int	get_base_light(t_array_int base_light, t_l *light,
							t_ray *ray, t_elem elements)
{
	t_ray			shadow_ray;
	float			adj_brightness;
	float			light_disp;
	t_array_int		light_add;

	shadow_ray.direction = v_subtract(light->view, ray->intersection);
	shadow_ray.intersection = ray->intersection;
	shadow_ray.t = INFINITY;
	light_disp = v_dot_product(ray->normal, v_normalize(shadow_ray.direction));
	if (light_disp > 0 && !in_shadow(light->view, &shadow_ray, &elements))
	{
		adj_brightness = (light->brightness * light_disp * 1000.0)
			/ (4 * M_PI * pow(v_length(shadow_ray.direction), 2));
		light_add = color_multiply(light->color, color_ratio(ray->color,
				adj_brightness));
		base_light = color_add(base_light, light_add);
	}
	return (base_light);
}

t_array_int	get_color(t_ray *ray, t_array_int back_light, t_elem elements)
{
	t_l				*light;
	t_array_int		base_light;

	light = elements.lights;
	base_light = color_ratio(light->color, 0);
	while (light != NULL)
	{
		base_light = get_base_light(base_light, light, ray, elements);
		light = light->next;
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
