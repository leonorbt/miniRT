/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:23:52 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/14 22:15:06 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main (int argc, char **argv)
{
	t_elem elements;

	if (argc != 2)
	{
		printf("Error\nThis program only takes 1 argument, the .rt scene");
		return (1);
	}
	elements = ft_parsing(argv[1]);
	if (elements->error == 1)
		return (1);
	else
		return (0);
}