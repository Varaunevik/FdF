/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:54:56 by vaunevik          #+#    #+#             */
/*   Updated: 2024/04/24 12:05:30 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

/** This function simply just initializes the fdf structure and 
 * sets all values either to 0 or it calls corresponding functions.
**/
void	init_fdf(t_fdf *fdf, char *file)
{
	if (!check_file(file))
		(perror(FILE_ERR), exit(1));
	null_pointers(fdf);
	fdf->width = get_width(file);
	fdf->height = get_height(file);
	fdf->colors = 0;
	fdf->min = 0;
	fdf->max = 0;
	fdf->colored_map = init_colors(fdf);
	fdf->map = make_map(fdf, file);
	fdf->x_angle = 0;
	fdf->y_angle = 0;
	fdf->z_angle = 0;
	fdf->z_height = 1;
	fdf->x_shift = 0;
	fdf->y_shift = 0;
	fdf->palette = 0;
	fdf->iso = 1;
	fdf->zoom = (WIDTH / fdf->width) / 3;
}

/** This function initializes our window and stores the pointer to the session and
 * to the window in our fdf struct. 
**/
void	init_window(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		(perror(MLX_INIT), exit(1));
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "fdf");
	if (!fdf->win_ptr)
		(perror(MLX_WIN), exit(1));
}

/** This function initialises the window and all the hook functions. 
 * We will have a hook for all our mouse events as well as the esc keypress command. 
 * In this case we want to exit the program. We continue the loop infinite number (until exit program)
**/
void	make_cool(t_fdf	*fdf)
{
	t_interface	interface;
	t_img		img;

	null_interface(&interface);
	img.img_ptr = NULL;
	img.addr = NULL;
	init_window(fdf);
	img.img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	if (!img.img_ptr)
		(perror(MLX_IMG),
		 	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr), exit(1));
	fdf->interface = &interface;
	fdf->img = &img;
	draw_map(fdf);
	put_panel(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
				fdf->interface->start, 0, 0);
	mlx_hook(fdf->win_ptr, 2, 0, &handle_key, fdf);
	mlx_hook(fdf->win_ptr, 4, 0, &handle_mouse, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, &exit_program, fdf);
	mlx_loop(fdf->mlx_ptr);
}
