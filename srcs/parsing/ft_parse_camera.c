/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:49:21 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/16 00:07:08 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// !!! Should there be any limits on the view point coordinates? Don't think so
int	ft_validate_camera(t_c camera)
{
	if (camera.view.f_error == 1)
		return (1);
	if (camera.vector.f_error == 1)
		return (1);
	if (camera.vector.elem1 < -1 || camera.vector.elem1 > 1)
		return (1);
	if (camera.vector.elem2 < -1 || camera.vector.elem2 > 1)
		return (1);
	if (camera.vector.elem3 < -1 || camera.vector.elem3 > 1)
		return (1);
	if (camera.FOV < 0 || camera.FOV > 180)
		return (1);
	return (0);
}

/* do ft_split and then treat each element */
int	ft_parse_camera(char *line, t_elem *elements)
{
	int		i;
	t_c		camera;
	char	**line_in_pieces;

	i = -1;
	if (elements->has_camera > 0)
		return (ft_errors(ERR_N_CAMERA));
	elements->has_camera += 1;
	line_in_pieces = ft_split(line, ' ');
	while (line_in_pieces[++i] != NULL)
	{
		if (i == 0 && ft_strcmp(line_in_pieces[i], "C") != 0)
			break ;
		if (i == 1)
			camera.view = ft_parse_3float(line_in_pieces[i]);
		if (i == 2)
			camera.vector = ft_parse_3int(line_in_pieces[i]);
		if (i == 3)
			camera.FOV = ft_parse_int(line_in_pieces[i]);
	}
	ft_free_arrays(line_in_pieces);
	if (i > 4 || ft_validate_camera(camera) == 1)
		return (ft_errors(ERR_CAMERA_ARGS));
	elements->camera = camera;
	return (0);
}
