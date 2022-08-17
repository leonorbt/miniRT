/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:12:37 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/18 00:36:32 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

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
	int	f_error;

	i = 0;
	f_error = 1;
	while (line[i] == ' ')
		i++;
	if (ft_line_has_alpha(line) == 1)
		return (ft_errors(ERR_ALPHA));
	if (line[i] == 'A')
		f_error = ft_parse_ambient(line, elements);
	else if (line[i] == 'C')
		f_error = ft_parse_camera(line, elements);
	else if (line[i] == 'L')
		f_error = ft_parse_light(line, elements);
	// !!! doesnt this risk a segfault like redirs?
	else if (line[i] == 'p' && line[i + 1] == 'l')
		f_error = ft_parse_plane(line, elements);
	else if (ft_strlen(line) == i)
		f_error = 0;
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

t_elem	ft_element_init(void)
{
	t_elem	elements;

	elements.has_ambient = 0;
	elements.has_camera = 0;
	elements.has_light = 0;
	elements.n_plane = 0;
	elements.planes = NULL;
	elements.n_sphere = 0;
	elements.spheres = NULL;
	elements.n_cylinder = 0;
	elements.cylinders = NULL;
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
	{
		printf("end in parsing\n");
		return (1);
	}
	if (close(fd) == -1)
		return (ft_errors(ERR_CLOSE));
	fd = 0;
	while (elements.planes->next != NULL && fd < elements.n_plane)
	{
		printf("The plan %d has colors %d,%d,%d\n", fd, elements.planes->color.elem1,
		elements.planes->color.elem2, elements.planes->color.elem3);
		elements.planes = elements.planes->next;
		fd++;
	}
	//miniRT stuff
	return (0);
}
