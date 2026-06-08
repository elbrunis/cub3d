# Line Reduction Plan

## Status Overview

| File | Violating Function | Body Lines | Total Functions | Extraction Needed |
|------|-------------------|------------|-----------------|-------------------|
| `main.c` | `main()` | 28 | 3 | ✅ Yes |
| `parse_map.c` | `parse_map()` | 33 | 4 | ✅ Yes |
| `read_map.c` | `read_map()` | 30 | 1 | ✅ Yes |
| `textures.c` | `get_extension()` | 40 | 4 | ✅ Yes |
| `raycaster_draw.c` | `calc_tex_x()` | 28 | 5 | ⚠️ New file needed |
| `raycaster.c` | `perform_dda()` | 30 | 5 | ⚠️ New file needed |
| `ft_split.c` | `ft_split()` | 31 | 5 | ⚠️ New file needed |
| `colors.c` | — | — | 3 | ✅ Already fixed (OK) |

> **Note:** `colors.c` was already resolved during the previous formatting pass. The `parse_colors()` function now sits at 27 lines (from brace to brace) and passes Norminette.

---

## 1. `main.c`

### Current State
- **Functions:** `print_error` (6), `game_loop` (14), `main` (28)
- **Total:** 3/5 functions

### Problem
`main()` (lines 39–67) has 28 lines.

### Extraction Plan
Extract the MLX hook setup into a new static helper:

```c
static void	setup_mlx_hooks(t_cube3d *game)
{
	mlx_hook(game->win, 2, 1L << 0, press_key, (void *)game);
	mlx_hook(game->win, 3, 1L << 1, release_key, (void *)game);
	mlx_hook(game->win, 17, 0, x_pres, (void *)game);
	mlx_loop_hook(game->mlx, game_loop, (void *)game);
}
```

- **Lines removed from `main()`:** 4 lines (mlx hooks block)
- **New `main()` length:** 24 lines
- **New function count:** 4/5 ✅

---

## 2. `parse_map.c`

### Current State
- **Functions:** `check_cell` (20), `check_line` (22), `skip_empty_lines` (8), `parse_map` (33)
- **Total:** 4/5 functions

### Problem
`parse_map()` (lines 71–104) has 33 lines.

### Extraction Plan
Extract the validation loop (lines 81–90) into a new static helper:

```c
static char	*check_map_lines(t_parse *parse, char **map, int *y)
{
	char	*err;

	while (map[*y] && map[*y][0] != '\0')
	{
		err = check_line(parse, map, *y);
		if (err)
		{
			free_map(map);
			return (err);
		}
		(*y)++;
	}
	return (NULL);
}
```

- **Lines removed from `parse_map()`:** 10 lines
- **New `parse_map()` length:** 23 lines
- **New function count:** 5/5 ✅

---

## 3. `read_map.c`

### Current State
- **Functions:** `read_map` (30) — plus 3 external prototypes at the top
- **Total:** 1/5 functions

### Problem
`read_map()` (lines 22–52) has 30 lines.

### Extraction Plan
Extract the list-cleanup-on-error block (lines 37–45) into a new static helper:

```c
static void	free_map_list(t_list_map *lst)
{
	t_list_map	*tmp;

	while (lst)
	{
		tmp = lst;
		free(lst->line);
		lst = lst->next;
		free(tmp);
	}
}
```

- **Lines removed from `read_map()`:** 8 lines
- **New `read_map()` length:** 22 lines
- **New function count:** 2/5 ✅

> **Note:** The 3 external prototypes at the top of `read_map.c` (`ft_lstnew_map`, `ft_lstadd_back_map`, `fill_array_and_free`) are non-static and violate the Norm. These should be moved to `cube3d.h` and removed from the file. This is a separate issue but worth noting.

---

## 4. `textures.c`

### Current State
- **Functions:** `save_extension` (17), `check_line_format` (7), `check_texture` (11), `get_extension` (40)
- **Total:** 4/5 functions

### Problem
`get_extension()` (lines 56–96) has 40 lines.

### Extraction Plan
Extract the extension validation and save block (lines 79–91) into a new static helper:

```c
static char	*validate_and_save_texture(t_parse *parse, char *type,
			char **split)
{
	int		len;
	char		*error;

	len = ft_strlen(split[0]);
	if (len < 5 || split[0][len - 1] != 'm' || split[0][len - 2] != 'p'
		|| split[0][len - 3] != 'x' || split[0][len - 4] != '.')
		return ("Invalid texture extension");
	error = save_extension(parse, type, split[0]);
	if (error)
		return (error);
	return (NULL);
}
```

- **Lines removed from `get_extension()`:** ~13 lines
- **New `get_extension()` length:** ~27 lines
- **New function count:** 5/5 ✅

> **Note:** `validate_and_save_texture` is a long name. A shorter name like `check_texture_ext` or `save_texture` could be used if needed.

