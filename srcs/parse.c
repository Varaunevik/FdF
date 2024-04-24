/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:37:46 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/22 16:25:58 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

/** This function converts the ascii value in each position to integer
 * If there is a comma present it signifies that there is a color, which
 * is why we update color flag and convert the string hex to hex and store it 
 * in the same position that we are on in the color-map.
 * We then iterate through the rest of the string and whitespace before returning
 * the integer value.
**/
int	store_value(int i, int j, t_fdf *fdf, char **line)
{
	int	value;

	value = ft_atoi(*line);
	while (**line && ft_isdigit(**line))
		(*line)++;
	if (**line == ',')
	{
		if (!fdf->colors)
			fdf->colors = 1;
		(*line)++;
		fdf->colored_map[j][i] = ft_atoi_base(*line);
	}
	while (**line && **line != ' ')
		(*line)++;
	while (**line && **line == ' ')
		(*line)++;
	return (value);
}

/** This function will allocate space for the rows. 
 * It iterates through the row by calling the store_value function
 * It then checks whether the current value is bigger than the last
 * If it is bigger, then we update the max. We do the same with the
 * min by comparing to the previous min value.
 * We need the max/min values when calculating our gradient colors.
 **/
int	*get_row(t_fdf *fdf, char *line, int j)
{
	int	*row;
	int	i;

	row = malloc(sizeof(int) * fdf->width);
	if (!row)
		return (NULL);
	i = 0;
	while (*line && *line == ' ')
		line++;
	while (i < fdf->width)
	{
		row[i] = store_value(i, j, fdf, &line);
		if (row[i] > fdf->max)
			fdf->max = row[i];
		if (row[i] < fdf->min)
			fdf->min = row[i];
		i++;
	}
	return (row);
}

/** This function will be filling each of the lines by calling gnl
 * Until reaching EOF (height is 0). Then it calls the get_row to fill 
 * the current row/line. 
**/
int	**fill_map(t_fdf *fdf, int fd, int **map)
{
	int		i;
	char	*line;

	i = 0;
	while (i < fdf->height)
	{
		line = get_next_line(fd);
		if (!line)
			(free_array(map), close(fd), perror(READ_ERR), exit(1));
		map[i] = get_row(fdf, line, i);
		if (!map[i])
			(free_array(map), close(fd), perror(ERR_MALLOC), exit(1));
		free(line);
		i++;
	}
	return (map);
}

/** This function will allocate space for each row (line) in our 
 * map. It also opens the file and call the fill_map function 
 * with our file descriptor. Lastly it closes the file and 
 * returns the filled map, if no error occured
**/
int	**make_map(t_fdf *fdf, char *file)
{
	int	**map;
	int	fd;

	map = malloc(sizeof(int *) * (fdf->height));
	if (!map)
		(perror(ERR_MALLOC), exit(1));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		(free(map), perror(ERR_OPEN), exit(1));
	fill_map(fdf, fd, map);
	close(fd);
	return (map);
}
