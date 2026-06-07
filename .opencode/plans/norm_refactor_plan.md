# Norm Refactoring Plan — 42 School Compliance

## Objective
Refactor all files violating the 42 Norm (NORM-001: max 5 functions per file, NORM-002: max 25 lines per function body) while preserving 100% of the original logic, variable states, and memory management.

---

## NORM-001: Function Count Per File (Max 5)

### File: `src/libft.c` — 15 functions → Split into 4 files

| New File | Functions | Count |
|----------|-----------|-------|
| `src/libft/ft_string.c` | `ft_strlen`, `ft_strchr`, `ft_strjoin`, `ft_strdup`, `ft_strncmp` | 5 |
| `src/libft/ft_memory.c` | `ft_bzero`, `ft_memset`, `ft_calloc` | 3 |
| `src/libft/ft_split.c` | `is_space` (static), `word_count` (static), `get_word` (static), `frees_split` (static), `ft_split` | 5 |
| `src/libft/ft_convert.c` | `ft_isdigit`, `ft_atoi` | 2 |

**Note**: `ft_split.c` has exactly 5 functions (4 static helpers + 1 public). All other files are ≤5.

### File: `src/raycasting/raycaster.c` — 9 functions → Split into 2 files

| New File | Functions | Count |
|----------|-----------|-------|
| `src/raycasting/raycaster.c` | `init_raycasting` (static), `calculate_step` (static), `perform_dda` (static), `select_texture` (static), `raycasting` | 5 |
| `src/raycasting/raycaster_draw.c` | `get_tex_color` (static), `draw_textured_line` (static), `draw_floor_ceiling` (static), `calc_tex_x` (static) | 4 |

**Issue**: `raycasting()` calls `draw_textured_line` and `draw_floor_ceiling` which will be in `raycaster_draw.c`. These must become non-static.

**Prototypes added to `cube3d.h`**:
```c
void	calc_wall_bounds(t_ray *r);
void	draw_textured_line(t_cube3d *game, int x, t_ray *r);
void	draw_floor_ceiling(t_cube3d *game, int x, t_ray *r);
void	calc_tex_x(t_cube3d *game, t_ray *r);
void	select_texture(t_cube3d *game, t_ray *r);
```

Actually — `raycasting()` also calls `init_raycasting`, `calculate_step`, `perform_dda`, `select_texture`. If these stay static in `raycaster.c`, that's fine since `raycasting()` is also in `raycaster.c`.

But `raycasting()` calls `draw_textured_line`, `draw_floor_ceiling`, `calc_tex_x`, and `select_texture`. Wait — `select_texture` is in `raycaster.c` (core). It's called by `raycasting()` which is also in core. That's fine.

So only the draw functions need to be non-static. But `select_texture` is called from `raycasting()` — if we keep it static in `raycaster.c`, that's fine.

**Final split**:

| New File | Functions | Static? |
|----------|-----------|---------|
| `src/raycasting/raycaster.c` | `init_raycasting`, `calculate_step`, `perform_dda`, `select_texture`, `raycasting` | All static except `raycasting` |
| `src/raycasting/raycaster_draw.c` | `get_tex_color`, `calc_wall_bounds` (NEW), `draw_textured_line`, `draw_floor_ceiling`, `calc_tex_x` | All static except draw functions |

Wait — `raycaster.c` already has 5 functions. If `perform_dda` gets an extracted helper `is_out_of_bounds`, that makes 6. Need to reconsider.

With the NORM-002 fix for `perform_dda` (extracting `is_out_of_bounds`), `raycaster.c` would have:
1. `is_out_of_bounds` (static)
2. `init_raycasting` (static)
3. `calculate_step` (static)
4. `perform_dda` (static)
5. `select_texture` (static)
6. `raycasting` (public)

That's 6 — still over the limit. Solution: move `is_out_of_bounds` into `perform_dda` inline (sacrifice the 25-line limit approach, or restructure).

