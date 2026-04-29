# cub3D - Raycasting 3D Maze

![42 school](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=flat-square)

## About

**cub3D** is a small 3D rendering project built with MiniLibX. It recreates a first-person maze experience using classic raycasting: the player moves inside a 2D map while the engine projects textured walls into a 3D view.

The project focuses on parsing a configuration file, validating the map, loading textures, handling keyboard input, drawing the scene frame by frame, and managing memory correctly.

## Project Goals

- Build a functional first-person 3D renderer using MiniLibX
- Parse and validate a `.cub` configuration file
- Load four wall textures and ceiling/floor colors
- Implement raycasting for wall projection
- Support player movement and rotation with collision handling
- Provide a minimap build target for easier navigation
- Keep memory management clean and leak-free

## Game Concept

### Gameplay

You wake up inside a maze-like map and explore it in first person. The world is represented by a 2D grid, but the renderer turns that grid into a 3D view by casting rays from the player position toward the walls.

### Objective

- Move through the map without walking through walls
- Use the textures and colors defined in the `.cub` file
- Navigate the environment from a first-person perspective

### Controls

- **W** or **↑** - Move forward
- **S** or **↓** - Move backward
- **A** - Strafe left
- **D** - Strafe right
- **←** - Rotate left
- **→** - Rotate right
- **ESC** - Exit the game

## Map Format

The project uses a `.cub` file that contains both rendering configuration and the map layout.

### Configuration Elements

- `NO` - Path to the north wall texture
- `SO` - Path to the south wall texture
- `WE` - Path to the west wall texture
- `EA` - Path to the east wall texture
- `F` - Floor color in RGB format
- `C` - Ceiling color in RGB format

### Map Components

- `1` - Wall
- `0` - Empty space
- `N` - Player start facing north
- `S` - Player start facing south
- `E` - Player start facing east
- `W` - Player start facing west

### Map Rules

1. The file must have a `.cub` extension
2. All required texture paths and colors must be present
3. The map must contain exactly one player spawn position
4. The map must be enclosed by walls
5. Only valid map characters are allowed
6. Empty lines and spacing are handled by the parser, but the final map must still be valid

### Example Configuration

```text
NO textures/north_wall.xpm
SO textures/south_wall.xpm
WE textures/west_wall.xpm
EA textures/east_wall.xpm

F 220,100,0
C 225,30,0

111111
1000N1
101111
100001
111111
```

This example contains:

- Four wall textures
- Floor and ceiling colors
- A closed map
- One player spawn facing north

## Graphics

The renderer uses MiniLibX and a fixed-size window.

- **Window size**: 1920x1080
- **Texture mapping**: one texture per wall face
- **Projection**: raycasting with per-column wall rendering
- **Floor and ceiling**: solid colors drawn after the wall pass
- **Minimap**: available through the `bonus` build target

## Compilation

### Requirements

- **MiniLibX** - Included in `inc/mlx/`
- **X11 libraries** - Required by MiniLibX on Linux
- **gcc** - C compiler
- **make** - Build tool

### Build Commands

```bash
make
```

This builds the `cub3D` executable.

```bash
make bonus
```

This builds the project with the minimap enabled.

### Available Commands

- `make` - Build the project
- `make clean` - Remove object files
- `make fclean` - Remove object files and the executable
- `make re` - Rebuild everything from scratch
- `make bonus` - Build with the minimap flag

## Usage

### Basic Usage

```bash
./cub3D [map_file.cub]
```

### Examples

```bash
./cub3D maps/test.cub
./cub3D maps/test2.cub
```

### Runtime Behavior

- The program opens a graphical window and renders the maze in first person
- Movement is updated continuously while keys are held down
- The ESC key closes the window and frees resources
- When built with `make bonus`, the minimap can be displayed

## Error Handling

The program reports descriptive errors for common failure cases:

- Invalid argument count
- Wrong file extension
- Missing `.cub` file
- Missing texture paths
- Missing floor or ceiling colors
- Invalid RGB values
- Invalid map characters
- Missing or duplicate player spawn positions
- Unclosed map geometry

## Implementation Structure

The project is split into focused modules:

### Core Files

- **main.c** - Program entry point, initialization, and game loop setup
- **cub3d.h** - Main header with constants, structures, and function prototypes

### Input Parsing

- **input_reader.c** - Reads the `.cub` configuration and extracts textures/colors
- **input_checker.c** - Validates configuration input
- **input_utils.c** - Helpers for line parsing and string checks

### Map Handling

- **map_reader.c** - Loads the map from the file
- **map_reader_utils.c** - Helpers for map allocation and reading
- **map_checker.c** - Validates map characters and closed geometry
- **map_utils.c** - Utility functions for line counting, flood fill, and spawn detection

### Rendering and Movement

- **raycaster.c** - Raycasting and wall projection
- **draw.c** - Drawing utilities and ceiling/floor rendering
- **player.c** - Player movement, rotation, and collision handling
- **init_player.c** - Player spawn initialization and key state setup
- **minimap.c** - Minimap rendering for the bonus build

### Utility Files

- **utils.c** - General helpers
- **utils_for_utils.c** - Additional helper functions

## Technical Details

- **Language**: C
- **Compiler**: gcc
- **Flags**: `-Wall -Wextra -Werror`
- **Graphics Library**: MiniLibX
- **Window Size**: 1920x1080
- **Tile Size**: 48 pixels
- **Raycasting Method**: DDA-style wall traversal
- **Player Movement**: forward/backward movement, strafing, and rotation
- **Collision System**: wall collision enabled by default

## Rendering Features

### Raycasting

The renderer casts one ray per screen column. Each ray finds the nearest wall hit, computes the projected wall height, and draws the matching texture slice on screen.

### Texture Selection

Wall faces are mapped to the correct texture according to the direction of impact:

- North wall texture
- South wall texture
- East wall texture
- West wall texture

### Floor and Ceiling

After the wall pass, the remaining background pixels are filled using the floor and ceiling RGB colors from the configuration file.

### Minimap

When compiled with `make bonus`, the project can also render a minimap that shows the local map area and the player position.

## Testing

### Sample Maps

The repository includes test maps in the `maps/` directory:

```bash
./cub3D maps/test.cub
./cub3D maps/test2.cub
```

### Creating Custom Maps

Create a `.cub` file with the required texture paths, floor and ceiling colors, and a valid enclosed map.

Checklist:

1. Provide all four wall textures
2. Define both RGB colors
3. Use one of `N`, `S`, `E`, or `W` for the spawn point
4. Keep the map fully surrounded by walls
5. Avoid invalid characters

## Notes

- The project uses a fixed window size rather than dynamic scaling
- Textures are loaded from the paths defined in the map file
- The player starts facing the direction encoded in the spawn tile
- Collision is enabled by default to prevent walking through walls
- The minimap is optional and controlled by the build flag

## Known Limitations

- No advanced lighting or shading effects
- No enemy or interaction system
- No animation system for movement
- No dynamic resolution scaling

## Author

**opopov**
