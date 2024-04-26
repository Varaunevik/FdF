/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:47:10 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/26 11:17:16 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

/** This function will allocate data for our color matrix by
 * using the already found height and width. It will also fill
 * it with our default blue color.
**/
int	**init_colors(t_fdf *fdf)
{
	int	i;
	int	j;
	int	**colors;

	i = 0;
	colors = malloc(sizeof(int *) * fdf->height);
	if (!colors)
		(error(1), exit(1));
	while (i < fdf->height)
	{
		j = -1;
		colors[i] = malloc(sizeof(int) * fdf->width);
		if (!colors[i])
			(free_array(colors), error(1), exit(1));
		while (++j < fdf->width)
			colors[i][j] = 0xb6cde8;
		i++;
	}
	return (colors);
}

/** The following three functions take two colors, calculates
 * the fraction and calls the find_color function, effectively
 * filling the map with a gradient.
**/
void	palette_3(t_fdf *fdf)
{
	int		i;
	int		j;
	float	frac;

	i = 0;
	j = 0;
	frac = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->max != fdf->min)
				frac = fraction(fdf->min, fdf->max, fdf->map[i][j]);
			fdf->colored_map[i][j] = find_color(frac, 0xFFDE59, 0x99AEC4);
			j++;
		}
		i++;
	}
}

void	palette_2(t_fdf *fdf)
{
	int		i;
	int		j;
	float	frac;

	i = 0;
	j = 0;
	frac = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->max != fdf->min)
				frac = fraction(fdf->min, fdf->max, fdf->map[i][j]);
			fdf->colored_map[i][j] = find_color(frac, 0xF08BB1, 0xDED6C9);
			j++;
		}
		i++;
	}
}

void	palette_1(t_fdf *fdf)
{
	int		i;
	int		j;
	float	frac;

	i = 0;
	j = 0;
	frac = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->max != fdf->min)
				frac = fraction(fdf->min, fdf->max, fdf->map[i][j]);
			fdf->colored_map[i][j] = find_color(frac, 0xE8EEF2, 0x77B6EA);
			j++;
		}
		i++;
	}
}

/** This function extracts the individual color value from the min 
 * and max color and multiplies it with a fraction to calculate 
 * the gradient color in accordance with the current position 
 * of the coordinate.
 * It uses the function: r = r1 + (r2 - r1) * fraction for each R G B T.
 * Keep in mind this will differ depending on which operating system, 
 * this is little endian.
**/
int	find_color(float fraction, int max_color, int min_color)
{
	int	r;
	int	g;
	int	b;
	int	t;

	b = (min_color & 255) + ((max_color & 255)
			- (min_color & 255)) * fraction;
	g = ((min_color >> 8) & 255) + (((max_color >> 8) & 255)
			- ((min_color >> 8) & 255)) * fraction;
	r = ((min_color >> 16) & 255) + (((max_color >> 16) & 255)
			- ((min_color >> 16) & 255)) * fraction;
	t = ((min_color >> 24) & 255) + (((max_color >> 24) & 255)
			- ((min_color >> 24) & 255)) * fraction;
	return (t << 24 | r << 16 | g << 8 | b);
}
