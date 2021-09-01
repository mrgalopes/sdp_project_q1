# Project q1
Project for System and Device Programming course at Politecnico di Torino

## Requirements
- A compiler with C++20 support
- CMake 3.20 or newer

## Project structure
`color_prog` is the main program, counting with CLI options. Pass `-h` or `--help` for help.
`tests` runs automated tests against the included example graphs.

## Platform compatibility
The program has been built and tested on Windows, Linux and MacOS environments.
Compilers used were MSVC 2019, GCC 9.3.0 and Clang 12.0.1 .
Building and testing on MacOS has been done solely based on CI.

## Build instructions
### Windows
- Open cmake-gui and point it to this project's directory.
- Define the build directory. A `build/` subdirectory is recommended.
- Click on "Configure" and choose the desired compiler, click on "Finish" and then "Generate"
- Compile the project.

### Linux
From the base directory (`sdp_project_q1/`), choose one of the following:

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

## Run Instructions

Given the binary is in the current directory (e.g. after build with previous Linux build instruction, 
do `cd build/bin/`), to run the program:

```sh
./color_prog path/to/graph/my_graph.gra # or my_other_graph.graph
```

###  List of flags

- `-b` or `--basic`: Selects Basic Algorithm, which is the greedy sequential algorithm. Is the default option, so it
can be skipped.

```sh
./color_prog -b path/to/graph/my_graph.gra 
# or
./color_prog --basic path/to/graph/my_graph.gra 
# or even
./color_prog path/to/graph/my_graph.gra 
```

- `-l` or `--luby`: Selects Luby Algorithm.

```sh
./color_prog -l path/to/graph/my_graph.gra 
# or
./color_prog --luby path/to/graph/my_graph.gra 
```

- `-j` or `--jones`: Selects Jones-Plassmann Algorithm.

```sh
./color_prog -j path/to/graph/my_graph.gra 
# or
./color_prog --jones path/to/graph/my_graph.gra 
```

- `-d` or `--ldf`: Selects the Largest Degree First (LDF) Algorithm.
 
```sh
./color_prog -d path/to/graph/my_graph.gra 
# or
./color_prog --ldf path/to/graph/my_graph.gra 
```

- `-t` or `--threads`: Selects the number of threads for the algorithms, if supported. Default is 4.

```sh
./color_prog -t 6 --luby path/to/graph/my_graph.gra # selects 6 threads for Luby Algorithm
# or
./color_prog --threads=6 --luby path/to/graph/my_graph.gra 
```

- `-s` or `--seed`: Selects a number to be used as random seed of the algorithm, if supported. Default is a time based
pseudo-random number.

```sh
# selects Luby Algorithm with random seed = 1, running multiple times should give the same coloring
./color_prog -s 1 --luby path/to/graph/my_graph.gra 
# or
./color_prog --seed=1 --luby path/to/graph/my_graph.gra 
```

- `-o` or `--output`: Outputs the coloring to a file given as argument. By default, the coloring is not saved.
```sh
# outputs coloring to a file called coloring.txt in current directory
./color_prog -o coloring.txt --luby path/to/graph/my_graph.gra
# or
./color_prog --output=coloring.txt --luby path/to/graph/my_graph.gra 
```

- `-h` or `--help`: Prints help for these options.
```sh
./color_prog -h
# or
./color_prog --help
```


## Authors
- Gabriel Lopes Rodrigues (s287315)
- Vinícius Massaki Benevides Kanaoka (s287000)
- Vitor Amaral Kiguchi (s287183)

## Licenses
This software uses the following open source libraries:

### Catch
`Boost Software License - Version 1.0`

### getopt
`LGPL`
