<task>
Audit the entire codebase against the official evaluation sheet requirements. You must act as the evaluator and verify if the current implementation passes all the mandatory checks.
</task>

<evaluation_criteria>
1. Introduction & Guidelines (Basics):

Check the codebase for Norm errors.

Verify the Makefile compiles correctly and does not relink.

Ensure the program starts securely without immediate segmentation faults.

2. Configuration & Error Handling:

Audit the .cub file parsing logic.

Verify that textures and RGB floor/ceiling colors are correctly parsed.

Ensure the program exits cleanly (no memory leaks) and displays an explicit error message when facing invalid configurations.

3. Map Validation:

Verify the map is strictly surrounded by walls.

Ensure the program rejects open maps or maps with invalid characters (ensuring spaces are handled correctly without triggering false errors unless touching a floor/player cell).

4. Technical Elements of the Display (MiniLibX):

Audit the MLX window creation and image management.

Verify the program remains stable and does not crash or leak memory when the window is minimized and restored.

5. Raycasting & Mechanics:

Verify the core 3D engine logic.

Check that the cardinal textures (North, South, East, West) are correctly applied to the corresponding wall orientations.

Ensure movement (WASD) and camera rotation (Left/Right arrows) respond correctly, and that wall collisions are flawlessly implemented.
</evaluation_criteria>

<instructions>
Read the relevant source files and Makefile. Generate a detailed markdown file named pre_evaluation_report.md. In this report, list each of the 5 criteria above and mark them as [PASS], [FAIL], or [NEEDS MANUAL TESTING], providing specific file names and line numbers if you detect a vulnerability or bug.
</instructions>