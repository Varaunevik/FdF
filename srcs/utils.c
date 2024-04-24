/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:34:43 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/22 16:18:32 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

void	null_pointers(t_fdf *fdf)
{
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->img = NULL;
	fdf->map = NULL;
	fdf->interface = NULL;
	fdf->a = NULL;
	fdf->b = NULL;
}

void	null_interface(t_interface *interface)
{
	interface->isometric = NULL;
	interface->parallel = NULL;
	interface->start = NULL;
}

int	wordcount(char *line)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			words++;
		while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			i++;
	}
	return (words);
}

int	get_height(char *file)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		(perror(ERR_OPEN), exit(1));
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			return (i);
		}
		free(line);
		i++;
	}
	close(fd);
	return (i);
}

int	get_width(char *file)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		(perror(ERR_OPEN), exit(1));
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (i);
	}
	i = wordcount(line);
	free(line);
	close(fd);
	return (i);
}
