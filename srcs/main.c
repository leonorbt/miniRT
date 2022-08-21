/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:23:52 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/21 22:45:22 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	on_window_destroy(t_window *data)
{
	// TODO! free program data
	free(data);
	exit(0);
	return (0);
}

int	on_key_press(int keycode, t_window *data)
{
	if (keycode == KEY_ESCAPE)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		free(data);
		// TODO! free program data
		exit(0);
	}
	return (0);
}

t_window	*init_window(t_elem *elements, void (*before_loop)(t_window *data))
{
	t_window	*data;

	data = (t_window *) malloc(sizeof(t_window));
	data->elements = elements;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
	mlx_key_hook(data->mlx_win, &on_key_press, data);
	mlx_hook(data->mlx_win, 17, 0, &on_window_destroy, data);
	before_loop(data);
	mlx_loop(data->mlx);
	return (data);
}

t_elem	ft_element_init(void)
{
	t_elem	elements;

	elements.has_ambient = 0;
	elements.has_camera = 0;
	elements.has_light = 0;
	elements.n_plane = 0;
	elements.planes = NULL;
	elements.n_sphere = 0;
	elements.spheres = NULL;
	elements.n_cylinder = 0;
	elements.cylinders = NULL;
	return (elements);
}

int	main(int argc, char **argv)
{
	t_elem		elements;
	t_window	*window;

	if (argc != 2)
		return (ft_errors(ERR_N_ARGS));
	elements = ft_element_init();
	if (ft_start_parsing(argv[1], &elements) == 1)
		return (1);
	// debug_print(&elements);
	window = init_window(&elements, &draw);
	return (0);
}
