/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:39:12 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 00:17:54 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h> //this is for debugging only so far
# include <unistd.h>
# include <fcntl.h>

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
	t_a		ambient_light;
	int		n_camera;
	t_c		*camera;
	int		n_light;
	t_l		*light;
	int		n_plane;
	t_pl	*plane;
	int		n_sphere;
	t_sp	*sphere;
	int		n_cylinder;
	t_cy	*cylinder;
}	t_elem;

typedef enum e_error_codes
{
	ERR_N_ARGS = 1,
	ERR_FILE_TYPE,
	ERR_OPEN,
	ERR_CLOSE,
	ERR_NO_CAM
}	t_error_codes;

/* ft_utils */
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(const char *str);

/* ft_errors */
int		ft_errors(int error_code);

/* ft_parsing */
int		ft_parsing(char *scene_file);

#endif