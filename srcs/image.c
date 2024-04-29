/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:02:11 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/29 10:26:03 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

void	assign_coordinates(int x, int y, t_fdf *fdf)
{
	fdf->a->x = x;
	fdf->a->y = y;
	fdf->b->x = x;
	fdf->b->y = y;
}

void	make_img(t_fdf *fdf)
{
	int	*addr;
	int	i;

	fdf->img->addr = mlx_get_data_addr(fdf->img->img_ptr,
			&fdf->img->bpp, &fdf->img->line_len, &fdf->img->endian);
	addr = (int *)fdf->img->addr;
	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		addr[i] = 0x242323;
		i++;
	}
}

void	draw_map(t_fdf *fdf)
{
	t_point	a;
	t_point	b;
	int		x;
	int		y;

	make_img(fdf);
	fdf->a = &a;
	fdf->b = &b;
	x = -1;
	while (++x < fdf->width)
	{
		y = 0;
		while (y < fdf->height)
		{
			assign_coordinates(x - fdf->width / 2, y - fdf->height / 2, fdf);
			b.x += 1;
			if (x + 1 < fdf->width)
				draw_line(fdf);
			assign_coordinates(x - fdf->width / 2, y - fdf->height / 2, fdf);
			b.y += 1;
			if (y + 1 < fdf->height)
				draw_line(fdf);
			y++;
		}
	}
}

void	put_panel(t_fdf *fdf)
{
	t_panel	isometric;
	t_panel	parallel;
	t_panel	start;

	fdf->interface->isometric = mlx_xpm_file_to_image(fdf->mlx_ptr,
			"./xpm/Isometric", &isometric.width, &isometric.height);
	fdf->interface->parallel = mlx_xpm_file_to_image(fdf->mlx_ptr,
			"./xpm/Parallel", &parallel.width, &parallel.height);
	fdf->interface->start = mlx_xpm_file_to_image(fdf->mlx_ptr,
			"./xpm/start", &start.width, &start.height);
}
