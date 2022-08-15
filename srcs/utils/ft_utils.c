/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 00:08:15 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 13:51:07 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_strlen(const char *str)
{
	unsigned long	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	unsigned char	*str;

	if (!s)
		return ;
	str = (unsigned char *)s;
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}

int	ft_check_line(char *str)
{
	int		i;

	if (str == NULL)
		return (1);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		return (0);
	return (1);
}

void	ft_free_arrays(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