---

## 5. `raycaster_draw.c`

### Current State
- **Functions:** `get_tex_color` (8), `calc_wall_bounds` (11), `draw_textured_line` (22), `draw_floor_ceiling` (24), `calc_tex_x` (28)
- **Total:** 5/5 functions — **at limit**

### Problem
`calc_tex_x()` (lines 88–116) has 28 lines. Adding a new function would make this 6/5.

### Extraction Plan
Extract the texture number selection logic (lines 92–105) into a helper. Since the file is at the 5-function limit, this helper must be moved to a new file.

**Proposed new file:** `src/raycasting/raycaster_utils.c`

```c
/* raycaster_utils.c */

#include "../../includes/cube3d.h"

void	set_tex_num(t_ray *r)
{
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
}
```

- **Lines removed from `calc_tex_x()`:** 8 lines
- **New `calc_tex_x()` length:** 20 lines
- **New function count:** `raycaster_draw.c` stays at 5/5 ✅
- **New file count:** `raycaster_utils.c` = 1/5 ✅

> **Also:** `is_out_of_bounds` from `raycaster.c` (10 lines) can be moved to `raycaster_utils.c` as well, freeing one slot in `raycaster.c` for its own extraction.

---

## 6. `raycaster.c`

### Current State
- **Functions:** `init_raycasting` (16), `calculate_step` (24), `is_out_of_bounds` (10), `perform_dda` (30), `raycasting` (16)
- **Total:** 5/5 functions — **at limit**

### Problem
`perform_dda()` (lines 71–101) has 30 lines.

### Extraction Plan
Extract the inner DDA loop (lines 78–96) into a helper. Since the file is at the 5-function limit, we must move an existing function out first.

**Step 1:** Move `is_out_of_bounds` to `src/raycasting/raycaster_utils.c` (shared with `set_tex_num` from `raycaster_draw.c`).

**Step 2:** Extract the DDA loop into a new static helper in `raycaster.c`:

```c
static void	run_dda_loop(t_cube3d *game, t_ray *r, int map_height)
{
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
}
```

- **Lines removed from `perform_dda()`:** 18 lines
- **New `perform_dda()` length:** 12 lines
- **New function count:** `raycaster.c` = 4/5 ✅
- **New file count:** `raycaster_utils.c` = 3/5 ✅ (with `is_out_of_bounds`, `set_tex_num`, and `run_dda_loop`? Wait, `run_dda_loop` would be in `raycaster.c`)

Wait, `run_dda_loop` is static in `raycaster.c`. So `raycaster_utils.c` would have `is_out_of_bounds` and `set_tex_num` = 2/5.

Actually, let me reconsider. The `run_dda_loop` would be static in `raycaster.c`. So after moving `is_out_of_bounds` out:
- `raycaster.c`: `init_raycasting`, `calculate_step`, `perform_dda` (now shorter), `run_dda_loop`, `raycasting` = 5/5 ✅
- `raycaster_utils.c`: `is_out_of_bounds`, `set_tex_num` = 2/5 ✅

This works perfectly.

---

## 7. `ft_split.c`

### Current State
- **Functions:** `is_space` (4), `word_count` (19), `frees_split` (8), `get_word` (13), `ft_split` (31)
- **Total:** 5/5 functions — **at limit**

### Problem
`ft_split()` (lines 67–98) has 31 lines.

### Extraction Plan
Extract the word-filling loop (lines 81–95) into a helper. Since the file is at the 5-function limit, this helper must be placed in a new file.

**Proposed new file:** `src/libft/ft_split_utils.c`

```c
/* ft_split_utils.c */

#include "../../includes/cube3d.h"

static char	**fill_split_words(char **res, const char *s)
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
				return (frees_split(res, j - 1), NULL);
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}
```

Wait, `is_space` and `get_word` and `frees_split` are currently static in `ft_split.c`. If `fill_split_words` is in a different file, it can't call static functions from `ft_split.c`. So I need to either:

1. Make `is_space`, `get_word`, and `frees_split` non-static (add them to the header)
2. Keep `fill_split_words` in `ft_split.c` and move something else out
3. Move `is_space`, `get_word`, and `frees_split` to `ft_split_utils.c` too

Option 3 is cleanest:
- `ft_split_utils.c`: `is_space`, `word_count`, `frees_split`, `get_word`, `fill_split_words` = 5/5
- `ft_split.c`: `ft_split` = 1/5

But that would be a big refactor. And `word_count` is only used by `ft_split`, so it could stay in `ft_split.c`.

Alternative: Keep `ft_split` at 5 functions and just shorten it by extracting something inline. But the function is 31 lines, we need to remove at least 6 lines.

