/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:49:21 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/21 22:44:49 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_validate_ambient(t_a ambient_light)
{
	if (ambient_light.ratio < 0.0 || ambient_light.ratio > 1.0)
		return (1);
	if (ambient_light.color.f_error == 1)
		return (1);
	if (ambient_light.color.elem1 < 0 || ambient_light.color.elem1 > 255)
		return (1);
	if (ambient_light.color.elem2 < 0 || ambient_light.color.elem2 > 255)
		return (1);
	if (ambient_light.color.elem3 < 0 || ambient_light.color.elem3 > 255)
		return (1);
	return (0);
}

/* do ft_split and then treat each element */
int	ft_parse_ambient(char *line, t_elem *elements)
{
	int		i;
	t_a		ambient_light;
	char	**line_in_pieces;

	i = 0;
	if (elements->has_ambient > 0)
		return (ft_errors(ERR_N_AMBIENT));
	elements->has_ambient += 1;
	line_in_pieces = ft_split(line, ' ');
	while (line_in_pieces[i] != NULL)
	{
		if (i == 0 && ft_strcmp(line_in_pieces[i], "A") != 0)
			break ;
		if (i == 1 && ft_str_is_number(line_in_pieces[i]))
			ambient_light.ratio = ft_parse_float(line_in_pieces[i]);
		if (i == 2)
			ambient_light.color = ft_parse_3int(line_in_pieces[i]);
		i++;
	}
	ft_free_arrays(line_in_pieces);
	if (i > 3 || ft_validate_ambient(ambient_light) == 1)
		return (ft_errors(ERR_AMBIENT_ARGS));
	elements->ambient_light = ambient_light;
	return (0);
}
