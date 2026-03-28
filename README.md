# C++ SFML Drawing Tablet 

## Overview
A custom, command-based drawing application built from scratch in C++ using the Simple and Fast Multimedia Library (SFML). Inspired by classic Turtle Graphics, this application parses text-based user commands to manipulate a virtual pen on the screen. 

This project was developed to demonstrate core programming fundamentals, including custom string parsing, 2D array manipulation, matrix-based history tracking, and file I/O operations.

## Key Features
* Custom Command Parser: Interprets string inputs to execute movement, rotation, and drawing actions.
* Command History Tracking: Dynamically displays valid, incomplete, and invalid commands in separate UI columns.
* Loop Logic: Supports nested-style `repeat` commands to execute complex geometric patterns.
* State Management: Tracks pen state (up/down), current angle, coordinates, and active colors.
* File I/O: Users can save their drawn patterns to text files and load them later to redraw sequences automatically.

## Supported Commands

### Movement & Drawing
* `fd <value>` or `forward <value>`: Moves the pen forward by the specified pixel value.
* `bk <value>` or `backward <value>`: Moves the pen backward.
* `rt <value>` / `lt <value>`: Rotates the pen to the right/left by the specified angle in degrees.
* `circle <radius>`: Draws a circle with the specified radius.

### Pen Settings
* `width <value>` or `w <value>`: Sets the thickness of the pen.
* `pu` / `pd`: Pen Up (moves without drawing) / Pen Down (resumes drawing).
* `color <color_name>`: Changes the pen color (e.g., RED, BLUE, CYAN, TRANSPARENT).

### Advanced Operations
* `repeat [times [commands]]`: Executes a set of commands multiple times. Example: `repeat [4 [fd 100 rt 90]]` draws a square.
* `save "<filename>"` / `load "<filename>"`: Saves or loads drawing sequences to/from a local text file.
* `cs` or `clear screen`: Clears the canvas.

## Technical Requirements & Setup
* **Language:** C++11 or higher.
* **Dependencies:** SFML (Simple and Fast Multimedia Library) 2.5+.
* **Fonts:** The application utilizes `arial.ttf` (included in the repository for cross-platform compatibility). 

**To Run Locally:**
Ensure SFML is properly linked in your compiler settings (graphics, window, and system modules required). Place the `arial.ttf` file in the same directory as your compiled executable.
