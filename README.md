# CPPND: Capstone Snake Game Example

This is an extension of the [Snake Game](https://github.com/udacity/CppND-Capstone-Snake-Game) provided by Udacity. On top of the existing functionality, it also features restarting the game. By pressing ESC, player would have the option to restart or end the game.

<img src="snake_game.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Class Structure

The following classes are provided by the original repository.

- `Controller`
- `Game`
- `Renderer`
- `Snake`

A new class template `MessageBox`. `EscapeMessageBox` is a derived class from `MessageBox` representing a message box that gives player the option to restart or end the game when ESC is pressed.

## Concurrency

The original Snake Game is run on the main thread only. Here I adopt the game and make `Snake::Update` running on its own thread. `Snake::Update` is responsible for updating the position of the snake as well as growing, changing speed and direction. As long as the snake is alive and player does not request to end/restart the game, the thread will run on its own indefinitely. The main thread will be running the game and the controller. It will acquire the latest snake position, whenever a new frame needs to be rendered.

## Rubic Points

### Loop, Functions, I/O

- The project code is clearly organized into functions.
  - `snake.h` line `26` - `33`

- The project accepts input from a user as part of the necessary operation of the program.
  - `controller.cpp` line `10` - `49`

### Object Oriented Programming

- Classes use appropriate access specifiers for class members.
  - `game.h` line `13`
  - `message.h` line `17`

- All class data members are explicitly specified as public, protected, or private.
  - `snake.h` line `36`-`57`
  - `message.h` line `10`-`14` and line `18`-`20`

- Class constructors utilize member initialization lists.
  - `game.h` line `10`-`15`

- Classes encapsulate behavior.
  - `snake.h` class `Snake`

- Classes follow an appropriate inheritance hierarchy.
  - `message.h` class `MessageBox` and `EscapeMessageBox`

- Derived class functions override virtual base class functions.
  - `message.h` class `MessageBox` and `EscapeMessageBox`

- Templates generalize functions in the project.
  - `message.h` class `MessageBox`

### Memory Management

- The project makes use of references in function declarations.
  - `game.h` line `15`-`16`

- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
  - `main.cpp` line `20`-`21` where `std::unique_ptr` is used to ensure resource is cleaned up after program ends.

- The project uses smart pointers instead of raw pointers.
  - `game.cpp` line `10`

### Concurrency

- The project uses multithreading.
  - `Snake::Update` is run in a different thread than the main thread

- A mutex or lock is used in the project.
  - mutex is used throught out `snake.cpp` to ensure shared resource thread safety
