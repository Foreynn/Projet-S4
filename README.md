# Kalos -- Labyrinth solver

## How to run our software

### Step 1:

Run the `make` command in the root of the project repository.

### Step 2:

Run the newly created `main` file using this command `./main`.

## How to use our software

### Inputs:

Our software accepts labyrinth files in the form of an image. Labyrinths must have equal rows and columns, high enough resolution, and 1 entrance and 1 exit.

### How to solve

In order to solve the labyrinth, you must enter the entrance and exit coordinates (`(x, y)`) into the software. These coordinates start at `(0, 0)` in the top-left corner of the maze, `x` grows as you go down in the column and `y` grows as you go to the right of the row.

Then, you simply need to press the solve button.

### Outputs:
If you want to save the solved maze, you only need to press the save button.

## How to remove our software

Run the `make clean` command in the root of the project repository.