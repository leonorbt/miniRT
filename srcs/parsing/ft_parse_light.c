/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:49:21 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/18 00:29:19 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_validate_light(t_l light)
{
	if (light.view.f_error == 1)
		return (1);
	if (light.brightness < 0.0 || light.brightness > 1.0)
		return (1);
	return (0);
}

/* do ft_split and then treat each element */
int	ft_parse_light(char *line, t_elem *elements)
{
	int		i;
	t_l		light;
	char	**line_in_pieces;

	i = 0;
	if (elements->has_light > 0)
		return (ft_errors(ERR_N_LIGHT));
	elements->has_light += 1;
	line_in_pieces = ft_split(line, ' ');
	while (line_in_pieces[i] != NULL)
	{
		if (i == 0 && ft_strcmp(line_in_pieces[i], "L") != 0)
			break ;
		if (i == 1)
			light.view = ft_parse_3float(line_in_pieces[i]);
		if (i == 2)
			light.brightness = ft_parse_int(line_in_pieces[i]);
		i++;
	}
	ft_free_arrays(line_in_pieces);
	if (i > 3 || ft_validate_light(light) == 1)
		return (ft_errors(ERR_LIGHT_ARGS));
	elements->light = light;
	return (0);
}