**Better approach**: Keep `is_out_of_bounds` as a separate static helper but put it in `raycaster_draw.c` since it's only called by `perform_dda`... no, it's called from `raycaster.c`.

**Simplest solution**: Don't extract `is_out_of_bounds`. Instead, reduce `perform_dda` by other means (simpler loop construct, combining conditions).

Actually, let me re-count `perform_dda` lines precisely:

```c
static void	perform_dda(t_cube3d *game, t_ray *r)
{
	int	map_height;       // 1
	int	row_len;           // 2

	map_height = 0;        // 3
	while (game->map[map_height]) // 4
		map_height++;       // 5
	while (r->hit == 0)    // 6
	{                       // 7
		if (r->side_dist_x < r->side_dist_y) // 8
		{                   // 9
			r->side_dist_x += r->delta_dist_x; // 10
			r->map_x += r->step_x;             // 11
			r->side = 0;                        // 12
		}                   // 13
		else                // 14
		{                   // 15
			r->side_dist_y += r->delta_dist_y; // 16
			r->map_y += r->step_y;             // 17
			r->side = 1;                        // 18
		}                   // 19
		if (r->map_y < 0 || r->map_y >= map_height) // 20
			break ;          // 21
		row_len = (int)ft_strlen(game->map[r->map_y]); // 22
		if (r->map_x < 0 || r->map_x >= row_len)       // 23
			break ;          // 24
		if (game->map[r->map_y][r->map_x] == '1')       // 25
			r->hit = 1;      // 26
	}                       // 27
	if (r->side == 0)       // 28
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x; // 29
	else                    // 30
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y; // 31
}                           // 32
```

That's 30 lines inside the body, which is over 25. The extraction approach works if we accept the file count going up.

