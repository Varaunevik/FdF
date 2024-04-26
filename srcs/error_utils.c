/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:11:17 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/26 12:19:32 by vaunevik         ###   ########.fr       */
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

/** This function checks whether the file given as input is in
 * the correct format aka. checking whether it ends with .fdf
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

void	error(int code)
{
	if (code == 1)
		ft_putstr_fd("Error: Malloc allocation failed", 2);
	if (code == 2)
		ft_putstr_fd("Error: Reading failure", 2);
	if (code == 3)
		ft_putstr_fd("Error: Wrong number of arguments", 2);
	if (code == 4)
		ft_putstr_fd("Error: Wrong file format, expected .fdf", 2);
	if (code == 5)
		ft_putstr_fd("Error: File is empty", 2);
	if (code == 6)
		ft_putstr_fd("Error: Cannot open window", 2);
	if (code == 7)
		ft_putstr_fd("Error: Cannot initiate session", 2);
	if (code == 8)
		ft_putstr_fd("Error: Cannot create image", 2);
	if (code == 9)
		ft_putstr_fd("Error: Cannot open file", 2);
	if (code == 10)
		ft_putstr_fd("Don't be crazy. Why would you pass such a large z-value?", 2);
}
