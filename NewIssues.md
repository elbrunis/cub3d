# Cube3D Pre-Evaluation Report

## 1. Introduction & Guidelines (Basics)

**Status: [FAIL]**

### Norm Violations Found:

**NORM-001: Too Many Functions Per File** - CRITICAL
| File | Count | Max Allowed |
|------|-------|-------------|
| `src/libft.c` | 15 | 5 |
| `src/raycasting/raycaster.c` | 9 | 5 |
| `src/hooks/move.c` | 8 | 5 |
| `src/utils/init_game.c` | 6 | 5 |
| `src/parsing/read_map.c` | 6 | 5 |

**NORM-002: Functions Exceeding 25 Lines** - CRITICAL
| File | Function | Line Count |
|------|----------|------------|
| `src/main.c:19` | `main()` | 28 lines |
| `src/libft.c:171` | `ft_split()` | 28 lines |
| `src/parsing/parse_map.c:94` | `parse_map()` | 32 lines |
| `src/raycasting/raycaster.c:13` | `draw_textured_line()` | 28 lines |
| `src/raycasting/raycaster.c:152` | `perform_dda()` | 31 lines |
| `src/utils/init_game.c:77` | `init_game()` | 29 lines |
| `src/utils/free_game.c:48` | `free_game()` | 30 lines |

**NORM-003: C++ Style Comments** - HIGH
| File | Line | Comment |
|------|------|---------|
| `src/raycasting/raycaster.c` | 21 | `// cambio` |
| `src/raycasting/raycaster.c` | 49 | `//cambio` |
| `src/raycasting/raycaster.c` | 55 | `// cambio realizado` |

**NORM-004: Variable Declaration with Initialization** - HIGH
- `src/render/window.c:16`: `t_cube3d *game = (t_cube3d *)data;`
- Norm requires: declaration at top, then assignment on separate line

**NORM-005: camelCase Struct Member Names** - MEDIUM
- `includes/cube3d.h:69-85`: `cameraX`, `rayDirX`, `rayDirY`, `mapX`, `mapY`, `deltaDistX`, `deltaDistY`, `sideDistX`, `sideDistY`, `stepX`, `stepY`, `perpWallDist`, `lineHeight`, `drawStart`, `drawEnd`

**NORM-006: Missing Blank Line Before Function** - MEDIUM
- `src/libft.c:171`: No blank line before `ft_split` function definition

**NORM-007: Multiple Consecutive Blank Lines** - MEDIUM
- `src/parsing/read_map.c:3`
- `src/get_next_line.c:4`

**NORM-008: Spanish Comments** - LOW
- `src/parsing/read_map.c:75-77`: Spanish comment block
- `src/raycasting/raycaster.c:21,49,55`: Spanish debug comments

---

## 2. Configuration & Error Handling

**Status: [FAIL]**

### Critical Bugs Found:

**BUG-001: Memory Leak in `get_extension()` - Success Path** - CRITICAL
- **File**: `src/parsing/textures.c:53-70`
- **Issue**: On line 53, `ft_split` allocates `split`. On the success path (lines 62-70), the function returns NULL on line 70 without ever calling `free_split(split)`. The error paths correctly free `split`, but the success path does not.
- **Impact**: Memory leak on every successful texture parse (4 leaks total per game start)

**BUG-002: Memory Leak in `get_extension()` - Empty Split** - HIGH
- **File**: `src/parsing/textures.c:54-55`
- **Issue**: If `ft_split` succeeds but produces zero words (e.g., input is all whitespace), `split[0]` is NULL. The function returns `"split error"` without freeing the allocated `split` array.
- **Fix**: Add `if (split) free_split(split);` before returning

**BUG-003: `(void)parse` Unnecessary Cast** - LOW
- **File**: `src/parsing/textures.c:49`
- **Issue**: `(void)parse;` suppresses unused parameter warning, but `parse` IS used later on line 62. This is misleading but not a functional bug.

---

## 3. Map Validation

**Status: [FAIL]**

### Critical Bugs Found:

