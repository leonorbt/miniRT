/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraz-te <lbraz-te@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:39:12 by lbraz-te          #+#    #+#             */
/*   Updated: 2022/09/21 01:29:46 by lbraz-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 800
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 600
# endif

# ifndef KEY_ESCAPE
#  if __APPLE__
#   define KEY_ESC 53
#  else
#   define KEY_ESC 65307
#  endif
# endif

# include <stdio.h> //this is for debugging only so far
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include "mlx.h"

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
	t_array_float	vector;
	int				fov;
	float			cam_to_world[4][4];
}	t_c;

typedef struct s_l
{
	t_array_float	view;
	float			brightness;
	t_array_int		color;
	struct s_l		*next;
}	t_l;

typedef struct s_pl
{
	t_array_float	view;
	t_array_float	vector;
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
	t_array_float	vector;
	float			diameter;
	float			height;
	t_array_int		color;
	struct s_cy		*next;
}	t_cy;

typedef struct s_tr
{
	t_array_float	p1;
	t_array_float	p2;
	t_array_float	p3;
	t_array_float	normal;
	float			area;
	t_array_int		color;
	struct t_tr		*next;
}	t_tr;

typedef struct s_obj
{
	t_pl			*plane;
	t_sp			*sphere;
	t_cy			*cylinder;
	t_tr			*triangle;
	struct s_obj	*next;
}	t_obj;

typedef struct s_elem
{
	int		has_ambient;
	t_a		ambient_light;
	int		has_camera;
	t_c		camera;
	t_l		*lights;
	t_obj	*obj_list;
}	t_elem;

typedef struct s_ray
{
	t_array_float	direction;
	float			t;
	t_array_float	intersection;
	t_array_float	normal;
	t_array_int		color;
}	t_ray;

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
	ERR_PLANE_ARGS,
	ERR_SPHERE_ARGS,
	ERR_CYLINDER_ARGS,
	ERR_TRIANGLE_ARGS,
	ERR_OBJS
}	t_error_codes;

typedef struct s_window
{
	void	*mlx;
	void	*mlx_win;
	t_elem	*elements;
}	t_window;

typedef struct s_mlx_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx_img;

/* debug */
void			debug_print(t_elem *elements);

/* ft_errors */
int				ft_errors(int error_code);

/* --------- rendering folder ---------- */
/* ray_dir */
//t_array_float	ft_raster_ndc(int pixel_x, int pixel_y)
//t_array_float	ft_pixel_to_canvas(int pixel_x, int pixel_y, t_elem *elements)
t_array_float	get_ray_dir(int pixel_x, int pixel_y, t_elem *elements);

/* draw */
//void	my_mlx_pixel_put(t_mlx_img *img_data, int x, int y, t_array_int rgb)
//static void	draw_core(int x, int y, t_mlx_img img, t_elem elements)
void			draw(t_window *mlx_data);

/* ray_casting */
t_array_float	get_intersection(t_array_float ray_orig, t_ray ray);
bool			in_shadow(t_array_float ray_orig, t_ray *ray, t_elem *elements);
bool			ray_intersect(t_array_float ray_orig, t_ray *ray,
					t_elem *elements);
void			sphere(t_array_float ray_orig, t_ray *ray, t_sp *sphere);
void			plane(t_array_float ray_orig, t_ray *ray, t_pl *plane);
void			cylinder(t_array_float ray_orig, t_ray *ray, t_cy *cylinder);
void			bottom_cap(t_array_float ray_orig, t_ray *ray, t_cy *cylinder);
void			top_cap(t_array_float ray_orig, t_ray *ray, t_cy *cylinder);
void			triangle(t_array_float ray_orig, t_ray *ray, t_tr *triangle);

/* colors */
t_array_int		color_ratio(t_array_int color, float ratio);
t_array_int		color_add(t_array_int color, t_array_int color2);
t_array_int		color_multiply(t_array_int color1, t_array_int color2);
int				rgb_to_color(t_array_int rgb);

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

/* ft_vector_math */
float			v_length(t_array_float vector);
t_array_float	v_normalize(t_array_float vector);
t_array_float	v_subtract(t_array_float v1, t_array_float v2);
t_array_float	v_cross_product(t_array_float v1, t_array_float v2);
t_array_float	m_multiply(t_array_float vector, t_c cam);
float			v_dot_product(t_array_float v1, t_array_float v2);
t_array_float	v_scale(t_array_float vector, float f);
t_array_float	v_add(t_array_float v1, t_array_float v2);

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
int				ft_parse_sphere(char *line, t_elem *elements);
int				ft_parse_cylinder(char *line, t_elem *elements);
int				ft_parse_triangle(char *line, t_elem *elements);

/* ft_parsing */
int				ft_start_parsing(char *scene_file, t_elem *elements);

/* ft_parsing_utils */
int				ft_parse_int(char *str);
float			ft_parse_float(char *str);
t_array_int		ft_parse_3int(char *str);
t_array_float	ft_parse_3float(char *str);
int				ft_line_has_alpha(char *str);
int				ft_str_is_number(char *str);

/* ft_object_list */
void			ft_free_obj_list(t_obj *lst);
void			ft_lstadd_back_obj_plane(t_obj **lst, t_pl **plane);
void			ft_lstadd_back_obj_sphere(t_obj **lst, t_sp **sphere);
void			ft_lstadd_back_obj_cylinder(t_obj **lst, t_cy **cylinder);
void			ft_lstadd_back_obj_triangle(t_obj **lst, t_tr **triangle);

void			quadratic_function(t_array_float params, float *t0, float *t1);

#endif
