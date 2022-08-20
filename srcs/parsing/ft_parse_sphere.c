/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 00:18:25 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/20 22:50:46 by lbraz-te         ###   ########.fr       */
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

static void	ft_lstadd_back_sphere(t_sp **lst, t_sp **new)
{
	t_sp	*element;

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

static void sphere_core(char **line_in_pieces, t_sp **sphere)
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
}

int	ft_parse_sphere(char *line, t_elem *elements)
{
	int		i;
	t_sp	*sphere;
	char	**line_in_pieces;

	i = 0;
	line_in_pieces = ft_split(line, ' ');
	sphere = (t_sp *) malloc(sizeof(t_sp));
	sphere_core(line_in_pieces, &sphere);
	ft_free_arrays(line_in_pieces);
	if (i > 4 || ft_validate_sphere(*sphere) == 1)
		return (ft_errors(ERR_SPHERE_ARGS));
	ft_lstadd_back_sphere(&elements->spheres, &sphere);
	elements->n_sphere += 1;
	return (0);
}
