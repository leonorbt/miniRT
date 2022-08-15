/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:23:52 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 11:11:33 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	main (int argc, char **argv)
{
	if (argc != 2)
		return (ft_errors(ERR_N_ARGS));
	if (ft_start_parsing(argv[1]) == 1)
		return (1);
	else
		return (0);
}