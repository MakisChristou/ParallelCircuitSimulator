## Compilation

Run `make` while in the main project directory. The source code was compiled on Ubuntu 19.10 without any extra dependecies needed.

## CLI Arguments
- `./simulator -C <path/to/bench/file>`
- `./simulator -T <unit_of_time>`
- `./simulator -I <path/to/input/file>`

## Example Usage

`./simulator -C ISCAS/iscas89/s27.bench` runs the simulator on s27.bench

`./simulator -C ISCAS/iscas89/s27.bench -T s` runs the simulator on s27.bench and returns in std out the execution time in seconds

`./simulator -C ISCAS/iscas89/s27.bench -T ns` runs the simulator on s27.bench and returns in std out the execution time in nanoseconds

`./simulator -C ISCAS/iscas89/s27.bench -T us` runs the simulator on s27.bench and returns in std out the execution time in microseconds

`./simulator -C ISCAS/iscas89/s27.bench -T ms` runs the simulator on s27.bench and returns in std out the execution time in miliseconds

`./simulator -C ISCAS/iscas89/s208.1.bench -I TESTS/iscas89/test\ suite\ 1/s208.vec` runs the simulator on *s27.bench* with input file *s208.vec*

## Scripts
With the simulator two simple bash scripts are included. The one *autocompile.sh* is just used to recompile the program whenever an edit to the source code is made. The second and more important script called *measure_cpu_time.sh* runs the simulator on all *ISCAS89* and *ISCAS85* bench files and times the execution time in miliseconds. It then saves it in a file called Results.
