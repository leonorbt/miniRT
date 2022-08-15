/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:49:21 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 12:19:35 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	ft_parse_ambient(char *line, t_elem *elements, int pos)
{
	t_a	ambient_light;
	
	if (elements->has_ambient > 0)
		return (ft_errors(ERR_N_AMBIENT));
	elements->has_ambient += 1;
	while (line[i] == ' ')
		i++;
}
