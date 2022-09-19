/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 00:18:25 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 17:02:44 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_validate_sphere(t_sp sphere)
{
	if (sphere.center.f_error == 1)
		return (1);
	if (sphere.diameter <= 0)
		return (1);
	if (sphere.color.f_error == 1)
		return (1);
	if (sphere.color.elem1 < 0 || sphere.color.elem1 > 255)
		return (1);
	if (sphere.color.elem2 < 0 || sphere.color.elem2 > 255)
		return (1);
	if (sphere.color.elem3 < 0 || sphere.color.elem3 > 255)
		return (1);
	return (0);
}

static int	sphere_core(char **line_in_pieces, t_sp **sphere)
{
	int	i;

	i = 0;
	while (line_in_pieces[i] != NULL)
	{
		if (i == 0 && ft_strcmp(line_in_pieces[i], "sp") != 0)
			break ;
		if (i == 1)
			(*sphere)->center = ft_parse_3float(line_in_pieces[i]);
		if (i == 2)
			(*sphere)->diameter = ft_parse_float(line_in_pieces[i]);
		if (i == 3)
			(*sphere)->color = ft_parse_3int(line_in_pieces[i]);
		i++;
	}
	(*sphere)->next = NULL;
	if (i > 4)
		return (1);
	return (0);
}

int	ft_parse_sphere(char *line, t_elem *elements)
{
	int		err;
	t_sp	*sphere;
	char	**line_in_pieces;

	line_in_pieces = ft_split(line, ' ');
	sphere = (t_sp *) malloc(sizeof(t_sp));
	err = sphere_core(line_in_pieces, &sphere);
	ft_free_arrays(line_in_pieces);
	if (err == 1 || ft_validate_sphere(*sphere) == 1)
		return (ft_errors(ERR_SPHERE_ARGS));
	ft_lstadd_back_obj_sphere(&elements->obj_list, &sphere);
	return (0);
}
