# Project q1
Project for System and Device Programming course at Politecnico di Torino

## Requirements
- A compiler with C++20 support
- CMake 3.20 or newer

## Project structure
`color_prog` is the main program, counting with CLI options. Pass `-h` or `--help` for help.
`tests` runs automated tests against the included example graphs.

## Platform compatibility
The program has been built and tested on Windows and Linux environments.
Compilers used were MSVC 2019, GCC 9.3.0 and Clang.
No testing has been done on MacOS environments.

## Build instructions
### Windows
- Open cmake-gui and point it to this project's directory.
- Define the build directory. A `build/` subdirectory is recommended.
- Click on "Configure" and choose the desired compiler, click on "Finish" and then "Generate"
- Compile the project.

### Linux
- If using Make, run:
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```
- Alternatively, run:
```
cmake -B ./build
cmake --build ./build --config Release
```
Use the `-DCMAKE_CXX_COMPILER` and `-DCMAKE_C_COMPILER` options to define the used compiler.

## Authors
- Gabriel Lopes Rodrigues (s287315)
- Vinícius Massaki Benevides Kanaoka (s287000)
- Vitor Amaral Kiguchi (s287183)
