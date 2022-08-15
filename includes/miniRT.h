/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:39:12 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/08/15 11:58:26 by lbraz-te         ###   ########.fr       */
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

typedef struct s_a
{
	float	ratio;
	int		red;
	int		green;
	int		blue;
}	t_a;

typedef struct s_c
{
	float		view_x;
	float		view_y;
	float		view_z;
	int			vector_x;
	int			vector_y;
	int			vector_z;
	int			FOV;
	struct s_c	*next;
}	t_c;

typedef struct s_l
{
	float		view_x;
	float		view_y;
	float		view_z;
	int			brightness;
	struct s_l	*next;
}	t_l;

typedef struct s_pl
{
	float		view_x;
	float		view_y;
	float		view_z;
	int			vector_x;
	int			vector_y;
	int			vector_z;
	int			red;
	int			green;
	int			blue;
	struct s_pl	*next;
}	t_pl;

typedef struct s_sp
{
	float		center_x;
	float		center_y;
	float		center_z;
	float		diameter;
	int			red;
	int			green;
	int			blue;
	struct s_sp	*next;
}	t_sp;

typedef struct s_cy
{
	float		view_x;
	float		view_y;
	float		view_z;
	int			vector_x;
	int			vector_y;
	int			vector_z;
	float		diameter;
	float		height;
	int			red;
	int			green;
	int			blue;
	struct s_cy	*next;
}	t_cy;

typedef struct s_elem
{
	int		has_ambient;
	t_a		ambient_light;
	int		n_camera;
	t_c		camera;
	int		n_light;
	t_l		light;
	int		n_plane;
	t_pl	plane;
	int		n_sphere;
	t_sp	sphere;
	int		n_cylinder;
	t_cy	cylinder;
}	t_elem;

typedef enum e_error_codes
{
	ERR_N_ARGS = 1,
	ERR_FILE_TYPE,
	ERR_OPEN,
	ERR_CLOSE,
	ERR_N_AMBIENT
}	t_error_codes;

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

/* ft_errors */
int		ft_errors(int error_code);


/* --------- parsing folder ---------- */
/* ft_parse_elements */
int		ft_parse_ambient(char *line, t_elem *elements);

/* ft_parsing */
int		ft_start_parsing(char *scene_file);

#endif