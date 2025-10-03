Sorting Visualizer
This project is a sorting algorithm visualization tool implemented in C using the SDL2 library. It supports multiple sorting algorithms (Bubble, Selection, Insertion, Quick, and Merge Sort) and allows visualization of the sorting process on arrays of integers, floats, or Student structures. The tool displays real-time statistics (comparisons, memory accesses, and execution time) and supports various input distributions (Random, Sorted, Reverse, Nearly Sorted, Duplicates, Pyramid).
The project is developed as part of a university assignment by Mohamed Naby NDAW, Diago Alioune TALL, and Madeleine BIAYE.
Features

Visualization: Displays arrays as vertical bars, with highlighted elements during comparisons and swaps.
Sorting Algorithms: Implements Bubble, Selection, Insertion, Quick, and Merge Sort with generic support for different data types.
Data Types: Supports sorting integers, floats, and Student structures (by age or grade).
Distributions: Generates arrays with various distributions to test algorithm performance.
Statistics: Tracks and displays comparisons, memory accesses, and execution time in real-time.
Interactivity: Allows stopping the sorting process with ESC or Space key.

Prerequisites
To compile and run this project, you need the following packages installed:

SDL2: For rendering the visualization.
SDL2_ttf: For rendering text (statistics display).
GCC: For compiling the C code.

On Ubuntu (or WSL with Ubuntu), install the required packages using:
sudo apt update
sudo apt install gcc libsdl2-dev libsdl2-ttf-dev

Ensure the fonts/DejaVuSans.ttf font file is present in the project directory for text rendering. You can download it from DejaVu Fonts or use another TTF font by updating the path in visual.c.
Project Structure

main/main.c: Main program loop, handles user input and coordinates sorting.
visual/visual.c, visual/visual.h: Handles SDL2 visualization and text rendering.
sorting/sorting.c, sorting/sorting.h: Implements sorting algorithms and event handling.
stats/stats.c, stats/stats.h: Tracks and manages sorting statistics.
utils/utils.c, utils/utils.h: Generates arrays with various distributions and comparison functions.
fonts/DejaVuSans.ttf: Font file for rendering statistics (ensure it exists).

Compilation
Compile the project using the following command from the project root directory:
gcc -Wall -Werror -o sorting_visualizer main/main.c visual/visual.c sorting/sorting.c stats/stats.c utils/utils.c -lSDL2 -lSDL2_ttf

This command:

Enables all warnings (-Wall) and treats warnings as errors (-Werror).
Links SDL2 and SDL2_ttf libraries.
Outputs the executable as sorting_visualizer.

Execution
Run the program with:
./sorting_visualizer

Usage
The program starts with an array of 100 integers in a random distribution. Use the following keys to interact:

Sorting Algorithms:
b: Bubble Sort
s: Selection Sort
i: Insertion Sort
q: Quick Sort
m: Merge Sort


Distributions:
r: Random
t: Sorted
v: Reverse Sorted
n: Nearly Sorted
d: Duplicates
p: Pyramid


Data Types:
f: Float
g: Student (sort by grade)
a: Student (sort by age)


Control:
ESC or Space: Stop the current sort
Close the window to exit



The console displays the array before and after sorting, and the SDL window shows the visualization with real-time statistics.
Troubleshooting

Font Error: If fonts/DejaVuSans.ttf is missing, download it or update the font path in visual.c.
SDL2 Errors: Ensure libsdl2-dev and libsdl2-ttf-dev are installed.
Compilation Errors: Verify all source files are in the correct directories (main/, visual/, etc.) and paths in the compilation command match your structure.

Useful Links

SDL2 Documentation: Official SDL2 documentation.
SDL2_ttf Documentation: Guide for SDL2_ttf usage.
DejaVu Fonts: Source for the TTF font used in the project.

Credits
Developed by:

Mohamed Naby NDAW
Diago Alioune TALL
Madeleine BIAYE
