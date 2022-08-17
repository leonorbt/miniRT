/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:39:12 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/18 00:07:23 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h> //this is for debugging only so far
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_array_int
{
	int	f_error;
	int	elem1;
	int	elem2;
	int	elem3;
}	t_array_int;

typedef struct s_array_float
{
	int		f_error;
	float	elem1;
	float	elem2;
	float	elem3;
}	t_array_float;

typedef struct s_a
{
	float		ratio;
	t_array_int	color;
}	t_a;

typedef struct s_c
{
	t_array_float	view;
	t_array_int		vector;
	int				FOV;
}	t_c;

typedef struct s_l
{
	t_array_float	view;
	int				brightness;
}	t_l;

typedef struct s_pl
{
	t_array_float	view;
	t_array_int		vector;
	t_array_int		color;
	struct s_pl		*next;
}	t_pl;

typedef struct s_sp
{
	t_array_float	center;
	float			diameter;
	t_array_int		color;
	struct s_sp		*next;
}	t_sp;

typedef struct s_cy
{
	t_array_float	view;
	t_array_int		vector;
	float			diameter;
	float			height;
	t_array_int		color;
	struct s_cy		*next;
}	t_cy;

typedef struct s_elem
{
	int		has_ambient;
	t_a		ambient_light;
	int		has_camera;
	t_c		camera;
	int		has_light;
	t_l		light;
	int		n_plane;
	t_pl	*planes;
	int		n_sphere;
	t_sp	*spheres;
	int		n_cylinder;
	t_cy	*cylinders;
}	t_elem;

typedef enum e_error_codes
{
	ERR_N_ARGS = 1,
	ERR_FILE_TYPE,
	ERR_OPEN,
	ERR_CLOSE,
	ERR_ALPHA,
	ERR_N_AMBIENT,
	ERR_AMBIENT_ARGS,
	ERR_N_CAMERA,
	ERR_CAMERA_ARGS,
	ERR_N_LIGHT,
	ERR_LIGHT_ARGS,
	ERR_PLANE_ARGS
}	t_error_codes;

/* ft_errors */
int				ft_errors(int error_code);

/* ------------- utils ------------- */
/* ft_gnl */
char			*ft_strjoin(char *str1, char *str2);
char			*ft_strdup(char *str, char c);
char			*ft_subdup(char *str);
//int		ft_pass_norme(int fd, char **line, char *buf);
int				get_next_line(int fd, char **line);

/* ft_utils */
int				ft_check_line(char *str);
void			ft_putstr_fd(char *s, int fd);
int				ft_strlen(const char *str);
void			ft_free_arrays(char **array);
int				ft_strcmp(char *s1, char *s2);

/* ft_split */
// static int ft_words(char const *str, char del)
// static char *ft_strdpl(char const *str, char del, char *res, int *counter)
char			**ft_split(char const *s, char c);

/* --------- parsing folder ---------- */
/* ft_parse_elements */
int				ft_parse_ambient(char *line, t_elem *elements);
int				ft_parse_camera(char *line, t_elem *elements);
int				ft_parse_light(char *line, t_elem *elements);
int				ft_parse_plane(char *line, t_elem *elements);

/* ft_parsing */
int				ft_start_parsing(char *scene_file);

/* ft_parsing_utils */
int				ft_parse_int(char *str);
float			ft_parse_float(char *str);
t_array_int		ft_parse_3int(char *str);
t_array_float	ft_parse_3float(char *str);
int				ft_line_has_alpha(char *str);

#endif