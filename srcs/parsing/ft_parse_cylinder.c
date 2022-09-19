/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 00:18:25 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 17:03:07 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_validate_cylinder(t_cy cylinder)
{
	if (cylinder.view.f_error == 1)
		return (1);
	if (cylinder.vector.f_error == 1)
		return (1);
	if (cylinder.vector.elem1 < -1 || cylinder.vector.elem1 > 1)
		return (1);
	if (cylinder.vector.elem2 < -1 || cylinder.vector.elem2 > 1)
		return (1);
	if (cylinder.vector.elem3 < -1 || cylinder.vector.elem3 > 1)
		return (1);
	if (cylinder.diameter <= 0)
		return (1);
	if (cylinder.height <= 0)
		return (1);
	if (cylinder.color.f_error == 1)
		return (1);
	if (cylinder.color.elem1 < 0 || cylinder.color.elem1 > 255)
		return (1);
	if (cylinder.color.elem2 < 0 || cylinder.color.elem2 > 255)
		return (1);
	if (cylinder.color.elem3 < 0 || cylinder.color.elem3 > 255)
		return (1);
	return (0);
}

static int	cylinder_core(char **line_in_pieces, t_cy **cylinder)
{
	int	i;

	i = 0;
	while (line_in_pieces[i] != NULL)
	{
		if (i == 0 && ft_strcmp(line_in_pieces[i], "cy") != 0)
			break ;
		if (i == 1)
			(*cylinder)->view = ft_parse_3float(line_in_pieces[i]);
		if (i == 2)
			(*cylinder)->vector = ft_parse_3float(line_in_pieces[i]);
		if (i == 3 && ft_str_is_number(line_in_pieces[i]))
			(*cylinder)->diameter = ft_parse_float(line_in_pieces[i]);
		if (i == 4 && ft_str_is_number(line_in_pieces[i]))
			(*cylinder)->height = ft_parse_float(line_in_pieces[i]);
		if (i == 5)
			(*cylinder)->color = ft_parse_3int(line_in_pieces[i]);
		i++;
	}
	(*cylinder)->next = NULL;
	if (i > 6)
		return (1);
	return (0);
}

int	ft_parse_cylinder(char *line, t_elem *elements)
{
	int		err;
	t_cy	*cylinder;
	char	**line_in_pieces;

	line_in_pieces = ft_split(line, ' ');
	cylinder = (t_cy *) malloc(sizeof(t_cy));
	err = cylinder_core(line_in_pieces, &cylinder);
	ft_free_arrays(line_in_pieces);
	if (err == 1 || ft_validate_cylinder(*cylinder) == 1)
		return (ft_errors(ERR_CYLINDER_ARGS));
	ft_lstadd_back_obj_cylinder(&elements->obj_list, &cylinder);
	return (0);
}
