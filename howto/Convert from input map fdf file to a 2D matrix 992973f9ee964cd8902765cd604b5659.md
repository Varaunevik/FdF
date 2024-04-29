# Convert from input map .fdf file to a 2D matrix.

Now, even the PDF states that this is not a parsing project, however, we must handle the maps somehow. 

The pdf even gives us clues this time, can you believe it?

It recommends using ft_split and get_next_line in specific, so guess what? We’ll listen, as the obedient little people we are. 

Just because I don’t want to be like 100% obedient, I have modified the split function a little (also because I had to in order to create an int 2D array, but let’s just say it is because I’m a rebel and a rule-breaker etc.)

This is our **main** map conversion function, which calls the helper functions. It works quite similarly to split, as mentioned, however, we don’t want to store chars, we want to store integers. 

Since we already know the height from our init struct function, we can use this for our malloc. 

Then we create the file descriptor by using open(). This is used as a parameter when we call the fill_map function.

```c
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
```

Our fill_map function will take use of gnl with the already found file descriptor. It iterates through the height of the map (the amount of int pointers we have allocated space for), and it stores the current line by calling the get_row function with the structure, the line we got from gnl, and the current position in the “main” array (height). 

```c
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
```

The get_row function will allocate space for the row by using the width we have from the init struct function at the very beginning. 

Then we iterate through the whitespace in the line extracted and store the value we encounter by calling the store_value function with the current position in the line, the current position in the width and the line by reference. 

Then we check whether the current integer is bigger than the assigned maximum integer, if it is, we update this value. The same is done for the min value. This will be useful later when we want to create gradients. 

```c

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
```

This is the store_value function and the final element of our parsing file. 

We start by converting the line into a “value” by using atoi on the parsed line. 

Then we iterate through the first digit and check whether we encountered a comma. If we did, it means that there is a color code present, and we need to set the flag to 1. Then we store this color in the colored_matrix (which essentially has the same measurements as the map matrix, but stores the corresponding colors instead). Then we call ft_atoi_base in order to convert this hexadecimal to decimal, making it better to extract when doing RGB operations later. 

Then we iterate through the hex and the next whitespace, effectively returning to the function above. 

```c
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

```