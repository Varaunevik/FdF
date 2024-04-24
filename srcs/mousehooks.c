/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:57:36 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/24 16:09:27 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

/** This function will handle all potential mouse events, such as
 * when clicking the panel buttons or zooming in/out by using the scroller.
 * It will then check whether the button is pressed and set the flag to one. 
 * Lastly it will create a new image based on the mouse action and push it to 
 * our mlx window. 
**/
int	handle_mouse(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (button == 1 && (x >= 0 && x <= 150)
		&& (y >= 212 && y <= 265))
	{
		if (fdf->iso == 0)
		{
			fdf->x_angle = 0;
			fdf->z_angle = 0;
			fdf->y_angle = 0;
		}
		isometric(fdf);
		fdf->iso = 1;
	}
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
		fdf->img->img_ptr, 0, 0);
	if (fdf->iso == 0)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
			fdf->interface->parallel, 0, 0);
	else
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
			fdf->interface->isometric, 0, 0);
	return (0);
}

void	handle_mouse2(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1 && (x >= 151 && x <= 300)
		&& (y >= 212 && y <= 265))
	{
		parallel(fdf, 1);
		fdf->iso = 0;
	}
	else if (button == 1 && (x >= 106 && x <= 193)
		&& (y >= 296 && y <= 328))
		reset_view(fdf);
	if (button == 4)
		zoom(ZOOM_IN, fdf);
	if (button == 5)
		zoom(ZOOM_OUT, fdf);
}

void	zoom(int keycode, t_fdf *fdf)
{
	if (keycode == ZOOM_IN)
		fdf->zoom += 1;
	else if (keycode == ZOOM_OUT && fdf->zoom > 0)
		fdf->zoom -= 1;
}
