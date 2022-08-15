/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:39:12 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 22:30:34 by lbraz-te         ###   ########.fr       */
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

typedef struct s_a
{
	float	ratio;
	int		color[3];
}	t_a;

typedef struct s_c
{
	float	view[3];
	int		vector[3];
	int		FOV;
}	t_c;

typedef struct s_l
{
	float	view[3];
	int		brightness;
}	t_l;

typedef struct s_pl
{
	float		view[3];
	int			vector[3];
	int			color[3];
	struct s_pl	*next;
}	t_pl;

typedef struct s_sp
{
	float		center[3];
	float		diameter;
	int			color[3];
	struct s_sp	*next;
}	t_sp;

typedef struct s_cy
{
	float		view[3];
	int			vector[3];
	float		diameter;
	float		height;
	int			color[3];
	struct s_cy	*next;
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
	ERR_N_AMBIENT,
	ERR_AMBIENT_ARGS
}	t_error_codes;

/* ft_errors */
int		ft_errors(int error_code);

/* ------------- utils ------------- */
/* ft_gnl */
char	*ft_strjoin(char *str1, char *str2);
char	*ft_strdup(char *str, char c);
char	*ft_subdup(char *str);
//int		ft_pass_norme(int fd, char **line, char *buf);
int		get_next_line(int fd, char **line);

/* ft_utils */
int		ft_check_line(char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(const char *str);
void	ft_free_arrays(char **array);
int		ft_strcmp(char *s1, char *s2);

/* ft_split */
// static int ft_words(char const *str, char del)
// static char *ft_strdpl(char const *str, char del, char *res, int *counter)
char	**ft_split(char const *s, char c);

/* --------- parsing folder ---------- */
/* ft_parse_elements */
int		ft_parse_ambient(char *line, t_elem *elements);

/* ft_parsing */
int		ft_start_parsing(char *scene_file);

/* ft_parsing_utils */
int		ft_parse_int(char *str);
float	ft_parse_float(char *str);
int		ft_parse_3int(char *str, int pos);
float	ft_parse_3float(char *str, int pos);

#endif