/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:59:51 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/29 10:14:22 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

/** This function is what creates the isometric view by applying
 * the isometric transformation matrix to the coordinates (30deg). 
 * it is important that this is done after the rotations so 
 * they don't get skewed and out of proportion.
**/
void	isometric(t_fdf *fdf)
{
	int	tmp;

	tmp = fdf->a->x;
	fdf->a->x = (tmp - fdf->a->y) * cos(0.523599);
	fdf->a->y = (tmp + fdf->a->y) * sin(0.523599) - fdf->a->z;
	tmp = fdf->b->x;
	fdf->b->x = (tmp - fdf->b->y) * cos(0.523599);
	fdf->b->y = (tmp + fdf->b->y) * sin(0.523599) - fdf->b->z;
}

/** This is our other view, we simply just set the 
 * angles to match the perspective.
**/
void	parallel(t_fdf *fdf, int keypress)
{
	if (keypress == TOP)
	{
		fdf->x_angle = 0;
		fdf->y_angle = 0;
		fdf->z_angle = 0;
	}
	else if (keypress == SIDE)
	{
		fdf->x_angle = 1.5707;
		fdf->y_angle = 0;
		fdf->z_angle = 0;
	}
}

/** This function is called whenever the user
 * is pressing the reset button, and it simply
 * resets the variables to their original value
**/
void	reset_view(t_fdf *fdf)
{
	fdf->zoom = (WIDTH / fdf->width) / 3;
	fdf->x_angle = 0;
	fdf->y_angle = 0;
	fdf->z_angle = 0;
	fdf->z_height = 1;
	fdf->x_shift = 0;
	fdf->y_shift = 0;
	fdf->iso = 1;
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
		fdf->img->img_ptr, 0, 0);
	if (fdf->iso)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
			fdf->interface->isometric, 0, 0);
	else
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
			fdf->interface->parallel, 0, 0);
}

/** This function calculates the current position on a scale
 * from 1 to 0, where 1 is the max and 0 is the min value.
**/
float	fraction(float min, float max, float current)
{
	if (min != max)
		return ((current - min) / (max - min));
	return (0);
}
