/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:59:34 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/24 15:34:17 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

/** This function calculates the slope of the current line 
 * we want to draw, and calls the corresponding line drawing
 * algorithms depending on whether they are under or below 1
**/
void	draw_line(t_fdf *fdf)
{
	int	dx;
	int	dy;

	fdf->a->z = fdf->map[(fdf->a->y + fdf->height / 2)]
	[(fdf->a->x + fdf->width / 2)] * fdf->z_height;
	fdf->b->z = fdf->map[(fdf->b->y + fdf->height / 2)]
	[(fdf->b->x + fdf->width / 2)] * fdf->z_height;
	fdf->a->color = fdf->colored_map[(fdf->a->y + fdf->height / 2)]
	[(fdf->a->x + fdf->width / 2)];
	fdf->b->color = fdf->colored_map[(fdf->b->y + fdf->height / 2)]
	[(fdf->b->x + fdf->width / 2)];
	coordinates(fdf);
	dx = fdf->b->x - fdf->a->x;
	dy = fdf->b->y - fdf->a->y;
	my_mlx_pixel_put_under(fdf->a->x, fdf->a->y, fdf);
	if (abs(dx) > abs(dy))
		slope_under_one(dx, dy, fdf);
	else
		slope_over_one(dx, dy, fdf);
}

/** This function applies the Bresenham algorithm to decide which 
 * picel to color to form our line between coordinate point a and b.
 * It chooses to either color y or y+1 depending on the p value.
 * x will always increase, except if it is negative, then it 
 * will always decrease.
**/
void	slope_under_one(int dx, int dy, t_fdf *fdf)
{
	int	p;
	int	i;

	i = -1;
	p = 2 * abs(dy) - abs(dx);
	while (++i < abs(dx))
	{
		if (dx > 0)
			fdf->a->x += 1;
		else
			fdf->a->x -= 1;
		if (p < 0)
			p = p + 2 * abs(dy);
		else
		{
			if (dy > 0)
				fdf->a->y += 1;
			else
				fdf->a->y -= 1;
			p = p + 2 * abs(dy) - 2 * abs(dx);
		}
		my_mlx_pixel_put_under(fdf->a->x, fdf->a->y, fdf);
	}
}

void	slope_over_one(int dx, int dy, t_fdf *fdf)
{
	int	p;
	int	i;

	i = -1;
	p = 2 * abs(dx) - abs(dy);
	while (++i < abs(dy))
	{
		if (dy > 0)
			fdf->a->y += 1;
		else
			fdf->a->y -= 1;
		if (p < 0)
			p = p + 2 * abs(dx);
		else
		{
			if (dx > 0)
				fdf->a->x += 1;
			else
				fdf->a->x -= 1;
			p = p + 2 * abs(dx) - 2 * abs(dy);
		}
		my_mlx_pixel_put_over(fdf->a->x, fdf->a->y, fdf);
	}
}

void	my_mlx_pixel_put_over(int x, int y, t_fdf *fdf)
{
	char	*addr;
	int		pixel;

	addr = fdf->img->addr;
	pixel = y * fdf->img->line_len + x * 4;
	if (x < WIDTH && x > 0 && y > 0 && y < HEIGHT)
	{
		addr[pixel + 0] = ((fdf->a->color) & 255)
			+ (((fdf->b->color) & 255) - ((fdf->a->color) & 255))
			* fraction(fdf->a->y, fdf->b->y, y);
		addr[pixel + 1] = ((fdf->a->color >> 8) & 255)
			+ (((fdf->b->color >> 8) & 255) - ((fdf->a->color >> 8) & 255))
			* fraction(fdf->a->y, fdf->b->y, y);
		addr[pixel + 2] = ((fdf->a->color >> 16) & 255)
			+ (((fdf->b->color >> 16) & 255) - ((fdf->a->color >> 16) & 255))
			* fraction(fdf->a->y, fdf->b->y, y);
		addr[pixel + 3] = ((fdf->a->color >> 24) & 255)
			+ (((fdf->b->color >> 24) & 255) - ((fdf->a->color >> 24) & 255))
			* fraction(fdf->a->y, fdf->b->y, y);
	}
}

void	my_mlx_pixel_put_under(int x, int y, t_fdf *fdf)
{
	char	*addr;
	int		pixel;

	addr = fdf->img->addr;
	pixel = y * fdf->img->line_len + x * 4;
	if (x < WIDTH && x > 0 && y > 0 && y < HEIGHT)
	{
		addr[pixel + 0] = ((fdf->a->color) & 255)
			+ (((fdf->b->color) & 255) - ((fdf->a->color) & 255))
			* fraction(fdf->a->x, fdf->b->x, x);
		addr[pixel + 1] = ((fdf->a->color >> 8) & 255)
			+ (((fdf->b->color >> 8) & 255) - ((fdf->a->color >> 8) & 255))
			* fraction(fdf->a->x, fdf->b->x, x);
		addr[pixel + 2] = ((fdf->a->color >> 16) & 255)
			+ (((fdf->b->color >> 16) & 255) - ((fdf->a->color >> 16) & 255))
			* fraction(fdf->a->x, fdf->b->x, x);
		addr[pixel + 3] = ((fdf->a->color >> 24) & 255)
			+ (((fdf->b->color >> 24) & 255) - ((fdf->a->color >> 24) & 255))
			* fraction(fdf->a->x, fdf->b->x, x);
	}
}
