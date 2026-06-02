# cub3D Issues List

## CRITICAL (Will receive 0)

| # | Issue | Location | Status |
|---|-------|----------|--------|
| 1 | **Missing `bonus` rule in Makefile** | `Makefile` - Subject requires `all, clean, fclean, re, bonus` | [x] DONE |
| 2 | **Missing `-Wall` flag in Makefile** | `Makefile:8` - Subject requires `-Wall -Wextra -Werror` | [x] DONE |
| 3 | **ESC key not handled** | `src/hooks/key_hooks.c` - Subject requires ESC to close window cleanly | [x] DONE |
| 4 | **Left/Right arrow keys not handled** | `src/hooks/key_hooks.c` - Subject requires arrow keys to look left/right | [x] DONE |
| 5 | **Textures not applied in raycaster** | `src/raycasting/raycaster.c:3-33` - Uses single color `0xFFFFFF` instead of textures | [x] DONE |
| 6 | **Floor/ceiling colors not used** | `src/raycasting/raycaster.c:23-32` - Uses hardcoded `0x333333`/`0x555555` instead of parsed colors | [x] DONE |
| 7 | **Program name wrong** | `Makefile:1` - Is `cube3d`, should be `cub3D` | [x] DONE |
| 8 | **README.md completely wrong** | `README.md` - Written in Spanish, missing required sections (Description, Instructions, Resources) | [x] DONE |
| 15 | **CRITICAL: Spaces in map incorrectly rejected** | `src/parsing/parse_map.c:32-39` - Subject says "Spaces are a valid part of the map" but code treats spaces as openings | [x] DONE |
| 16 | **Subject example map fails** | `assets/maps/test_subject_exact.cub` - The exact example from the subject with spaces fails validation | [x] DONE |

## HIGH (Functional issues)

| # | Issue | Location | Status |
|---|-------|----------|--------|
| 9 | **No collision detection** | `src/hooks/move.c` - Player can walk through walls | [x] DONE |
| 10 | **Memory leak: map not freed properly** | `src/utils/free_game.c:35` - Uses `free(game->map)` instead of `free_map(game->map)` | [x] DONE |
| 11 | **Memory leak: texture paths not freed** | `src/utils/free_game.c` - `no_path`, `so_path`, `we_path`, `ea_path` never freed | [x] DONE |
| 12 | **libft not in separate folder** | Subject requires libft sources + Makefile in `libft/` folder | [ ] PENDING |
| 13 | **Map validation: map not required to be last** | `src/parsing/parsing.c` - Subject says "map content always has to be the last" but not enforced | [ ] PENDING |
| 14 | **XPM texture validation too strict** | `src/parsing/textures.c:48-54` - Only checks `.xpm` extension, should allow any texture path | [x] DONE |

## MEDIUM (Norm/Code quality)

| # | Issue | Location | Status |
|---|-------|----------|--------|
| 17 | **Comments using `//`** | Multiple files - 42 Norm requires `/* */` only | [x] DONE |
| 18 | **Commented-out files should be removed** | `src/raycasting/raycaster_sucio.c`, `src/render/map2d.c` | [x] DONE |
| 19 | **Variable declaration not at top** | `src/main.c:34` - `const char *error` declared mid-function | [x] DONE |
| 20 | **Potential buffer overflow in DDA** | `src/raycasting/raycaster.c:97` - No bounds checking for `map[r->mapY][r->mapX]` | [x] DONE |
| 21 | **`fill_array_and_free` memory issue** | `src/parsing/reed_map.c:65-80` - Frees list nodes but loses pointer to `line` content | [ ] PENDING |

## LOW (Minor issues)

| # | Issue | Location | Status |
|---|-------|----------|--------|
| 22 | **Unused defines** | `includes/cube3d.h` - `WIDTH`, `HEIGHT`, `PLAYER_LEN`, `SQUARE_LEN`, `GRAY`, `WHITE`, `ORANGE` | [x] DONE |
| 23 | **Inconsistent naming** | `src/parsing/reed_map.c` - "reed" should be "read" | [x] DONE |
| 24 | **Missing newline at end of Makefile** | `Makefile:30` | [x] DONE |
| 25 | **Error message format** | `src/main.c` - Should be "Error\n" + message, currently "Error\n" + message + ": " + strerror | [ ] PENDING |

## Test Results Summary

| Test Case | Result | Notes |
|-----------|--------|-------|
| Simple valid map | ✅ PASS | Basic 5x5 map works |
| Open map detection | ✅ PASS | Correctly rejects open maps |
| Invalid characters | ✅ PASS | Correctly rejects invalid chars |
| Multiple players | ✅ PASS | Correctly rejects multiple players |
| Different element order | ✅ PASS | Elements in any order works |
| **Subject example with spaces** | ✅ **PASS** | Now correctly parses the subject example |
| Missing configurations | ✅ PASS | Correctly rejects missing configs |
| No player | ✅ PASS | Correctly rejects maps without player |
| Duplicate texture | ✅ PASS | Correctly rejects duplicate textures |
| Invalid color | ✅ PASS | Correctly rejects invalid colors |

## Fixed Map Validation Logic

For each cell in the map:
1. Skip spaces (` `) and walls (`1`)
2. For floor (`0`) and player (`NSEW`) cells, check neighbors:
   - Left/right must not be space or edge
   - Up/down: if neighbor row exists at this x, must not be space
   - If neighbor row is shorter (x beyond its length), that's OK (void)
3. Reject with "Map is not closed" if any check fails