**BUG-004: Map Validation Gap - Open Map Not Detected** - HIGH
- **File**: `src/parsing/parse_map.c:37-48`
- **Issue**: `check_cell()` validates walkable tiles are surrounded by walls. However, when the row above or below is an empty string, `ft_strlen` returns 0, and the boundary check `x < up_len` is always false, causing the check to be silently skipped.
- **Impact**: Maps with empty lines before/after the actual map content can have walkable tiles on the boundary that are not detected as "open"

**BUG-005: Null Pointer Dereference Risk in `read_map()`** - HIGH
- **File**: `src/parsing/read_map.c:90-91`
- **Issue**: `ft_lstnew_map` can return NULL if malloc fails. On line 90-91, the return value `tmp` is used directly without a NULL check. Passing NULL to `ft_lstadd_back_map` would cause a NULL dereference.

---

## 4. Technical Elements of the Display (MiniLibX)

**Status: [NEEDS MANUAL TESTING]**

### Issues Found:

**BUG-006: `exit(0)` Bypasses Normal Cleanup Path** - MEDIUM
- **File**: `src/main.c:10-11`
- **Issue**: `game_loop()` calls `free_game(game)` then `exit(0)`. While `free_game` handles cleanup, `exit()` does not unwind the stack, so resources allocated by mlx_loop internals may not be properly cleaned up.

**BUG-007: Dead Code in `main()`** - LOW
- **File**: `src/main.c:48`
- **Issue**: `mlx_loop(game->mlx)` on line 47 does not return (it loops forever internally). The `free_game(game)` call on line 48 is dead code that will never execute.

---

## 5. Raycasting & Mechanics

**Status: [FAIL]**

### Critical Bugs Found:

**BUG-008: Swapped WASD Key Mappings** - CRITICAL
- **File**: `includes/cube3d.h:23-25`
- **Issue**: `K_A` is defined as `100` (ASCII for 'd') and `K_D` is defined as `97` (ASCII for 'a'). These values are swapped.
- **Impact**: Player will strafe right when pressing A and strafe left when pressing D
- **Fix**: Swap the values: `K_A 97` and `K_D 100`

**BUG-009: No Player Collision Buffer** - LOW
- **File**: `src/hooks/move.c:3-17`
- **Issue**: The `is_wall` function checks only the integer cell the player is trying to move into. There is no buffer/margin, meaning the player's view can clip through walls at close range.

**BUG-010: Redundant Bounds Check in `draw_floor_ceiling`** - LOW
- **File**: `src/raycasting/raycaster.c:46-73`
- **Issue**: `draw_textured_line` already clamps `r->drawStart` and `r->drawEnd` to valid ranges. `draw_floor_ceiling` repeats these same checks redundantly.

---

## Summary by Severity

| Severity | Count | Issues |
|----------|-------|--------|
| **CRITICAL** | 3 | BUG-001 (memory leak), BUG-008 (swapped keys), NORM-001/002 (norm violations) |
| **HIGH** | 5 | BUG-002, BUG-004, BUG-005, NORM-003, NORM-004 |
| **MEDIUM** | 5 | BUG-006, NORM-005, NORM-006, NORM-007, DESIGN-002 |
| **LOW** | 8 | BUG-003, BUG-007, BUG-009, BUG-010, NORM-008, PARSE-002/3/4, DESIGN-001/3 |

---

## Top Priority Fixes Required

1. **Swap `K_A` and `K_D`** in `cube3d.h` - A/D controls are backwards
2. **Add `free_split(split)` before success return** in `textures.c:get_extension` - leaks 4 times per parse
3. **Split into max 5 functions per file** - libft.c, raycaster.c, move.c, init_game.c, read_map.c all exceed the limit
4. **Remove `//` comments** - replace with `/* */` style
5. **Fix `x_pres` variable declaration** - separate declaration from assignment
6. **Rename camelCase struct members** to snake_case
7. **Fix map validation** for empty-line boundary cases
8. **Add NULL check** after `ft_lstnew_map` in `read_map`

---

**Overall Assessment**: The project will likely fail evaluation due to critical norm violations (too many functions per file, functions exceeding 25 lines) and functional bugs (swapped A/D keys, memory leaks). The raycasting engine appears functionally correct, but the code organization needs significant refactoring to comply with 42 standards.
