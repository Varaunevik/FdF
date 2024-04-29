# Line Drawing Algorithm

Oh the beloved Bresenham’s line drawing algorithm. You better believe we will be using it. 

Now, we need to know the height (the z value we stored earlier), in order to actually draw the map properly. We also need the colors (if not already provided in the map file). These are extracted by using the current coordinates, the z value will be multiplied with the height, as we are implementing a z-up/down key.

Then we call our coordinate function which will perform all translations and transformations, including our isometric projection. 

Then we put the first pixel (the first point, hence using a), and check whether the slope is less or bigger than 1, as we will need different functions for each scenario. 

```c
void	draw_line(t_fdf *fdf)
{
	int	dx;
	int	dy;

	fdf->a->z = fdf->map[(fdf->a->y + fdf->height / 2)]
				[(fdf->a->x + fdf->width / 2)] * fdf->z_height;
	fdf->b->z = fdf->map[(fdf->b->y + fdf->height / 2)]
				[(fdf->b->x + fdf->width / 2)] * fdf->z_height;
	fdf->a->color = fdf->colored_map[(fdf->a->y + fdf->height / 2)]
				[(fdf->a->x + fdf->width / 2)];
	fdf->b->color = fdf->colored_map[(fdf->b->y + fdf->height / 2)]
				[(fdf->b->x + fdf->width / 2)];
	coordinates(fdf);
	dx = fdf->b->x - fdf->a->x;
	dy = fdf->b->y - fdf->a->y;
	my_mlx_pixel_put_under(fdf->a->x, fdf->a->y, fdf);
	if (abs(dx) > abs(dy))
		slope_under_one(dx, dy, fdf);
	else
		slope_over_one(dx, dy, fdf);
}
```

Now, if the slope is under one, we have the following function. This is the whole algorithm, yes, but that does not mean it is easy. 

In order to understand everything that is actually going on, I would recommend watching this video. 

Then come back. 

Ok. 

Let’s continue. 

Now, you probably know what the p value signifies. It is the decision variable which helps us decide what pixel to draw, or, whether to increase the y coordinate or keep it (or X, depending on the slope). 

We also utilise the absolute value, in case we have a negative slope under -1 or a negative slope above -1. The method is the same even though we have negative numbers. So by using the absolute value we can stick to only two different functions although there could be multiple scenarios. 

```c

void	slope_under_one(int dx, int dy, t_fdf *fdf)
{
	int	p;
	int i;

	i = -1;
	p = 2 * abs(dy) - abs(dx);
	while (++i < abs(dx))
	{
		if (dx > 0)
			fdf->a->x += 1;
		else
			fdf->a->x -= 1;
		if (p < 0)
			p = p + 2 * abs(dy);
		else
		{
			if (dy > 0)
				fdf->a->y += 1;
			else
				fdf->a->y -= 1;
			p = p + 2 * abs(dy) - 2 * abs(dx);
		}
		my_mlx_pixel_put_under(fdf->a->x, fdf->a->y, fdf);
	}
}

void	slope_over_one(int dx, int dy, t_fdf *fdf)
{
	int p;
	int i;

	i = -1;
	p = 2 * abs(dx) - abs(dy);
	while (++i < abs(dy))
	{
		if (dy > 0)
			fdf->a->y += 1;
		else
			fdf->a->y -= 1;
		if (p < 0)
			p = p + 2 * abs(dx);
		else
		{
			if (dx > 0)
				fdf->a->x += 1;
			else
				fdf->a->x -= 1;
			p = p + 2 * abs(dx) - 2 * abs(dy);
		}
		my_mlx_pixel_put_over(fdf->a->x, fdf->a->y, fdf);
	}
}
```

Now, let’s dive into the formula behind the algorithm.

You may be wondering what this p value is (which is very fair). 

Imagine you have a line that is going through two pixels - which one do we chose?

