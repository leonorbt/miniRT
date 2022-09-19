/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:35:28 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/18 00:24:20 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	free_array_and_return(char **array, int ret)
{
	ft_free_arrays(array);
	return (ret);
}

int	ft_str_is_number(char *str)
{
	int	i;

	if (ft_line_has_alpha(str))
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			return (0);
		i++;
	}
	return (1);
}

int	ft_line_has_alpha(char *str)
{
	int		i;
	int		j;
	char	**line_in_pieces;

	line_in_pieces = ft_split(str, ' ');
	i = 0;
	while (line_in_pieces[i] != NULL)
	{
		j = 0;
		while (line_in_pieces[i][j] != '\0' && i > 0)
		{
			if ((line_in_pieces[i][j] >= '0' && line_in_pieces[i][j] <= '9')
			|| line_in_pieces[i][j] == '-'
			|| line_in_pieces[i][j] == ',' || line_in_pieces[i][j] == '.')
				;
			else
				return (free_array_and_return(line_in_pieces, 1));
			j++;
		}
		i++;
	}
	return (free_array_and_return(line_in_pieces, 0));
}
