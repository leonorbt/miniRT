/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazevedo <aazevedo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 00:08:15 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 18:02:41 by aazevedo         ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s1 != '\0')
			s1++;
		if (*s2 != '\0')
			s2++;
	}
	return (0);
}
