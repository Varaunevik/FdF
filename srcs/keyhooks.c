/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:55:32 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/23 14:33:02 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

void	zoom(int keycode, t_fdf *fdf)
{
	if (keycode == ZOOM_IN)
		fdf->zoom += 1;
	else if (keycode == ZOOM_OUT && fdf->zoom > 0)
		fdf->zoom -= 1;
}

/** This function is in charge of updating the angles of the grid b and hence 
 * rotates the view in correspondance with the key that is being pressed.
**/
void	rotate(int keycode, t_fdf *fdf)
{
	if (keycode == ROTATE_Y)
		fdf->y_angle += 0.05;
	if (keycode == REVROT_Y)
		fdf->y_angle -= 0.05;
	if (keycode == ROTATE_X)
		fdf->x_angle -= 0.05;
	if (keycode == REVROT_X)
		fdf->x_angle += 0.05;
	if (keycode == ROTATE_Z)
		fdf->z_angle += 0.05;
	if (keycode == REVROT_Z)
		fdf->z_angle -= 0.05;
}

/** This function is in charge of updating the horizontal and vertical shift in 
 * view. It can be applied to any view, as it is only shifting the pixels and not
 * actually transforming any angle.
**/
void	shift(int keycode, t_fdf *fdf)
{
	if (keycode == UP)
		fdf->y_shift += 4;
	if (keycode == DOWN)
		fdf->y_shift -= 4;
	if (keycode == LEFT)
		fdf->x_shift -= 4;
	if (keycode == RIGHT)
		fdf->x_shift += 4;
}

/** This function is in charge of moving the elevation up or down
 * depending on the keycode pressed
**/
void	z_move(int keycode, t_fdf *fdf)
{
	if (keycode == Z_UP)
		fdf->z_height += 0.05;
	if (keycode == Z_DOWN)
		fdf->z_height -= 0.05;
}

void	change_color(t_fdf *fdf, int keycode)
{
	if (keycode == 18)
	{
		fdf->palette = 1;
		palette_1(fdf);
	}
	if (keycode == 19)
	{
		fdf->palette = 3;
		palette_2(fdf);
	}
	if (keycode == 20)
	{
		fdf->palette = 2;
		palette_3(fdf);
	}
	if (keycode == 21)
	{
		fdf->palette = 4;
		disco_disco(fdf);
	}
}

/** This function is in charge of the key press events. It will check
 * which key has been pressed and then call the corresponding functions
 * Then it will call the draw map function and put the correct image to the
 * window.
**/
int	handle_key(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == 53)
		exit_program(fdf);
	if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		shift(keycode, fdf);
	if (keycode == ROTATE_X || keycode == REVROT_X || keycode == ROTATE_Y
			|| keycode == REVROT_Y || keycode == ROTATE_Z || keycode == REVROT_Z)
		rotate(keycode, fdf);
	if (keycode == ZOOM_IN || keycode == ZOOM_OUT)
		zoom(keycode, fdf);
	if (keycode == Z_UP || keycode == Z_DOWN)
		z_move(keycode, fdf);
	handle_key2(keycode, fdf);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
				fdf->img->img_ptr, 0, 0);
	if (fdf->iso)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
					fdf->interface->isometric, 0, 0);
	else
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
					fdf->interface->parallel, 0, 0);
	return (0);
}

void	handle_key2(int keycode, t_fdf *fdf)
{
	if (keycode == TOP || keycode == SIDE)
    {
        fdf->iso = 0;
        parallel(fdf, keycode);
    }
    if (keycode == RESET)
        reset_view(fdf);
    if (keycode == 18 || keycode == 19 || keycode == 20)
        change_color(fdf, keycode);
    if (keycode == 21)
        disco_disco(fdf);
}
