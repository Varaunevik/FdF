/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:47:12 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/25 14:48:11 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

/** The following functions are directly taken from the standard
 * 3D rotation matrix, and applied to both points we want to draw
 * a line between. These are separate from our isometric transformation
 * and will be called when user rotates using corresponding keys.
**/
void	rotate_x(t_fdf *fdf)
{
	int	tmp;

	tmp = fdf->a->y;
	fdf->a->y = tmp * cos(fdf->x_angle) - fdf->a->z * sin(fdf->x_angle);
	fdf->a->z = tmp * sin(fdf->x_angle) + fdf->a->z * cos(fdf->x_angle);
	tmp = fdf->b->y;
	fdf->b->y = tmp * cos(fdf->x_angle) - fdf->b->z * sin(fdf->x_angle);
	fdf->b->z = tmp * sin(fdf->x_angle) + fdf->b->z * cos(fdf->x_angle);
}

void	rotate_z(t_fdf *fdf)
{
	int	tmp;

	tmp = fdf->a->x;
	fdf->a->x = tmp * cos(fdf->z_angle) - fdf->a->y * sin(fdf->z_angle);
	fdf->a->y = tmp * sin(fdf->z_angle) + fdf->a->y * cos(fdf->z_angle);
	tmp = fdf->b->x;
	fdf->b->x = tmp * cos(fdf->z_angle) - fdf->b->y * sin(fdf->z_angle);
	fdf->b->y = tmp * sin(fdf->z_angle) + fdf->b->y * cos(fdf->z_angle);
}

void	rotate_y(t_fdf *fdf)
{
	int	tmp;

	tmp = fdf->a->x;
	fdf->a->x = tmp * cos(fdf->y_angle) + fdf->a->z * sin(fdf->y_angle);
	fdf->a->z = fdf->a->z * cos(fdf->y_angle) - tmp * sin(fdf->y_angle);
	tmp = fdf->b->x;
	fdf->b->x = tmp * cos(fdf->y_angle) + fdf->b->z * sin(fdf->y_angle);
	fdf->b->z = fdf->b->z * cos(fdf->y_angle) - tmp * sin(fdf->y_angle);
}

/** This function updates the points/coordinates before being drawn
 * to our image. It takes into consideration the panel which is of 
 * width 300 pixels. 
**/
void	transformer(t_fdf *fdf)
{
	fdf->a->x *= fdf->zoom;
	fdf->b->x *= fdf->zoom;
	fdf->a->y *= fdf->zoom;
	fdf->b->y *= fdf->zoom;
	fdf->a->z *= fdf->zoom;
	fdf->b->z *= fdf->zoom;
	rotate_x(fdf);
	rotate_y(fdf);
	rotate_z(fdf);
	if (fdf->iso)
		isometric(fdf);
	fdf->a->x += 300 + (WIDTH - 300) / 2 + fdf->x_shift;
	fdf->b->x += 300 + (WIDTH - 300) / 2 + fdf->x_shift;
	fdf->a->y += HEIGHT / 2 + fdf->y_shift;
	fdf->b->y += HEIGHT / 2 + fdf->y_shift;
}
