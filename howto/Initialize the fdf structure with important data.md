# Initialize the fdf structure with important data

The fdf project is heavy on the structures, both from parsing colors, maps, integers, flags, but also when it comes to handling the mlx structures (such as the img structure). 

The key is really just to keep your tongue inside your mouth (actually I don’t know if that is an expression in English, it is in Norwegian, so pretend you know what I mean).

To at least start of in a good place, we will make sure to initiate all variables and to also NULL out all pointers. 

Lets first have a look at our main function. The shortest function in the whole program, yet the one who starts it all. 

```c
int main(int argc, char **argv)
{
    t_fdf	fdf;

	if (argc != 2)
		(perror(ARG_ERROR), exit(1));
	init_fdf(&fdf, argv[1]);
	make_cool(&fdf);
}
```

Yeah, looks pretty easy huh? Just initiate and make it cool.

Let’s start with the boring part, and then we’ll move onto the cool stuff. 

```c
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
	fdf->zoom = (WIDTH / fdf->width) / 4;
}
```

Here we check the filename (check_file), call the null_pointers function and obtain the height and width by calling corresponding functions with the filename. 

It is important to catch that we FIRST init_colors, because we need this allocated memory in the make_map function that we call under it. If we don’t have it already, we’ll get segmentation fault for trying to access data that does not exist (speaking from experience). 

Then we just set the z_height to 1, because we want to start with the height from the map, and we set the isometric flag to 1, as this is the standard view at beginning. 

The zoom is also set to (WIDTH / fdf→width) / 4 for optimal view. 

Time for cool things. 

```c
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
	panel(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
				fdf->interface->start, 0, 0);
	mlx_hook(fdf->win_ptr, 2, 0, &handle_key, fdf);
	mlx_hook(fdf->win_ptr, 4, 0, &handle_mouse, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, &exit_program, fdf);
	mlx_loop(fdf->mlx_ptr);
}
```

So, essentially this should probably be our main, because this is where things actually happen. 

We start off by nulling off the interface structure pointers, as we are good coders with good practices.

The two structures declared in this function is the interface one, which is in charge of the pointers to our three different panels (start panel, isometric panel and the parallel panel). We also init a img structure, as we want to create a new image in this function. 

We then call the init_window function with our fdf structure, which will start a new mlx session and store the mlx_ptr as well as the win_ptr in the appropriate space in our structure. 

Now that we have established both a session and a window, it is time to start making our window. 

First we set the address of each interface and img structure to the pointers in fdf, just so we can more easily manage and access them later in the program. 

Then we call our draw_map function, which is a BIG one we will get to later. 

Then our panel, which will convert the xpm files and put them in our image. 

We begin by putting the start panel to our window, by using mlx_put_image_to_window. 

THEN we begin creating hooks, which will sort of “wait” for something to be pushed or clicked, and take action correspondingly. 

We also have the mlx loop at the end, which means the window will keep running until the user exits the program.
