/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:39:12 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/14 22:15:24 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>

typedef struct s_a
{
	float	ratio;
	int		red;
	int		green;
	int		blue;
}	t_a;

typedef struct s_c
{
	float	view_x;
	float	view_y;
	float	view_z;
	int		vector_x;
	int		vector_y;
	int		vector_z;
	int		FOV;
}	t_c;

typedef struct s_l
{
	float	view_x;
	float	view_y;
	float	view_z;
	int		brightness;
}	t_l;

typedef struct s_pl
{
	float	view_x;
	float	view_y;
	float	view_z;
	int		vector_x;
	int		vector_y;
	int		vector_z;
	int		red;
	int		green;
	int		blue;
}	t_pl;

typedef struct s_sp
{
	float	center_x;
	float	center_y;
	float	center_z;
	float	diameter;
	int		red;
	int		green;
	int		blue;
}	t_sp;

typedef struct s_cy
{
	float	view_x;
	float	view_y;
	float	view_z;
	int		vector_x;
	int		vector_y;
	int		vector_z;
	float	diameter;
	float	height;
	int		red;
	int		green;
	int		blue;
}	t_cy;

typedef struct s_elem
{
	int		error;
	t_a		ambient_light;
	int		n_camera;
	t_c		*camera:
	int		n_light;
	t_l		*light;
	int		n_plane;
	t_pl	*plane;
	int		n_sphere;
	t_sp	*sphere;
	int		n_cylinder;
	t_cy	*cylinder;
} t_elem;

t_elem	ft_parsing(char *scene_file);

#endif