/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 00:18:25 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/19 01:23:00 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_validate_triangle(t_tr triangle)
{
	if (triangle.p1.f_error == 1)
		return (1);
	if (triangle.p2.f_error == 1)
		return (1);
	if (triangle.p3.f_error == 1)
		return (1);
	if (triangle.area == 0)
		return (1);
	if (triangle.color.f_error == 1)
		return (1);
	if (triangle.color.elem1 < 0 || triangle.color.elem1 > 255)
		return (1);
	if (triangle.color.elem2 < 0 || triangle.color.elem2 > 255)
		return (1);
	if (triangle.color.elem3 < 0 || triangle.color.elem3 > 255)
		return (1);
	return (0);
}

static void	ft_lstadd_back_triangle(t_tr **lst, t_tr **new)
{
	t_tr	*element;

	if (*lst == NULL)
	{
		*lst = *new;
		return ;
	}
	element = *lst;
	while (element->next)
		element = element->next;
	element->next = *new;
}

static int	triangle_core(char **line_in_pieces, t_tr **triangle)
{
	int	i;

	i = 0;
	while (line_in_pieces[i] != NULL)
	{
		if (i == 0 && ft_strcmp(line_in_pieces[i], "tr") != 0)
			break ;
		if (i == 1)
			(*triangle)->p1 = ft_parse_3float(line_in_pieces[i]);
		if (i == 2)
			(*triangle)->p2 = ft_parse_3float(line_in_pieces[i]);
		if (i == 3)
			(*triangle)->p3 = ft_parse_3float(line_in_pieces[i]);
		if (i == 4)
			(*triangle)->color = ft_parse_3int(line_in_pieces[i]);
		i++;
	}
	(*triangle)->normal = v_cross_product(v_subtract((*triangle)->p2, 
		(*triangle)->p1),v_subtract((*triangle)->p3, (*triangle)->p1));
	(*triangle)->area = 0.5 * v_length((*triangle)->normal);
	(*triangle)->next = NULL;
	if (i > 5)
		return (1);
	return (0);
}

int	ft_parse_triangle(char *line, t_elem *elements)
{
	int		err;
	t_tr	*triangle;
	char	**line_in_pieces;

	line_in_pieces = ft_split(line, ' ');
	triangle = (t_tr *) malloc(sizeof(t_tr));
	err = triangle_core(line_in_pieces, &triangle);
	ft_free_arrays(line_in_pieces);
	if (err == 1 || ft_validate_triangle(*triangle) == 1)
		return (ft_errors(ERR_TRIANGLE_ARGS));
	ft_lstadd_back_triangle(&elements->triangle, &triangle);
	ft_lstadd_back_obj_triangle(&elements->obj_list, &triangle);
	elements->n_triangle += 1;
	return (0);
}
