CHIP-8 Emulator
Overview
This project is a simple emulator for the CHIP-8 programming language. It uses the SDL (Simple DirectMedia Layer) library for graphics rendering and event handling.

Features
SDL-based graphics window for rendering.
Configurable window dimensions and colors.
Basic event handling for quitting the application.
Simple structure for emulating CHIP-8 instructions (to be implemented).
Prerequisites
Before running the emulator, ensure you have the following installed:

SDL2: The library required for graphics and event handling. You can install it using your package manager.
Building the Emulator
Clone the repository (if applicable):

bash
Copy code
git clone https://github.com/hshubbard/chip8-emulator.git
cd chip8-emulator
Install SDL2: For example, on Ubuntu you can run:

bash
Copy code
sudo apt-get install libsdl2-dev
Compile the code: Use gcc to compile the code. In the project directory, run:

bash
Copy code
make
Alternatively, you can manually compile the code using:

bash
Copy code
gcc chip8.c -o chip8 -Wall -Wextra -Werror -I/usr/include/SDL2 -lSDL2
Running the Emulator
To run the emulator, execute the following command:

bash
Copy code
./chip8 [width] [height]
width: Optional parameter to set the width of the emulator window (default: 64).
height: Optional parameter to set the height of the emulator window (default: 32).
Example:
bash
Copy code
./chip8 1280 640
Key Components
sdl_t: Structure containing SDL window and renderer objects.
config_t: Configuration structure for the emulator's appearance and behavior.
chip8_t: Structure representing the state of the CHIP-8 emulator.
init_sdl(): Initializes SDL and creates the window and renderer.
set_config_args(): Configures emulator settings based on command-line arguments.
handle_input(): Processes user input events.
clear_window(): Clears the window with the specified background color.
update_window(): Presents the rendered frame.
Cleaning Up
To clean up resources upon exiting the emulator, the quit_sdl() function is called, which destroys the SDL renderer and window, and quits SDL.

Future Improvements
Implement the actual CHIP-8 instruction set and memory management.
Add support for loading and executing CHIP-8 ROM files.
Enhance input handling for keyboard events (e.g., arrow keys).
Improve graphical rendering and user interface.

License
This project is licensed under the MIT License. See the LICENSE file for details.
