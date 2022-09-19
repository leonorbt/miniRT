/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:49:21 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/18 00:51:04 by aazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_validate_light(t_l light)
{
	if (light.view.f_error == 1)
		return (1);
	if (light.brightness < 0.0 || light.brightness > 1.0)
		return (1);
	if (light.color.f_error == 1)
		return (1);
	if (light.color.elem1 < 0 || light.color.elem1 > 255)
		return (1);
	if (light.color.elem2 < 0 || light.color.elem2 > 255)
		return (1);
	if (light.color.elem3 < 0 || light.color.elem3 > 255)
		return (1);
	return (0);
}

static void	ft_lstadd_back_light(t_l **lst, t_l **new)
{
	t_l	*element;

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

/* do ft_split and then treat each element */
int	ft_parse_light(char *line, t_elem *elements)
{
	int		i;
	t_l		*light;
	char	**line_in_pieces;

	i = 0;
	line_in_pieces = ft_split(line, ' ');
	light = (t_l *) malloc(sizeof(t_l));
	while (line_in_pieces[i] != NULL)
	{
		if (i == 0 && ft_strcmp(line_in_pieces[i], "L") != 0)
			break ;
		if (i == 1)
			light->view = ft_parse_3float(line_in_pieces[i]);
		if (i == 2 && ft_str_is_number(line_in_pieces[i]))
			light->brightness = ft_parse_float(line_in_pieces[i]);
		if (i == 3)
			light->color = ft_parse_3int(line_in_pieces[i]);
		i++;
	}
	light->next = NULL;
	ft_free_arrays(line_in_pieces);
	ft_lstadd_back_light(&elements->lights, &light);
	if (i > 4 || ft_validate_light(*light) == 1)
		return (ft_errors(ERR_LIGHT_ARGS));
	return (0);
}
