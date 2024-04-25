# Step-by-step

### Overview of everything that happens in the program:

1. **Convert from input map .fdf file to a 2D matrix.** 
- The matrix will be read as a coordinate-like system where the height (z int) is stored
- So map[x][y] = 1 would tell us that point has the height 1, or, has a 3D coordinate (x, y, 1).
- For this we utilize get_next_line to read from the given file
2. **Initialize the fdf structure with important data (or null values)**
- Checking the fdf filename is correct by seeing whether it ends with the .fdf
- Then we null all the pointers and the variables we won’t use right now in fdf structure
- We initialize the width and height of the map by using the corresponding functions
- We call init map and init color map to store both the height and the potential color
- We set the isometric view to 1 as this is the standard view. 
3. **Initializing a mlx session by calling corresponding functions
-** Beginning with the mlx_init function and mlx_new window using the macro window measurements. We store the pointers in our structure (fdf).
- Then we init a new image that we want to fill, and store the pointer in the image structure
- We call find img addr function to get the address of the pixels in the image so we can modify
4. **Drawing the map
-** We want to start drawing the map by first filling the whole screen with black/grey color, storing it inside our addr array.
- Then we want to start drawing the lines between the points. We need to find the points and center them to the screen by using a specific formula. 
- We extract the z value that we stored in our 2d map matrix and store it in the z variable in the fdf struct. 
- We also extract the color we stored in our color 2d matrix
- The values extracted will be put inside our point structure
- Then we perform all needed transformations and translations. Such as zoom, rotations, isometric translations, and centering on the screen.
- After all transformations are done, it means we have the final coordinates, and we want to draw a line between the two points we found and updated. 
- We check whether slope is less than or bigger than one, and call corresponding line drawing algorithm functions. 
5. **Line Drawing Algorithm
-** The line drawing algorithm needs to know whether the slope between the two coordinates is less than or bigger than 1. The formula will be different, so we start off by calculating that.
- The algorithm used is the Bresenham’s line drawing algorithm (you can find a multitude of videos on youtube, but I personally enjoyed [this one](https://youtu.be/y_SPO_b-WXk?si=ZNtaHQjJAGqT23Ez)).
- We update and keep track of a p value that will decide whether to increase/keep the Y value (or X value, depending on the slope).
- After each calculation, we call the custom pixel drawing algorithm that will store that chosen pixel position in the addr[] array in our img structure. 
- We find the pixel needed by using the formula `pixel = y * line_len + x * 4` . Then we want to extract the color at the coordinates by using bitwise operations. We know one pixel consists of four bytes, so we iterate from 0-3 in the array (current position and the next three) in order to store the proper color value there. 
- We use the formula min_color + (max_color - min_color) * fraction. This gives us the gradient (if we have more than one color applied).
- When we have iterated from the min coordinate to the max, we go back to our “point-finding” algorithm to get the next two coordinates. 
- This continues until all lines have been drawn between the present points.
6. **Create the panel and mouse hooks for interaction
-**  We want to sort of hardcode our buttons in the panel by assigning certain places on the screen. So if the mouse clicks on this area, an action is performed. 
- We first have to design the panel, convert it to .xpm format and push it to the window 
- This panel will be present for as long as the program is running (it will switch between the two perspectives depending on which button is currently being pushed)
- We simply just make boundaries for x and y and adjust the view depending on where we clicked. 
7. **Defining hooks and actions
-** Now we are just going to define a magnitude of different buttons and keypresses so that our program can be more interactive, such as zoom, translations using the arrow keys, and rotations using our keys.
8. **Exiting the program with grace
-** This is the sort of program where a lot of things can go wrong, therefore it is important to error handle gracefully and have a multitude of error return statements so we can know exactly what it is that happened if the program crashes. 
- This can be defined in our structures and can be printed out using the perror() function with the exit(1) command. 

Okay, now that you have a step-by-step overview of the project and what needs to be done, let’s actually get to it, shall we?

[**Convert from input map .fdf file to a 2D matrix.** ](Step-by-step%20acc3f5348adf4b42996a593b389f33a1/Convert%20from%20input%20map%20fdf%20file%20to%20a%202D%20matrix%20992973f9ee964cd8902765cd604b5659.md)

[**Initialize the fdf structure with important data**](Step-by-step%20acc3f5348adf4b42996a593b389f33a1/Initialize%20the%20fdf%20structure%20with%20important%20data%2057576a5067bc4c8fa9eb1cd7054f7834.md)

[**Drawing the map**](Step-by-step%20acc3f5348adf4b42996a593b389f33a1/Drawing%20the%20map%20ee48ca12f1844e54a9d3b510877da9b1.md)

[**Line Drawing Algorithm**](Step-by-step%20acc3f5348adf4b42996a593b389f33a1/Line%20Drawing%20Algorithm%2071eea765afef4bd4806286ec78dc6ff5.md)