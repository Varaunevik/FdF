#ifndef FDF_H
# define FDF_H

# include "fdf_structs.h"
# include "../libraries/minilibx_macos/mlx.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>

/*************DRAW_LINE.C*************/
void	draw_line(t_fdf *fdf);
void	slope_under_one(int dx, int dy, t_fdf *fdf);
void	slope_over_one(int dx, int dy, t_fdf *fdf);
void	my_mlx_pixel_put_under(int x, int y, t_fdf *fdf);
void	my_mlx_pixel_put_over(int x, int y, t_fdf *fdf);

/***********ERROR_UTILS.C**************/
int		exit_program(void *f);
void	free_array(int	**array);
int		check_file(char *s);

/***************FDF.C*****************/
void	init_fdf(t_fdf *fdf, char *file);
void	init_window(t_fdf *fdf);
void	make_cool(t_fdf	*fdf);

/****************COLOR.C***************/
int		**init_colors(t_fdf *fdf);
int		find_color(float z, int max_color, int min_color);
void 	disco_disco(t_fdf *fdf);
void    palette_1(t_fdf *fdf);
void    palette_2(t_fdf *fdf);
void    palette_3(t_fdf *fdf);

/***************KEYHOOKS.C************/
void	zoom(int keycode, t_fdf *fdf);
void	rotate(int keycode, t_fdf *fdf);
void	shift(int keycode, t_fdf *fdf);
void	z_move(int keycode, t_fdf *fdf);
int		handle_key(int keycode, void *param);
void    handle_key2(int keycode, t_fdf *fdf);
void	change_color(t_fdf *fdf, int keycode);

/*************MOUSEHOOKS.C*************/
int	handle_mouse_release(int button, int x, int y, void *param);
int	handle_mouse(int button, int x, int y, void *param);

/**************PARSE.C*****************/
int	store_value(int i, int j, t_fdf *fdf, char **line);
int	*get_row(t_fdf *fdf, char *line, int j);
int	**fill_map(t_fdf *fdf, int fd, int **map);
int	**make_map(t_fdf *fdf, char *file);

/************PERSPECTIVE.C**************/
void	isometric(t_fdf *fdf);
void	parallel(t_fdf *fdf, int keypress);
void	reset_view(t_fdf *fdf);
float	fraction(float min, float max, float current);

/************TRANSFORM.C****************/
void    rotate_x(t_fdf *fdf);
void    rotate_z(t_fdf *fdf);
void	rotate_y(t_fdf *fdf);
void	coordinates(t_fdf *fdf);

/****************UTILS.C*****************/
void	null_pointers(t_fdf *fdf);
void	null_interface(t_interface *interface);
int		get_width(char *file);
int		get_height(char *file);
void	read_file(t_fdf *fdf, char *file);

/****************IMAGE.C******************/
void	assign_coordinates(int x, int y, t_fdf *fdf);
void	draw_map(t_fdf *fdf);
void	make_img(t_fdf *fdf);
void	put_panel(t_fdf *fdf);

/**************STDUTILS.C****************/
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_atoi_base(char *line);
int		ft_tolower(int c);

/*************GET_NEXT_LINE.C************/
void	clean_list(t_list **list);
void	list_to_line(t_list *list, char **line);
void	create_list(t_list **list, int fd);
t_list	*read_to_node(int fd, int *read_count);
char	*get_next_line(int fd);

void	pass_over_node(t_list *list, t_list **pass_over);
void	create_line(t_list **list, char **line, int length);
int		find_newline(t_list *node);
void	free_list(t_list *list);

#endif
