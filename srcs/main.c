/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:36:59 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/22 16:26:53 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

int main(int argc, char **argv)
{
    t_fdf	fdf;
	
	if (argc != 2)
		(perror(ARG_ERROR), exit(1));
	init_fdf(&fdf, argv[1]);
	make_cool(&fdf);
}
