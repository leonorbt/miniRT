/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:12:37 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/20 13:53:41 by aazevedo         ###   ########.fr       */
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
	else if (line[i] == 'p' && ft_strlen(line) > i + 1 && line[i + 1] == 'l')
		f_error = ft_parse_plane(line, elements);
	else if (line[i] == 's' && ft_strlen(line) > i + 1 && line[i + 1] == 'p')
		f_error = ft_parse_sphere(line, elements);
	else if (line[i] == 'c' && ft_strlen(line) > i + 1 && line[i + 1] == 'y')
		f_error = ft_parse_cylinder(line, elements);
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

/*
1. Check the file type
2. Open the file
3. Initialize the structure
4. Parse the scene
5. Close the file
 */
int	ft_start_parsing(char *scene_file, t_elem elements)
{
	int		fd;

	if (ft_file_type(scene_file) == 1)
		return (ft_errors(ERR_FILE_TYPE));
	fd = open(scene_file, O_RDONLY);
	if (fd == -1)
		return (ft_errors(ERR_OPEN));
	if (ft_parser(fd, &elements) == 1)
	{
		printf("end in parsing\n");
		return (1);
	}
	if (close(fd) == -1)
		return (ft_errors(ERR_CLOSE));
	//midraniRT stuff
	// !! todo: free each plane, sphere and cylinder
	return (0);
}