Actually, looking at `ft_split`:
```c
char **ft_split(const char *s)
{
    char **res;
    int i;
    int j;
    int start;

    if (!s)
        return (NULL);
    res = malloc(sizeof(char *) * (word_count(s) + 1));
    if (!res)
        return (NULL);
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
                return (frees_split(res, j - 1), NULL);
            j++;
        }
    }
    res[j] = NULL;
    return (res);
}
```

The body has 31 lines. To get under 25, we need to remove at least 7 lines. Extracting the while loop (lines 81–95) removes 13 lines, which would make `ft_split` 18 lines. That's good.

But we can't add a 6th function to `ft_split.c`. So we need to either:
1. Move the helper to a new file and expose the static functions
2. Inline the helper (not possible since it's a loop)
3. Move `frees_split` to a new file (since it's a utility function)

Actually, `frees_split` is only used in `ft_split.c`. If we move it to a new file and make it non-static, we can add it to `cube3d.h`. Then `ft_split.c` has 4 functions, and we can add `fill_split_words` as the 5th.

**Revised plan for `ft_split.c`:**

1. Move `frees_split` to `ft_split_utils.c` (make it non-static, add prototype to `cube3d.h`)
2. `ft_split.c` now has 4 functions: `is_space`, `word_count`, `get_word`, `ft_split`
3. Add `fill_split_words` to `ft_split.c` as the 5th function
4. `ft_split_utils.c` has 1 function: `frees_split`

Wait, but `fill_split_words` would call `is_space`, `get_word`, and `frees_split`. If `fill_split_words` is in `ft_split.c`, it can call the static functions there. That's fine.

But `fill_split_words` needs to return `res` with `res[j] = NULL` set. So:

```c
static char	**fill_split_words(char **res, const char *s)
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
				return (frees_split(res, j - 1), NULL);
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}
```

Then `ft_split` becomes:
```c
char	**ft_split(const char *s)
{
	char	**res;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (word_count(s) + 1));
	if (!res)
		return (NULL);
	return (fill_split_words(res, s));
}
```

That's 10 lines. Perfect.

But we need to move `frees_split` out first to make room for `fill_split_words`. So:

**Step 1:** Move `frees_split` to `ft_split_utils.c` and add prototype to `cube3d.h`
**Step 2:** Add `fill_split_words` to `ft_split.c`

- `ft_split.c`: `is_space`, `word_count`, `get_word`, `fill_split_words`, `ft_split` = 5/5 ✅
- `ft_split_utils.c`: `frees_split` = 1/5 ✅

> **Note:** `frees_split` was static, so moving it requires adding a prototype to `cube3d.h`. This is acceptable since it's a utility function.

---

## New Files Required

| New File | Functions | Called From |
|----------|-----------|-------------|
| `src/raycasting/raycaster_utils.c` | `is_out_of_bounds`, `set_tex_num` | `raycaster.c`, `raycaster_draw.c` |
| `src/libft/ft_split_utils.c` | `frees_split` | `ft_split.c` (via `fill_split_words`) |

> **Makefile impact:** The Makefile uses `$(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)`, so new files in existing subdirectories are picked up automatically. No Makefile changes needed.

---

## Header Updates Required

The following prototypes must be added to `includes/cube3d.h`:

```c
/* raycaster_utils.c */
int		is_out_of_bounds(t_cube3d *game, t_ray *r, int map_height);
void		set_tex_num(t_ray *r);

/* ft_split_utils.c */
void		frees_split(char **res, int i);
```

> **Note:** `frees_split` loses its `static` qualifier when moved to `ft_split_utils.c`.

---

## Prototype Cleanup (read_map.c)

The 3 non-static prototypes at the top of `read_map.c` (lines 15–17) are a Norm violation:

```c
t_list_map	*ft_lstnew_map(char *line);
void		ft_lstadd_back_map(t_list_map **lst, t_list_map *new);
char		**fill_array_and_free(t_list_map *lst, int size);
```

These should be moved to `includes/cube3d.h` and removed from `read_map.c`. This is a related fix that should be done in the same pass.

---

## Execution Order

1. **Create `raycaster_utils.c`** and move `is_out_of_bounds`
2. **Update `raycaster_draw.c`** — extract `set_tex_num` and move to `raycaster_utils.c`
3. **Update `raycaster.c`** — extract `run_dda_loop` (now that `is_out_of_bounds` is moved out)
4. **Update `main.c`** — extract `setup_mlx_hooks`
5. **Update `parse_map.c`** — extract `check_map_lines`
6. **Update `read_map.c`** — extract `free_map_list`; also move prototypes to header
7. **Update `textures.c`** — extract `validate_and_save_texture`
8. **Create `ft_split_utils.c`** — move `frees_split`
9. **Update `ft_split.c`** — extract `fill_split_words`
10. **Update `includes/cube3d.h`** — add all new non-static prototypes
11. **Run `make`** and **run Norminette** to verify
