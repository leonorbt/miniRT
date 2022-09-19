/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 23:46:02 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/19 19:51:38 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static void	ft_error_elements(int error_code)
{
	if (error_code == ERR_ALPHA)
		ft_putstr_fd("Error\nThe only chars supported are identifiers\n", 2);
	else if (error_code == ERR_N_AMBIENT)
		ft_putstr_fd("Error\nThere is more than 1 ambient light\n", 2);
	else if (error_code == ERR_AMBIENT_ARGS)
		ft_putstr_fd("Error\nThe ambient light is ill formated\n", 2);
	else if (error_code == ERR_N_CAMERA)
		ft_putstr_fd("Error\nThere shold be exactly 1 camera\n", 2);
	else if (error_code == ERR_CAMERA_ARGS)
		ft_putstr_fd("Error\nThe camera is ill formated\n", 2);
	else if (error_code == ERR_N_LIGHT)
		ft_putstr_fd("Error\nThere is more than 1 light\n", 2);
	else if (error_code == ERR_LIGHT_ARGS)
		ft_putstr_fd("Error\nThe light is ill formated\n", 2);
	else if (error_code == ERR_PLANE_ARGS)
		ft_putstr_fd("Error\nThe plane is ill formated\n", 2);
	else if (error_code == ERR_SPHERE_ARGS)
		ft_putstr_fd("Error\nThe sphere is ill formated\n", 2);
	else if (error_code == ERR_CYLINDER_ARGS)
		ft_putstr_fd("Error\nThe cylinder is ill formated\n", 2);
	else if (error_code == ERR_TRIANGLE_ARGS)
		ft_putstr_fd("Error\nThe triangle is ill formated\n", 2);
}

int	ft_errors(int error_code)
{
	if (error_code == ERR_N_ARGS)
		ft_putstr_fd("Error\nThis program takes 1 argument, the .rt scene\n", 2);
	else if (error_code == ERR_FILE_TYPE)
		ft_putstr_fd("Error\nThe scene file must be .rt\n", 2);
	else if (error_code == ERR_OPEN)
		ft_putstr_fd("Error\nCouldn't open scene file\n", 2);
	else if (error_code == ERR_CLOSE)
		ft_putstr_fd("Error\nCouldn't close scene file\n", 2);
	else
		ft_error_elements(error_code);
	return (1);
}
