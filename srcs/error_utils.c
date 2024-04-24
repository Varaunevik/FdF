/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:11:17 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/22 14:16:19 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (*(s1 + i) && *(s2 + i) && *(s1 + i) == *(s2 + i))
		i++;
	return (*(s1 + i) - *(s2 + i));
}

int	exit_program(void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	exit(0);
}

void	free_array(int	**array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

/** This function checks whether the file given as input is in the correct format
 * aka. checking whether it ends with .fdf
**/
int	check_file(char *s)
{
	int	i;

	if (!*s)
		return (0);
	i = 0;
	while (*(s + i))
		i++;
	i--;
	while (*(s + i) != '.' && i >= -1)
		i--;
	if (i == -1)
		return (0);
	if (!ft_strcmp(s + i, ".fdf"))
		return (1);
	return (0);
}
