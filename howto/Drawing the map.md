# Drawing the map

As mentioned, this is the “heaviest” part of the program, at least it was for me. 

There is a lot of things that needs to be taken into consideration, so let’s just start. 

So this function is responsible for calling the mlx_get_data_addr function and stores the result in our img structure. This essentially is an array of all the pixels in our window, and we need it to later modify so we can create our own window. 

The standard color of all the pixels is just black, however, I wanted it a little less harsh, so I set all the pixels in the array to a greyish color instead.

```c
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
```

Now, we want to draw the line between all of our points. For example, the first number in our map would be the point (0, 0), with the value stored there (from our get_map function earlier), being the height. 

```c

void	draw_map(t_fdf *fdf)
{
	t_point	a;
	t_point	b;
	int		x;
	int		y;

	make_img(fdf);
	fdf->a = &a;
	fdf->b = &b;
	x = 0;
	while (x < fdf->width)
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
		x++;
	}
}
```

This algorithm essentially iterates through all the coordinates. It is a little difficult to understand, so I created this visual for better understanding:

![image](https://github.com/Varaunevik/FdF/assets/145858191/a5e6d12f-b96d-41ff-9549-bd8ed1737612)
![image](https://github.com/Varaunevik/FdF/assets/145858191/3b90885e-77e6-4d52-8340-95ec2cd4f5f1)
![image](https://github.com/Varaunevik/FdF/assets/145858191/9b8a66a8-af24-41be-b29e-10fc6827ccf5)
![image](https://github.com/Varaunevik/FdF/assets/145858191/d253b017-a165-4e37-9fec-0aabf1c6b798)
![image](https://github.com/Varaunevik/FdF/assets/145858191/f7c8ce42-e5ee-40bf-b07b-cee13e6c9fa2)


You get the gist?

Now, the assign_coordinates function simply just takes the x and the y and assigns them to the a and b points in the structure. 

```c
void	assign_coordinates(int x, int y, t_fdf *fdf)
{
	fdf->a->x = x;
	fdf->a->y = y;
	fdf->b->x = x;
	fdf->b->y = y;
}
```

The next step will be drawing the line, so prepare yourself for a pretty tough line drawing algorithm, or pretty cool, depending on how you see it.
