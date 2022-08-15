/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:18:06 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 13:08:15 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char		*res;
	int			i;

	if (!str1)
		return (ft_strdup(str2, '\0'));
	res = (char *)malloc(sizeof(char) * (ft_strlen(str1)
				+ ft_strlen(str2) + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (str1[++i] != '\0')
		res[i] = str1[i];
	while (str2[i - ft_strlen(str1)] != '\0')
	{
		res[i] = str2[i - ft_strlen(str1)];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(char *str, char c)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_subdup(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		while (str[i + j] != '\0')
			j++;
	if (j == 0)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (j + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (str[i++] != '\0')
	{
		res[j] = str[i];
		j++;
	}
	return (res);
}

static int	ft_pass_norme(int fd, char **line, char *buf)
{
	static char	*res;
	int			fr;
	char		*temp;

	fr = BUFFER_SIZE;
	while (ft_check_line(res) == 1 && fr == BUFFER_SIZE)
	{
		fr = read(fd, buf, BUFFER_SIZE);
		buf[fr] = '\0';
		temp = ft_strjoin(res, buf);
		free(res);
		res = temp;
	}
	*line = ft_strdup(res, '\n');
	temp = ft_subdup(res);
	free(res);
	res = temp;
	if (fr < BUFFER_SIZE && temp == NULL)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	int			ret;

	if (read(fd, NULL, 0) == -1 || BUFFER_SIZE < 1 || !line)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	ret = ft_pass_norme(fd, line, buf);
	free(buf);
	return (ret);
}
