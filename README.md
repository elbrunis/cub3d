*This project has been created as part of the 42 curriculum by mwilline and biniesta.*

# cub3D

## Description

A 3D graphical representation of a maze from a first-person perspective using ray-casting principles. Built with C and miniLibX, this project renders walls with different textures based on their orientation (North, South, East, West) and supports floor/ceiling coloring.

## Instructions

### Compilation
```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile everything
```

### Execution
```bash
./cub3D <map.cub>
```

### Controls
- **W/A/S/D**: Move through the maze
- **Left/Right arrows**: Look around
- **ESC**: Quit the program
- **Red cross**: Close window

### Map Format (.cub)
- `0`: Empty space
- `1`: Wall
- `N/S/E/W`: Player spawn position and orientation
- Map must be surrounded by walls

## Resources

- [Ray-casting tutorial](https://lodev.org/cgtutor/raycasting.html)
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx.html)
- AI assistance was used for understanding ray-casting concepts and debugging
