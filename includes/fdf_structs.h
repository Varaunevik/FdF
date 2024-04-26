/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:20:41 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/26 12:53:34 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_STRUCTS_H
# define FDF_STRUCTS_H

# define WIDTH 1920
# define HEIGHT 1080
# define UP 126
# define DOWN 125
# define LEFT 124
# define RIGHT 123
# define ZOOM_IN 69
# define ZOOM_OUT 78
# define ROTATE_Z 89
# define REVROT_Z 92
# define ROTATE_X 91
# define REVROT_X 84
# define ROTATE_Y 86
# define REVROT_Y 88
# define Z_UP 32
# define Z_DOWN 2
# define RESET 49
# define TOP 17
# define SIDE 1
# define ESC 53

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_point
{
	int		x;
	int		y;
	float	z;
	int		color;
}	t_point;

/** This structure will contain void pointers to the image
 * of each panel
**/
typedef struct s_interface
{
	void	*isometric;
	void	*parallel;
	void	*start;
}	t_interface;

typedef struct s_panel
{
	int	width;
	int	height;
}	t_panel;

/** This is our main big structure that contains all information
 * and some pointers to other structures due to the norm.
**/
typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_interface	*interface;
	t_point		*a;
	t_point		*b;
	int			width;
	int			height;
	int			**map;
	int			**colored_map;
	float		x_angle;
	float		y_angle;
	float		z_angle;
	int			iso;
	int			max;
	int			palette;
	int			min;
	float		z_height;
	int			x_shift;
	int			y_shift;
	float		zoom;
	int			colors;
}	t_fdf;

#endif
