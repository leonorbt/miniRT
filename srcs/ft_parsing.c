/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 22:12:37 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 00:17:30 by lbraz-te         ###   ########.fr       */
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

/*
1. Check the file type
2. Open the file
3. Initialize the structure
4. Parse the scene
5. Close the file
 */
int	ft_parsing(char *scene_file)
{
	int	fd;

	if (ft_file_type(scene_file) == 1)
		return (ft_errors(ERR_FILE_TYPE));
	fd = open(scene_file, O_RDONLY);
	if (fd == -1)
		return (ft_errors(ERR_OPEN));
	//initialize elements
	//parse
	if (close(fd) == -1)
		return (ft_errors(ERR_CLOSE));
	//miniRT stuff
	return (0);
}