![image](https://github.com/Varaunevik/FdF/assets/145858191/1aa68b6e-3317-4d8a-896c-af78f9ab6767)
![image](https://github.com/Varaunevik/FdF/assets/145858191/f6315573-2cdd-479e-ad68-ebc11555bade)
![image](https://github.com/Varaunevik/FdF/assets/145858191/8fb3b56e-9d59-4931-8dbe-31f98c5b9573)
![image](https://github.com/Varaunevik/FdF/assets/145858191/5eca320e-1729-483a-b585-a71b0c135081)
![image](https://github.com/Varaunevik/FdF/assets/145858191/4adeb405-3288-477f-9573-802c89d33f96)
![image](https://github.com/Varaunevik/FdF/assets/145858191/29fe22b4-e958-44e5-b7dd-bf39083a53e9)
![image](https://github.com/Varaunevik/FdF/assets/145858191/7ab536be-8abe-4f30-8169-e81282037879)
![image](https://github.com/Varaunevik/FdF/assets/145858191/1b3042f9-0e08-41fc-951c-0a6d2067cc75)


I won’t lie, this part was possibly the trickiest part for me to understand, as I haven’t really dealt with pixels before. 

If you don’t already know, a pixel consists of 24 bits, or, 4 bytes. Each byte is a different color value - Transparent, Red, Green and Blue.

Additionally, our addr array is actually a single array, not a 2D matrix like our map. Therefore, we have to figure out the pixel position in our single array by converting from the 2d coordinates we have. 

Imagine the pixel screen being a 2D array of 1020x1280 pixels. This means we have 1020 rows of 1280 pixels each. 

Now, if we want to color the pixel at coordinate (200, 304), we have to convert to single array. 

To obtain the correct position, we have to first multiply the y coordinate with the line length (the line length is the amount of bytes in one row, so if we have 1280 pixels with 4 bytes each - the line length would be 1280 * 4). 

This is also why we need to iterate through the current pos and the next three ones, because these four will consitute the whole pixel, each byte keeping one color. 

![image](https://github.com/Varaunevik/FdF/assets/145858191/0e66fd20-1214-4531-aea6-dece546433b0)


```c
void	my_mlx_pixel_put_over(int x, int y, t_fdf *fdf)
{
	char	*addr;
	int		pixel;

	addr = fdf->img->addr;
	pixel = y * fdf->img->line_len + x * 4;
	if (x < WIDTH && x > 0 && y > 0 && y < HEIGHT)
	{
		addr[pixel + 0] = ((fdf->a->color) & 255) + (((fdf->b->color) & 255)
				- ((fdf->a->color) & 255)) * fraction(fdf->a->y, fdf->b->y, y);
		addr[pixel + 1] = ((fdf->a->color >> 8) & 255) + (((fdf->b->color >> 8) & 255)
				- ((fdf->a->color >> 8) & 255)) * fraction(fdf->a->y, fdf->b->y, y);
		addr[pixel + 2] = ((fdf->a->color >> 16) & 255) + (((fdf->b->color >> 16) & 255)
				- ((fdf->a->color >> 16) & 255)) * fraction(fdf->a->y, fdf->b->y, y);
		addr[pixel + 3] = ((fdf->a->color >> 24) & 255) + (((fdf->b->color >> 24) & 255)
				- ((fdf->a->color >> 24) & 255)) * fraction(fdf->a->y, fdf->b->y, y);
	}
}

void	my_mlx_pixel_put_under(int x, int y, t_fdf *fdf)
{
	char	*addr;
	int		pixel;

	addr = fdf->img->addr;
	pixel = y * fdf->img->line_len + x * 4;
	if (x < WIDTH && x > 0 && y > 0 && y < HEIGHT)
	{
		addr[pixel + 0] = ((fdf->a->color) & 255) + (((fdf->b->color) & 255)
				- ((fdf->a->color) & 255)) * fraction(fdf->a->x, fdf->b->x, x);
		addr[pixel + 1] = ((fdf->a->color >> 8) & 255) + (((fdf->b->color >> 8) & 255)
				- ((fdf->a->color >> 8) & 255)) * fraction(fdf->a->x, fdf->b->x, x);
		addr[pixel + 2] = ((fdf->a->color >> 16) & 255) + (((fdf->b->color >> 16) & 255)
				- ((fdf->a->color >> 16) & 255)) * fraction(fdf->a->x, fdf->b->x, x);
		addr[pixel + 3] = ((fdf->a->color >> 24) & 255) + (((fdf->b->color >> 24) & 255)
				- ((fdf->a->color >> 24) & 255)) * fraction(fdf->a->x, fdf->b->x, x);
	}
}
```

Now, hopefully you understand our pixel formula, or at least how to find the position in a single array from a 2d coordinate. 

You may be wondering what all these & and 255s and >> signify. Which is very fair. 

These are bitwise operations that help us extract and find the correct color and gradient from our already saved color. 

It looks a bit more complicated than it actually is. That is because we are using the formula for the gradient on top of the bitwise operations `min_color + (max_color - min_color) * fraction(min, max, current)` 

What we are doing is extracting the specific color byte and adding it to the byte position in our addr array. Since our addr array is taking all BYTES and not pixels, this is what we have to do (unfortunately).

So - we therefore extract each color byte from the current position we want to draw. 

The way we extract this is through first shifting the 8 bytes we want to extract to the least significant position, then using an & 255 to get the value. 

So in the first position we don’t have to perform any shifting of the bytes, because it is already in the least significant position. However, when we move onto the next color, it will be 8 bits in front, and we want to shift it back in order to extract it. 

We do the same with the next 8 bits, and the next 8, which is why in our last color we have to shift 24 bits before extracting the color. 

The number 255 might seem a bit random, however, what it actually does it comparing the color range with the max opacity 255 to eliminate the excess values of the color.

I would highly recommend [this article](https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx), which explains it way better than I ever could. This one is also great for more in depth [color theory.](https://03-jon-perez.gitbook.io/coding-library/c/minilibx/colores)

Okay now, should we talk about the **fraction** that keeps appearing throughout the program?

This is essentially just a formula that we apply to each and every point in order to obtain the gradient color. 

```c
float   fraction(float min, float max, float current)
{
    if (min != max)
        return ((current - min) / (max - min));
    return (0);
}
```

As you obviously can tell, it takes three floats as input - the maximum coordinate value (which we set in our map function), the minimum and lastly, the current value we actually want to calculate the fraction for.
