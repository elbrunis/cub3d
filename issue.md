# cub3D Issues List

## CRITICAL (Will receive 0)

| # | Issue | Location |
|---|-------|----------|
| 1 | **Missing `bonus` rule in Makefile** | `Makefile` - Subject requires `all, clean, fclean, re, bonus` |
| 2 | **Missing `-Wall` flag in Makefile** | `Makefile:8` - Subject requires `-Wall -Wextra -Werror` |
| 3 | **ESC key not handled** | `src/hooks/key_hooks.c` - Subject requires ESC to close window cleanly |
| 4 | **Left/Right arrow keys not handled** | `src/hooks/key_hooks.c` - Subject requires arrow keys to look left/right |
| 5 | **Textures not applied in raycaster** | `src/raycasting/raycaster.c:3-33` - Uses single color `0xFFFFFF` instead of textures |
| 6 | **Floor/ceiling colors not used** | `src/raycasting/raycaster.c:23-32` - Uses hardcoded `0x333333`/`0x555555` instead of parsed colors |
| 7 | **Program name wrong** | `Makefile:1` - Is `cube3d`, should be `cub3D` |
| 8 | **README.md completely wrong** | `README.md` - Written in Spanish, missing required sections (Description, Instructions, Resources) |

## HIGH (Functional issues)

| # | Issue | Location |
|---|-------|----------|
| 9 | **No collision detection** | `src/hooks/move.c` - Player can walk through walls |
| 10 | **Memory leak: map not freed properly** | `src/utils/free_game.c:35` - Uses `free(game->map)` instead of `free_map(game->map)` |
| 11 | **Memory leak: texture paths not freed** | `src/utils/free_game.c` - `no_path`, `so_path`, `we_path`, `ea_path` never freed |
| 12 | **libft not in separate folder** | Subject requires libft sources + Makefile in `libft/` folder |
| 13 | **Map validation: map not required to be last** | `src/parsing/parsing.c` - Subject says "map content always has to be the last" but not enforced |
| 14 | **XPM texture validation too strict** | `src/parsing/textures.c:48-54` - Only checks `.xpm` extension, should allow any texture path |

## MEDIUM (Norm/Code quality)

| # | Issue | Location |
|---|-------|----------|
| 15 | **Comments using `//`** | Multiple files - 42 Norm requires `/* */` only |
| 16 | **Commented-out files should be removed** | `src/raycasting/raycaster_sucio.c`, `src/render/map2d.c` |
| 17 | **Variable declaration not at top** | `src/main.c:34` - `const char *error` declared mid-function |
| 18 | **Potential buffer overflow in DDA** | `src/raycasting/raycaster.c:97` - No bounds checking for `map[r->mapY][r->mapX]` |
| 19 | **`fill_array_and_free` memory issue** | `src/parsing/reed_map.c:65-80` - Frees list nodes but loses pointer to `line` content |

## LOW (Minor issues)

| # | Issue | Location |
|---|-------|----------|
| 20 | **Unused defines** | `includes/cube3d.h` - `WIDTH`, `HEIGHT`, `PLAYER_LEN`, `SQUARE_LEN`, `GRAY`, `WHITE`, `ORANGE` |
| 21 | **Inconsistent naming** | `src/parsing/reed_map.c` - "reed" should be "read" |
| 22 | **Missing newline at end of Makefile** | `Makefile:30` |
