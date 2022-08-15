/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:49:21 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 13:52:22 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
			break;
		if (i == 1)
			ambient_light.ratio = ft_parse_float(line_in_pieces[i]);
		if (i == 2)
		{
			ambient_light.color[0] = ft_parse_3int(line_in_pieces[i], 0);
			ambient_light.color[1] = ft_parse_3int(line_in_pieces[i], 1);
			ambient_light.color[2] = ft_parse_3int(line_in_pieces[i], 2);
		}
		if (i > 2)
			printf("There is an error to be handled\n");
		i++;
	}
	ft_free_arrays(line_in_pieces);
	printf("Need to validate that the values are allowed\n");
	return (1);
}

