/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 22:54:28 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/21 17:01:37 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	print_elements(t_elem elements)
{
	int	i;

	i = 0;
	printf("There are %d planes\n", elements.n_plane);
	while (i < elements.n_plane)
	{
		printf("\t %d plane: view %f | %f | %f, vector %d | %d | %d, color %d | %d | %d \n",
			i + 1,
			elements.planes->view.elem1,
			elements.planes->view.elem2,
			elements.planes->view.elem3,
			elements.planes->vector.elem1,
			elements.planes->vector.elem2,
			elements.planes->vector.elem3,
			elements.planes->color.elem1,
			elements.planes->color.elem2,
			elements.planes->color.elem3);
		elements.planes = elements.planes->next;
		i++;
	}
	i = 0;
	printf("There are %d spheres\n", elements.n_sphere);
	while (i < elements.n_sphere)
	{
		printf("\t %d spheres: center %f | %f | %f, diameter %f, color %d | %d | %d \n",
			i + 1,
			elements.spheres->center.elem1,
			elements.spheres->center.elem2,
			elements.spheres->center.elem3,
			elements.spheres->diameter,
			elements.spheres->color.elem1,
			elements.spheres->color.elem2,
			elements.spheres->color.elem3);
		elements.spheres = elements.spheres->next;
		i++;
	}
	i = 0;
	printf("There are %d cylinders\n", elements.n_cylinder);
	while (i < elements.n_cylinder)
	{
		printf("\t %d cylinders: view %f | %f | %f, vector %d | %d | %d, diameter %f, height %f, color %d | %d | %d \n",
			i + 1,
			elements.cylinders->view.elem1,
			elements.cylinders->view.elem2,
			elements.cylinders->view.elem3,
			elements.cylinders->vector.elem1,
			elements.cylinders->vector.elem2,
			elements.cylinders->vector.elem3,
			elements.cylinders->diameter,
			elements.cylinders->height,
			elements.cylinders->color.elem1,
			elements.cylinders->color.elem2,
			elements.cylinders->color.elem3);
		elements.cylinders = elements.cylinders->next;
		i++;
	}
	printf("End of printing\n");
}

void	debug_print(t_elem *elements)
{
	if (elements->has_ambient > 0)
		printf("Has ambient light: ratio %f, color %d | %d | %d\n",
			elements->ambient_light.ratio,
			elements->ambient_light.color.elem1,
			elements->ambient_light.color.elem2,
			elements->ambient_light.color.elem3);
	if (elements->has_camera > 0)
		printf("Has camera: view %f | %f | %f, vector %d | %d | %d, fov %d\n",
			elements->camera.view.elem1,
			elements->camera.view.elem2,
			elements->camera.view.elem3,
			elements->camera.vector.elem1,
			elements->camera.vector.elem2,
			elements->camera.vector.elem3,
			elements->camera.fov);
	if (elements->has_light > 0)
		printf("Has light: view %f | %f | %f, brightness %d\n",
			elements->light.view.elem1,
			elements->light.view.elem2,
			elements->light.view.elem3,
			elements->light.brightness);
	print_elements(*elements);
}
