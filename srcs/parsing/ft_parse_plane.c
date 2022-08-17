/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 00:12:58 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/18 00:35:26 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_validate_plane(t_pl plane)
{
	if (plane.view.f_error == 1)
		return (1);
	if (plane.vector.f_error == 1)
		return (1);
	if (plane.vector.elem1 < -1 || plane.vector.elem1 > 1)
		return (1);
	if (plane.vector.elem2 < -1 || plane.vector.elem2 > 1)
		return (1);
	if (plane.vector.elem3 < -1 || plane.vector.elem3 > 1)
		return (1);
	if (plane.color.f_error == 1)
		return (1);
	if (plane.color.elem1 < 0 || plane.color.elem1 > 255)
		return (1);
	if (plane.color.elem2 < 0 || plane.color.elem2 > 255)
		return (1);
	if (plane.color.elem3 < 0 || plane.color.elem3 > 255)
		return (1);
	return (0);
}

static void	ft_lstadd_back_plane(t_pl **lst, t_pl *new)
{
	t_pl	*element;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	element = *lst;
	while (element->next)
		element = element->next;
	element->next = new;
}

/* !!! need to do the linked lists part */
int	ft_parse_plane(char *line, t_elem *elements)
{
	int		i;
	t_pl	plane;
	char	**line_in_pieces;

	i = 0;
	line_in_pieces = ft_split(line, ' ');
	while (line_in_pieces[i] != NULL)
	{
		if (i == 0 && ft_strcmp(line_in_pieces[i], "pl") != 0)
			break ;
		if (i == 1)
			plane.view = ft_parse_3float(line_in_pieces[i]);
		if (i == 2)
			plane.vector = ft_parse_3int(line_in_pieces[i]);
		if (i == 3)
			plane.color = ft_parse_3int(line_in_pieces[i]);
		i++;
	}
	plane.next = NULL;
	ft_free_arrays(line_in_pieces);
	if (i > 4 || ft_validate_plane(plane) == 1)
		return (ft_errors(ERR_PLANE_ARGS));
	ft_lstadd_back_plane(&elements->planes, &plane);
	elements->n_plane += 1;
	return (0);
}
