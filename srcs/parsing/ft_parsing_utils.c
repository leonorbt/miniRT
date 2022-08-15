/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:49:11 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 22:37:54 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_parse_int(char *str)
{
	long	nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (nbr >= LONG_MAX / 10)
		{
			if (sign == -1)
				return (0);
			else
				return (-1);
		}
		nbr = (nbr * 10) + (*str++ - '0');
	}
	return (nbr * sign);
}

float	ft_parse_float(char	*str)
{
	char	**parts;
	int		left;
	float	right;
	int		right_len;

	parts = ft_split(str, '.');
	right_len = ft_strlen(parts[1]);
	left = ft_parse_int(parts[0]);
	if (parts[1] == NULL)
		right = 0.0;
	else
		right = (float) ft_parse_int(parts[1]);
	while (right_len-- > 0)
		right /= 10;
	return (left + right);
}

int	ft_parse_3int(char	*str, int pos)
{
	char	**parts;
	int		part;
	int		size;

	parts = ft_split(str, ',');
	size = 0;
	while (parts[size] != NULL)
		size++;
	if (pos > size || parts[pos] == NULL)
		part = -5;
	else
		part = ft_parse_int(parts[pos]);
	ft_free_arrays(parts);
	return (part);
}

float	ft_parse_3float(char *str, int pos)
{
	char	**parts;
	float	part;

	parts = ft_split(str, ',');
	part = ft_parse_float(parts[pos]);
	ft_free_arrays(parts);
	return (part);
}
