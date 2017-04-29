# Voxelpaint
Voxelpaint is a three-dimensional version of Microsoft Paint built using C++ and OpenGL.
Authors: @joeylmaalouf, @jovanduy, @jsutker, @sarahwalters
See [the project website](https://joeylmaalouf.github.io/SoftSysViolentViolets) for more detail.

![Voxelpaint model](./reports/voxelpaint_model.png)

### Dependencies
- [cpplint](https://pypi.python.org/pypi/cpplint)
- g++
- build-essential
- freeglut3-dev

For a complete install on ubuntu, run: `pip install cpplint && sudo apt-get install -y g++ build-essential freeglut3-dev`

To install on Mac, run `pip install cpplint`

### Usage
Running `make && ./voxelpaint` starts Voxelpaint. Type `h` for the help page to display the commands:
- **Move cursor:**
    - `l/r` arrow keys: x-axis
    - `u/d` arrow keys: y-axis
    - `page u/d` keys: z-axis
- **Place voxel:**
    - `<space>`: place
    - `<delete>`: erase
- **History:**
    - `u`: undo
    - `ctrl-u`: redo
- **Camera controls:**
    - `w/s`: rotate around x-axis
    - `a/d`: rotate around y-axis
    - `q/e`: rotate around z-axis
    - `z`: zoom out
    - `x`: zoom in
    - `r`: reset
- **Other controls:**
    - `c<red><green><blue>`: set color with rgb values
    - `k<path/to/file>`: export current world to .3dp
    - `l<path/to/file>`: load existing world from .3dp
    - `f<path/to/file>`: export current world to .stl
    - `h`: display help menu
    - `ctrl-c`: exit
