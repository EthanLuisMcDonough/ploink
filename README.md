# Ploink

Ploink is a 2D physics game where the user plays as a ball bouncing on bezier curves. The ball
must get to the goal while minimizing damage taken from hazards.

## Third party dependencies
- [SDL2](https://www.libsdl.org/): Cross platform library used for rendering game objects
  to the screen and processing user I/O. You will need to install SDL2 in order to run this
  project
- [JSON for Modern C++](https://github.com/nlohmann/json): Used for parsing the level json
  file. This library is included under [third-party/nlohmann](include/third-party/nlohmann).

## Build instructions for Linux or Raspbian
1. Clone repository
2. Install SDL2 and SDL2 build tools
3. CD into the repository directory and `mkdir build`
4. CD into build and run `cmake ..` and `make`
