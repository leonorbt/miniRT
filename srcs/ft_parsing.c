/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:12:37 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 12:24:32 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	ft_file_type(char *str)
{
	int	size;

	size = ft_strlen(str);
	if (size < 4)
		return (1);
	if (str[size - 1] != 't')
		return (1);
	if (str[size - 2] != 'r')
		return (1);
	if (str[size - 3] != '.')
		return (1);
	return (0);
}

// !! test for empty lines. are they size 0?
//what is the minimum length of the line?
/*
 We are going to skip the spaces and then check the identifier
 we try to store the element according to the identifier and
 return error if it's not a valid identifier or if there is
 information missing
 */
int	ft_parse_line(char *line, t_elem *elements)
{
	int	i;
	int	size;
	int	f_error;

	i = 0;
	f_error = 1;
	size = ft_strlen(line);
	while (line[i] == ' ')
		i++;
	if (line[i] == 'A' && line[i + 1] == ' ')
		f_error = ft_parse_ambient(line, elements, i + 1);
	return (f_error);
}

/* Should I add a variable that is the position
so the objects can be "painted" in the right order?
 */
int	ft_parser(int fd, t_elem *elements)
{
	char	*line;
	int		line_end;

	line = "";
	line_end = 1;
	while (line_end > 0)
	{
		line_end = get_next_line(fd, &line);
		if (ft_parse_line(line, elements) == 1)
			line_end = -1;
		free(line);
	}
	if (line_end == -1)
		return (1);
	else
		return (0);
}

// Antonio can you do this in the right way please? I was looping
t_elem	ft_element_init(void)
{
	t_elem	elements;
	t_a		*ambient_light;
	t_c		*camera;
	t_l		*light;
	t_pl	*plane;
	t_sp	*sphere;
	t_cy	*cylinder;

	ambient_light = NULL;
	camera = NULL;
	light = NULL;
	plane = NULL;
	sphere = NULL;
	cylinder = NULL;
	elements.has_ambient = 0;
	elements.ambient_light = *ambient_light;
	elements.n_camera = 0;
	elements.camera = *camera;
	elements.n_light = 0;
	elements.light = *light;
	elements.n_plane = 0;
	elements.plane = *plane;
	elements.n_sphere = 0;
	elements.sphere = *sphere;
	elements.n_cylinder = 0;
	elements.cylinder = *cylinder;
	return (elements);
}

/*
1. Check the file type
2. Open the file
3. Initialize the structure
4. Parse the scene
5. Close the file
 */
// !!! validate that there is at least 1 camera!
// !!! Should I validate ambient light and light?
int	ft_start_parsing(char *scene_file)
{
	int		fd;
	t_elem	elements;

	if (ft_file_type(scene_file) == 1)
		return (ft_errors(ERR_FILE_TYPE));
	fd = open(scene_file, O_RDONLY);
	if (fd == -1)
		return (ft_errors(ERR_OPEN));
	elements = ft_element_init();
	if (ft_parser(fd, &elements) == 1)
		return (1);
	if (close(fd) == -1)
		return (ft_errors(ERR_CLOSE));
	//miniRT stuff
	return (0);
}
