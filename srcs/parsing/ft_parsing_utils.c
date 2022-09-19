/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:49:11 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/17 00:33:57 by lbraz-te         ###   ########.fr       */
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
	ft_free_arrays(parts);
	while (right_len-- > 0)
		right /= 10;
	if (left == 0 && str[0] == '-')
		return ((left + right) * -1);
	return (left + right);
}

t_array_int	ft_parse_3int(char *str)
{
	char		**parts;
	int			size;
	t_array_int	array;

	parts = ft_split(str, ',');
	size = 0;
	while (parts[size] != NULL)
	{
		if (size == 0)
			array.elem1 = ft_parse_int(parts[size]);
		if (size == 1)
			array.elem2 = ft_parse_int(parts[size]);
		if (size == 2)
			array.elem3 = ft_parse_int(parts[size]);
		size++;
	}
	if (size == 3)
		array.f_error = 0;
	else
		array.f_error = 1;
	ft_free_arrays(parts);
	return (array);
}

t_array_float	ft_parse_3float(char *str)
{
	char			**parts;
	int				size;
	t_array_float	array;

	parts = ft_split(str, ',');
	size = 0;
	while (parts[size] != NULL)
	{
		if (size == 0)
			array.elem1 = ft_parse_float(parts[size]);
		if (size == 1)
			array.elem2 = ft_parse_float(parts[size]);
		if (size == 2)
			array.elem3 = ft_parse_float(parts[size]);
		size++;
	}
	if (size == 3
		&& ft_str_is_number(parts[0])
		&& ft_str_is_number(parts[1])
		&& ft_str_is_number(parts[2]))
		array.f_error = 0;
	else
		array.f_error = 1;
	ft_free_arrays(parts);
	return (array);
}
