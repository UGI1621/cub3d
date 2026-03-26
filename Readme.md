*This project has been created as part of the 42 curriculum by saan, hwiskim.*

# Description

This project implements a 3D rendering system based on information from a 2D plane.
It uses the MiniLibX library to validate the input file and renders a 3D view using the data defined inside a `.cub` file.

## 1. Project Goal

Understand and implement raycasting, the rendering algorithm used in the early Wolfenstein games.

## 2. Process

When the program is executed, it takes a `.cub` file as an argument.
It validates the elements defined in the file.

After that, it initializes the actual data that will be used and renders the scene using distances calculated by raycasting.

During rendering, delta time is used to compensate movement speed according to processing speed and to keep the frame rate stable.

## 3. Notes

The program will not run unless the texture files match the predefined size specified in the header file.

If the prepared texture files are modified, the program may fail to run.

This project currently has no simulation end condition or clear condition.
To exit the program, press the ESC key or click the 'x' button in the top-right corner of the window.

# Instructions

Download `minilibx-linux.tgz` from the project page on intra.
Then, extract it in the root folder of this project and rename the extracted folder to `mlx`.

Open a terminal in the root folder of the project.

```bash
make
```
Use the command above to compile the program.

```bash
./cub3D {path_of_.cub_file}
```
Use the command above to run the program.

Keymap
---

W : Move forward<br>
A : Move left<br>
S : Move backward<br>
D : Move right<br>

Left Arrow : Rotate left<br>
Right Arrow : Rotate right<br>

ESC : Exit<br>

```bash
make clean
```
This command removes the object files.

```bash
make fclean
```
This command removes both the object files and the program executable.

# Resource

[Raycasting tutorial in Korean]<https://github.com/365kim/raycasting_tutorial/tree/master><br>
[Raycasting tutorial]https://www.youtube.com/watch?v=g8p7nAbDz6Y<br>
[Understanding raycasting]https://sikpang.tistory.com/32<br>
[Rotation Matrix]https://xoft.tistory.com/109<br>
[Delta time]https://blog.naver.com/since_1992_/221412390449<br>
<br><br>

# AI Usage

AI was used for:

Calculating the proportional values for texture positions drawn on screen in
```C
static void draw_wall_column(t_game *g, int x, int top, int bot)
```

Ideas for fixed-point shift operations for optimization<br>
<br>
Optimization ideas for
```C
void put_pixel(t_game *g, int x, int y, int color)
```
<br>

__Understanding vector operations and representation__<br>

__Analyzing memory leaks and errors detected by Valgrind, including static leaks in get_next_line and invalid reads__<br>

__Translating this README__<br>

__General mental support__<br>