**For `raycaster.c` with 6 functions**: We can move `select_texture` to `raycaster_draw.c` (it's a small 8-line function, and it references `game` and `r` like the draw functions).

| New File | Functions | Count |
|----------|-----------|-------|
| `src/raycasting/raycaster.c` | `is_out_of_bounds` (static), `init_raycasting` (static), `calculate_step` (static), `perform_dda` (static), `raycasting` | 5 |
| `src/raycasting/raycaster_draw.c` | `get_tex_color` (static), `calc_wall_bounds` (static), `draw_textured_line`, `draw_floor_ceiling`, `calc_tex_x` | 5 |

Wait, `select_texture` needs to go somewhere. It's small (8 lines). Let me add it to `raycaster_draw.c`:

| New File | Functions | Count |
|----------|-----------|-------|
| `src/raycasting/raycaster.c` | `is_out_of_bounds` (static), `init_raycasting` (static), `calculate_step` (static), `perform_dda` (static), `raycasting` | 5 |
| `src/raycasting/raycaster_draw.c` | `get_tex_color` (static), `calc_wall_bounds` (static), `select_texture`, `draw_textured_line`, `draw_floor_ceiling`, `calc_tex_x` | 6 |

6 functions — still over. Need to combine or rethink.

**Better rethink**: `select_texture` can be inlined into `raycasting()` since it's just a few if/else branches. That eliminates one function.

Or: Move `select_texture` back to `raycaster.c` (it was there originally) and accept 6 functions... no, max is 5.

**Final solution for raycaster**: Keep `select_texture` as static in `raycaster_draw.c` and accept that `raycaster_draw.c` has 6 functions. OR, make `select_texture` part of `calc_tex_x` since it's always called right before it.

**Best solution**: Merge `select_texture` into `calc_tex_x`. They're always called sequentially (`select_texture` then `calc_tex_x` in `raycasting()`). The combined function would be `calc_tex_x` that also sets `tex_num`.

New function (merged):
```c
static void	calc_tex_x(t_cube3d *game, t_ray *r)
{
	double	wall_x;

	/* select texture */
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			r->tex_num = 2;
		else
			r->tex_num = 3;
	}
	else
	{
		if (r->ray_dir_y > 0)
			r->tex_num = 1;
		else
			r->tex_num = 0;
	}
	/* calculate texture x coordinate */
	if (r->side == 0)
		wall_x = game->player->y_pos + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = game->player->x_pos + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	r->tex_x = (int)(wall_x * TEX_WIDTH);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
}
```

That's ~20 lines — within the 25-line limit. And now:

| New File | Functions | Count |
|----------|-----------|-------|
| `src/raycasting/raycaster.c` | `is_out_of_bounds` (static), `init_raycasting` (static), `calculate_step` (static), `perform_dda` (static), `raycasting` | 5 |
| `src/raycasting/raycaster_draw.c` | `get_tex_color` (static), `calc_wall_bounds` (static), `draw_textured_line`, `draw_floor_ceiling`, `calc_tex_x` | 5 |

Perfect — both at exactly 5.

### File: `src/hooks/move.c` — 9 functions → Split into 3 files

| New File | Functions | Count |
|----------|-----------|-------|
| `src/hooks/collision.c` | `is_wall` (static), `is_blocked` | 2 |
| `src/hooks/move_walk.c` | `move_front` (static), `move_back` (static), `strafe_left` (static), `strafe_right` (static) | 4 |
| `src/hooks/move.c` | `rotate_left` (static), `rotate_right` (static), `move` | 3 |

**Cross-file call analysis**:
- `move()` calls `move_front`, `move_back`, `strafe_left`, `strafe_right` (in `move_walk.c`)
- `move_front` etc. call `is_blocked()` (in `collision.c`)

**Required prototypes in `cube3d.h`**:
```c
int		is_blocked(t_cube3d *game, double x, double y);
void	move_front(t_cube3d *game);
void	move_back(t_cube3d *game);
void	strafe_left(t_cube3d *game);
void	strafe_right(t_cube3d *game);
```

**Note**: The 4 walk functions cannot stay static if they're in a different file from `move()`. They become non-static but are internal helpers. This is acceptable under the 42 Norm.

### File: `src/utils/init_game.c` — 6 functions → Split into 2 files

| New File | Functions | Count |
|----------|-----------|-------|
| `src/utils/init_game.c` | `allocate_game_components` (static), `init_parser`, `init_game` | 3 |
| `src/utils/load_game.c` | `load_texture` (static), `load_all_textures`, `init_player_values` | 3 |

**Cross-file calls**:
- `init_game()` calls `load_all_textures()` and `init_player_values()` (in `load_game.c`)

**Required prototypes in `cube3d.h`**:
```c
int		load_all_textures(t_cube3d *game, t_parse *parse);
void	init_player_values(t_cube3d *game, t_parse *parse);
```

Wait — with NORM-002 fix, `init_game()` body will be shorter. But `allocate_game_components` is still called only by `init_game()`, so it can stay static in the same file.

### File: `src/parsing/read_map.c` — 7 functions → Split into 2 files

| New File | Functions | Count |
|----------|-----------|-------|
| `src/parsing/read_map_list.c` | `free_map_list` (static), `clean_line` (static), `ft_lstnew_map`, `ft_lstadd_back_map`, `fill_array_and_free` | 5 |
| `src/parsing/read_map.c` | `read_map` | 1 |

**Cross-file calls**:
- `read_map()` calls `ft_lstnew_map`, `ft_lstadd_back_map`, `fill_array_and_free` (in `read_map_list.c`)

**Approach**: Use forward declarations at the top of `read_map.c` (42-idiomatic approach for internal helpers):

```c
#include "../includes/cube3d.h"

t_list_map	*ft_lstnew_map(char *line);
void		ft_lstadd_back_map(t_list_map **lst, t_list_map *new);
char		**fill_array_and_free(t_list_map *lst, int size);

char	**read_map(t_parse *parse) { ... }
```

No changes needed in `cube3d.h` for these — they're internal to the parsing module.

### File: `src/utils/free_game.c` — 4 functions (OK)

`free_game.c` currently has 4 functions: `free_map`, `free_parse`, `free_textures` (static), `free_game`. This is within the 5-function limit. No split needed.

With NORM-002 fix (extracting `free_game_resources`), it becomes 5 functions — exactly at the limit.

### File: `src/parsing/parse_map.c` — 5 functions (OK)

`parse_map.c` currently has 5 functions: `handle_player`, `check_cell`, `check_line`, `check_empty_end`, `parse_map`. This is at the 5-function limit. No split needed.

With NORM-002 fix, if we extract helpers from `parse_map()`, the count might go up. But the extracted helpers can be static, so they replace existing logic within `parse_map()` rather than adding new functions.

Actually wait — extracting `skip_empty` and `validate_lines` would add 2 static functions, bringing the total to 7. Need to reconsider.

**Solution**: Don't extract separate helper functions for `parse_map()`. Instead, reduce line count by:
1. Combining the allocated-return pattern into shorter forms
2. Using ternary expressions where appropriate
3. Or: move `check_empty_end` and `handle_player` to a separate utility file

**Better solution**: Move `handle_player` to `read_map_list.c` (since it's player-related initialization) and `check_empty_end` to the same file. Then `parse_map.c` has only `check_cell` (static), `check_line` (static), `parse_map` — and the 2 extracted helpers total 5.

| New File | Functions | Count |
|----------|-----------|-------|
| `src/parsing/parse_map.c` | `check_cell` (static), `check_line` (static), `skip_empty_lines` (static), `validate_map_body` (static), `parse_map` | 5 |
| `src/parsing/parse_map_player.c` | `handle_player`, `check_empty_end` | 2 |

Wait — `check_line` calls `check_cell` and `handle_player`. If `handle_player` moves to a different file, `check_line` can't call it if it's static. Make `handle_player` non-static with a prototype.

**Also**: `parse_map` calls `check_empty_end`. Need prototype for that too.

**Prototypes needed in `cube3d.h` or forward declarations**:
```c
char	*handle_player(t_parse *parse, char c, int y, int x);
char	*check_empty_end(char **map, int y);
```

---

## NORM-002: Function Body Line Count Reductions (Max 25)

### `main()` — 29 lines → Target ≤25

**Extract**:
```c
static void	print_error(const char *msg)
{
	if (errno != 0)
		printf("Error\n%s: %s\n", msg, strerror(errno));
	else
		printf("Error\n%s\n", msg);
}
```

**After extraction, `main()` body** (~23 lines):
```c
if (argc != 2)
	return (printf("Error\nmissing arguments\n"));
parse = init_parser();
if (!parse)
	return (1);
error = parser(parse, argv[1]);
if (error)
{
	print_error(error);
	free_parse(parse);
	return (1);
}
game = init_game(parse);
if (!game)
	return (1);
mlx_hook(game->win, 2, 1L << 0, press_key, (void *)game);
mlx_hook(game->win, 3, 1L << 1, release_key, (void *)game);
mlx_hook(game->win, 17, 0, x_pres, (void *)game);
mlx_loop_hook(game->mlx, game_loop, (void *)game);
mlx_loop(game->mlx);
free_game(game);
return (0);
```

**Result**: `main()` = ~23 body lines, `print_error()` = ~5 body lines. Both under 25.

### `ft_split()` — ~31 lines → Target ≤25

**Extract the word-filling loop**:
```c
static int	split_fill(const char *s, char **res)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		start = i;
		while (s[i] && !is_space(s[i]))
			i++;
		if (i > start)
		{
			res[j] = get_word(s, start, i);
			if (!res[j])
				return (frees_split(res, j - 1), -1);
			j++;
		}
	}
	res[j] = NULL;
	return (0);
}
```

**After extraction, `ft_split()` body** (~10 lines):
```c
char	**res;

if (!s)
	return (NULL);
res = malloc(sizeof(char *) * (word_count(s) + 1));
if (!res)
	return (NULL);
if (split_fill(s, res) == -1)
	return (NULL);
return (res);
```

**Result**: `ft_split()` = ~10 body lines, `split_fill()` = ~18 body lines. Both under 25.

### `parse_map()` — ~34 lines → Target ≤25

**Extract**:
```c
static int	skip_empty_lines(char **map)
{
	int	y;

	y = 0;
	while (map[y] && map[y][0] == '\0')
		y++;
	return (y);
}
```

**After extraction, `parse_map()` body** (~21 lines):
```c
char	**map;
char	*err;
int		y;

map = read_map(parse);
if (!map || !map[0])
	return ("Empty map");
y = skip_empty_lines(map);
while (map[y] && map[y][0] != '\0')
{
	err = check_line(parse, map, y);
	if (err)
	{
		free_map(map);
		return (err);
	}
	y++;
}
err = check_empty_end(map, y);
if (err)
{
	free_map(map);
	return (err);
}
if (!parse->player_set)
{
	free_map(map);
	return ("Missing player");
}
parse->map = map;
return (NULL);
```

Wait, that's still 24 lines. And with the function needing to move `handle_player` and `check_empty_end` out, the file count works.

**Result**: `parse_map()` = ~24 body lines. Under 25.

### `draw_textured_line()` — ~31 lines → Target ≤25

**Extract**:
```c
static void	calc_wall_bounds(t_ray *r)
{
	if (r->perp_wall_dist < 0.0001)
		r->perp_wall_dist = 0.0001;
	r->line_height = (int)(SCREEN_HEIGHT / r->perp_wall_dist);
	r->draw_start = (SCREEN_HEIGHT / 2) - (r->line_height / 2);
	r->draw_end = (SCREEN_HEIGHT / 2) + (r->line_height / 2);
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
}
```

**After extraction, `draw_textured_line()` body** (~19 lines):
```c
int		y;
double	step;
double	tex_pos;
int		tex_y;
int		color;

calc_wall_bounds(r);
step = (double)TEX_HEIGHT / r->line_height;
tex_pos = (r->draw_start - SCREEN_HEIGHT / 2 + r->line_height / 2) * step;
y = r->draw_start;
while (y <= r->draw_end)
{
	tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
	tex_pos += step;
	color = get_tex_color(&game->tex[r->tex_num], r->tex_x, tex_y);
	if (r->side == 1)
		color = (color >> 1) & 8355711;
	my_mlx_pixel_put(game, x, y, color);
	y++;
}
```

**Result**: `draw_textured_line()` = ~19 body lines. Under 25.

### `perform_dda()` — ~34 lines → Target ≤25

**Extract**:
```c
static int	is_out_of_bounds(t_cube3d *game, t_ray *r, int map_height)
{
	int	row_len;

	if (r->map_y < 0 || r->map_y >= map_height)
		return (1);
	row_len = (int)ft_strlen(game->map[r->map_y]);
	if (r->map_x < 0 || r->map_x >= row_len)
		return (1);
	return (0);
}
```

**After extraction, `perform_dda()` body** (~20 lines):
```c
int	map_height;

map_height = 0;
while (game->map[map_height])
	map_height++;
while (r->hit == 0)
{
	if (r->side_dist_x < r->side_dist_y)
	{
		r->side_dist_x += r->delta_dist_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_dist_y += r->delta_dist_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
	if (is_out_of_bounds(game, r, map_height))
		break ;
	if (game->map[r->map_y][r->map_x] == '1')
		r->hit = 1;
}
if (r->side == 0)
	r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
else
	r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
```

**Result**: `perform_dda()` = ~20 body lines. Under 25.

### `init_game()` — ~32 lines → Target ≤25

**Extract**:
```c
static int	setup_resources(t_cube3d *game, t_parse *parse)
{
	char	*error;

	error = init_mlx_components(game);
	if (error)
	{
		printf("Error\n%s\n", error);
		return (0);
	}
	if (!load_all_textures(game, parse))
	{
		printf("Error\nFailed to load textures\n");
		return (0);
	}
	return (1);
}
```

**After extraction, `init_game()` body** (~14 lines):
```c
t_cube3d	*game;

game = (t_cube3d *)malloc(sizeof(t_cube3d));
if (!game)
	return (NULL);
ft_memset(game, 0, sizeof(t_cube3d));
if (!allocate_game_components(game))
{
	free(game);
	return (NULL);
}
game->parse = parse;
if (!setup_resources(game, parse))
{
	free_game(game);
	return (NULL);
}
init_player_values(game, parse);
game->close_game = false;
game->map = parse->map;
return (game);
```

**Result**: `init_game()` = ~14 body lines. Under 25.

### `free_game()` — ~31 lines → Target ≤25

**Extract**:
```c
static void	free_game_resources(t_cube3d *game)
{
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
		free_textures(game);
	if (game->frame)
	{
		if (game->frame->img && game->mlx)
			mlx_destroy_image(game->mlx, game->frame->img);
		free(game->frame);
		game->frame = NULL;
	}
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
```

**After extraction, `free_game()` body** (~8 lines):
```c
if (!game)
	return (false);
free_game_resources(game);
free_parse(game->parse);
free(game);
return (true);
```

**Result**: `free_game()` = ~8 body lines, `free_game_resources()` = ~20 body lines. Both under 25.

**File count for `free_game.c` after**: 5 functions (`free_map`, `free_parse`, `free_textures` (static), `free_game_resources` (static), `free_game`). Exactly at the limit.

---

## Complete New Files List

| File | Functions (count) | New? |
|------|--------------------|------|
| `src/libft/ft_string.c` | `ft_strlen`, `ft_strchr`, `ft_strjoin`, `ft_strdup`, `ft_strncmp` (5) | YES |
| `src/libft/ft_memory.c` | `ft_bzero`, `ft_memset`, `ft_calloc` (3) | YES |
| `src/libft/ft_split.c` | `is_space` (s), `word_count` (s), `get_word` (s), `frees_split` (s), `ft_split` (5) | YES |
| `src/libft/ft_convert.c` | `ft_isdigit`, `ft_atoi` (2) | YES |
| `src/raycasting/raycaster_draw.c` | `get_tex_color` (s), `calc_wall_bounds` (s), `draw_textured_line`, `draw_floor_ceiling`, `calc_tex_x` (5) | YES |
| `src/hooks/collision.c` | `is_wall` (s), `is_blocked` (2) | YES |
| `src/hooks/move_walk.c` | `move_front` (s), `move_back` (s), `strafe_left` (s), `strafe_right` (4) | YES |
| `src/utils/load_game.c` | `load_texture` (s), `load_all_textures`, `init_player_values` (3) | YES |
| `src/parsing/read_map_list.c` | `free_map_list` (s), `clean_line` (s), `ft_lstnew_map`, `ft_lstadd_back_map`, `fill_array_and_free` (5) | YES |
| `src/parsing/parse_map_player.c` | `handle_player`, `check_empty_end` (2) | YES |

### Files to Delete
| File | Reason |
|------|--------|
| `src/libft.c` | Replaced by 4 files in `src/libft/` |

### Files to Modify (existing)
| File | Change |
|------|--------|
| `src/raycasting/raycaster.c` | Remove draw functions; add `is_out_of_bounds` (static); add forward decls for draw functions |
| `src/hooks/move.c` | Remove `is_wall`/`is_blocked`/walk functions; keep `rotate_left`/`rotate_right`/`move`; add fwd decls for walk functions |
| `src/utils/init_game.c` | Remove `load_texture`/`load_all_textures`/`init_player_values`; add `setup_resources` (static); add fwd decls |
| `src/utils/free_game.c` | Add `free_game_resources` (static) |
| `src/parsing/read_map.c` | Remove list helper functions; add forward declarations |
| `src/parsing/parse_map.c` | Remove `handle_player`/`check_empty_end`; add `skip_empty_lines` (static); add fwd decls |
| `src/main.c` | Add `print_error` (static) |
| `includes/cube3d.h` | Add new prototypes (see below) |

---

## Header Changes: `includes/cube3d.h`

### Prototypes to ADD:

```c
/* RAYCASTING - draw */
void	draw_textured_line(t_cube3d *game, int x, t_ray *r);
void	draw_floor_ceiling(t_cube3d *game, int x, t_ray *r);
void	calc_tex_x(t_cube3d *game, t_ray *r);

/* HOOKS - collision */
int		is_blocked(t_cube3d *game, double x, double y);

/* HOOKS - move_walk */
void	move_front(t_cube3d *game);
void	move_back(t_cube3d *game);
void	strafe_left(t_cube3d *game);
void	strafe_right(t_cube3d *game);

/* UTILS - load_game */
int		load_all_textures(t_cube3d *game, t_parse *parse);
void	init_player_values(t_cube3d *game, t_parse *parse);

/* PARSING - parse_map_player */
char	*handle_player(t_parse *parse, char c, int y, int x);
char	*check_empty_end(char **map, int y);
```

### Prototypes to KEEP (unchanged):
All existing prototypes remain.

### Forward Declarations (in .c files, NOT in cube3d.h):

**`src/parsing/read_map.c`** (top of file):
```c
t_list_map	*ft_lstnew_map(char *line);
void		ft_lstadd_back_map(t_list_map **lst, t_list_map *new);
char		**fill_array_and_free(t_list_map *lst, int size);
```

**`src/raycasting/raycaster.c`** (top of file):
```c
void	draw_textured_line(t_cube3d *game, int x, t_ray *r);
void	draw_floor_ceiling(t_cube3d *game, int x, t_ray *r);
void	calc_tex_x(t_cube3d *game, t_ray *r);
```

---

## Makefile Impact

Current wildcard: `$(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)`

This automatically picks up:
- `src/libft/*.c` ✓
- `src/raycasting/*.c` ✓
- `src/hooks/*.c` ✓
- `src/utils/*.c` ✓
- `src/parsing/*.c` ✓

**Required action**: Delete `src/libft.c` after creating `src/libft/` directory. The wildcard will pick up the new files automatically.

**No Makefile changes needed** except the deletion.

---

## Execution Order

1. Create directory `src/libft/`
2. Create `src/libft/ft_string.c`, `ft_memory.c`, `ft_split.c`, `ft_convert.c`
3. Create `src/raycasting/raycaster_draw.c`
4. Create `src/hooks/collision.c`, `src/hooks/move_walk.c`
5. Create `src/utils/load_game.c`
6. Create `src/parsing/read_map_list.c`, `src/parsing/parse_map_player.c`
7. Modify `src/raycasting/raycaster.c` (remove draw funcs, add `is_out_of_bounds`, add fwd decls)
8. Modify `src/hooks/move.c` (reduce to rotate + move, add fwd decls)
9. Modify `src/utils/init_game.c` (remove load funcs, add `setup_resources`)
10. Modify `src/utils/free_game.c` (add `free_game_resources`)
11. Modify `src/parsing/read_map.c` (remove list funcs, add fwd decls)
12. Modify `src/parsing/parse_map.c` (remove handle_player/check_empty_end, add skip_empty_lines, add fwd decls)
13. Modify `src/main.c` (add `print_error`)
14. Modify `includes/cube3d.h` (add new prototypes)
15. Delete `src/libft.c`
16. Run `make fclean && make` to verify compilation
17. Run norminette to verify compliance