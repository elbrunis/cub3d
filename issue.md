# cub3D Issues List

## CRITICAL (Will receive 0)

| # | Issue | Location | Status |
|---|-------|----------|--------|
| 1 | **Missing `bonus` rule in Makefile** | `Makefile` | [x] DONE |
| 2 | **Missing `-Wall` flag in Makefile** | `Makefile:8` | [x] DONE |
| 3 | **ESC key not handled** | `src/hooks/key_hooks.c` | [x] DONE |
| 4 | **Left/Right arrow keys not handled** | `src/hooks/key_hooks.c` | [x] DONE |
| 5 | **Textures not applied in raycaster** | `src/raycasting/raycaster.c` | [x] DONE |
| 6 | **Floor/ceiling colors not used** | `src/raycasting/raycaster.c` | [x] DONE |
| 7 | **Program name wrong** | `Makefile:1` | [x] DONE |
| 8 | **README.md completely wrong** | `README.md` | [x] DONE |
| 15 | **Spaces in map incorrectly rejected** | `src/parsing/parse_map.c` | [x] DONE |
| 16 | **Subject example map fails** | Subject example with spaces | [x] DONE |
| 26 | **Uses `atoi` instead of `ft_atoi`** | `src/parsing/colors.c:41` | [x] DONE |
| 27 | **Memory leak: `split` not freed on duplicate texture** | `src/parsing/textures.c:62-64` | [x] DONE |
| 28 | **Memory leak: `t_list_map` nodes never freed** | `src/parsing/read_map.c:53-70` | [x] DONE |
| 29 | **File descriptor leak on missing configurations** | `src/parsing/parsing.c:86-87` | [x] DONE |
| 30 | **Memory leak: map not freed on `check_empty_end` error** | `src/parsing/parse_map.c:116-118` | [x] DONE |
| 31 | **Memory leak: map not freed on missing player error** | `src/parsing/parse_map.c:119-120` | [x] DONE |
| 32 | **NULL dereference risk** | `src/main.c:27-28` | [x] DONE |

## HIGH (Functional issues)

| # | Issue | Location | Status |
|---|-------|----------|--------|
| 9 | **No collision detection** | `src/hooks/move.c` | [x] DONE |
| 10 | **Memory leak: map not freed properly** | `src/utils/free_game.c` | [x] DONE |
| 11 | **Memory leak: texture paths not freed** | `src/utils/free_game.c` | [x] DONE |
| 12 | **libft not in separate folder** | Subject requires libft in `libft/` folder | [ ] PENDING |
| 13 | **Map validation: map not required to be last** | `src/parsing/parsing.c` | [ ] PENDING |
| 14 | **XPM texture validation too strict** | `src/parsing/textures.c` | [x] DONE |

## MEDIUM (Norm/Code quality)

| # | Issue | Location | Status |
|---|-------|----------|--------|
| 17 | **Comments using `//`** | Multiple files | [x] DONE |
| 18 | **Commented-out files should be removed** | `src/raycasting/raycaster_sucio.c`, `src/render/map2d.c` | [x] DONE |
| 19 | **Variable declaration not at top** | `src/main.c:34` | [x] DONE |
| 20 | **Potential buffer overflow in DDA** | `src/raycasting/raycaster.c` | [x] DONE |
| 21 | **`fill_array_and_free` memory issue** | `src/parsing/read_map.c:53-70` | [x] DONE |
| 33 | **Wrong error format for missing arguments** | `src/main.c:26` | [x] DONE |
| 34 | **Error format inconsistency in init_game** | `src/utils/init_game.c:95,101` | [x] DONE |
| 35 | **Spanish comment in libft.c** | `src/libft.c:171-175` | [x] DONE |
| 36 | **Typo in error message** | `src/parsing/parse_map.c:61` | [x] DONE |
| 37 | **GNL helper functions not static** | `src/get_next_line.c:7,16,40,66` | [x] DONE |

## LOW (Minor issues)

| # | Issue | Location | Status |
|---|-------|----------|--------|
| 22 | **Unused defines** | `includes/cube3d.h` | [x] DONE |
| 23 | **Inconsistent naming** | `src/parsing/reed_map.c` | [x] DONE |
| 24 | **Missing newline at end of Makefile** | `Makefile:30` | [x] DONE |
| 25 | **Error message format** | `src/main.c` | [x] DONE |

## Test Results Summary

| Test Case | Result | Notes |
|-----------|--------|-------|
| Missing arguments | ✅ PASS | `Error\nmissing arguments` |
| File not found | ✅ PASS | `Error\nThe file could not be opened correctly: No such file or directory` |
| Invalid extension | ✅ PASS | `Error\nInvalid extension` |
| Open map | ✅ PASS | `Error\nMap is not closed` |
| Invalid character | ✅ PASS | `Error\ninvalid char in the map` |
| Multiple players | ✅ PASS | `Error\nThere is more than one player on the map` |
| Duplicate texture | ✅ PASS | `Error\nDuplicate configuration detected` |
| Missing config | ✅ PASS | `Error\nThere is an invalid character in the map file` |
| No player | ✅ PASS | `Error\nMissing player` |
| map.cub | ✅ PASS | Runs successfully |
| Subject example with spaces | ✅ PASS | Runs successfully |
| Simple valid map | ✅ PASS | Runs successfully |
| Different element order | ✅ PASS | Runs successfully |

## Summary

| Severity | Total | Done | Pending |
|----------|-------|------|---------|
| 🔴 Critical | 17 | 17 | 0 |
| 🟡 High | 6 | 4 | 2 |
| 🟠 Medium | 10 | 10 | 0 |
| 🔵 Low | 4 | 4 | 0 |

**All critical and medium issues resolved.** Only 2 high issues remain (libft folder structure, map-last enforcement).

-----------infite loop-------------------------
Build succeeds with zero warnings. Here's what was done:
File modified: src/parsing/read_map.c
New function added: pad_map_rows(char **map) (lines 75-110)
How it works:
1. First pass: iterates all rows to find max_width (the longest row)
2. Second pass: any row shorter than max_width gets reallocated and padded with spaces (' ') to match max_width
3. After padding, char **map is a perfect rectangle — every row has identical length
Why this fixes the infinite loop:
The DDA loop in raycaster.c:162-164 checks r->mapX >= row_len where row_len = ft_strlen(game->map[r->mapY]). Before this fix, stepping into a short row would give a small row_len, but stepping further could land on garbage memory beyond the string's null terminator. Now all rows are the same length, so the bounds check is consistent and the break fires reliably.
The existing DDA bounds checks are preserved as a safety net — they still protect against any edge case where a ray escapes the map entirely.