## Violent Violets Preliminary Report
#### Joe Sutker, Joey Maalouf, Jordan Van Duyne, Sarah Walters

The goal of our project is to create a three-dimensional version of Microsoft Paint. We’d like to learn about 3D graphics and C++. We plan to utilize OpenGL to render our graphics, which will be voxel-based (as MS Paint is pixel-based). OpenGL abstracts away the lowest-level graphics primitives and provides wrapper functions which make it easier to model, render, and manipulate three-dimensional objects. We’re choosing to use OpenGL because we would rather focus on the project-specific details than a low-level implementation. We’re choosing to use C++ because it’s more commonly used with OpenGL.

At minimum, we’d like to be able to create and delete three-dimensional shapes with specified colors. We have several ideas for stretch goals, primarily based on making more user-friendly features: we could make it possible to save and load drawings, we could allow texturing of shapes, we could provide an undo/redo mechanism, or we could provide several specialized brush shapes. We’ve already implemented something close to the minimum viable product -- GIF included below (writing "HELLO WORLD!" in voxels, displayed at 3x speed).

![writing "HELLO WORLD!" in voxels, displayed at 3x speed](hello-world.gif)


### Progress to date
As of now, we’ve implemented a camera which views a world, controls for the camera view, a cursor and controls to move the cursor around the world, and the ability to click to place and delete voxels.
Here are the cards we’ve completed this sprint. Each card’s description includes a link to the pull request which completed the card.
- [OpenGL Hello World](https://trello.com/c/pXb4x7MZ)
- [Underlying world class](https://trello.com/c/Wsl5f7qO)
- [Cursor class](https://trello.com/c/22hL6B9G)
- [Voxel class](https://trello.com/c/ysQ4qT9H)
- [Camera class](https://trello.com/c/QnuuaKd0)
- [Makefile](https://trello.com/c/yFRz9bYW)
- [Main graphics update loop](https://trello.com/c/xe74JuLG)
- [Include guards for header files](https://trello.com/c/DppG8TyO)
- [Different brush shapes](https://trello.com/c/6dNm9YCZ)
- [Rotating/zooming camera](https://trello.com/c/fXf3kSMt)
- [Control cursor position based on keyboard input](https://trello.com/c/G5B4nzxW)
- [Block creation upon left click and deletion upon right click](https://trello.com/c/X5vCaCEW)
- [Cursor color rendering/blending](https://trello.com/c/9zDY9SvC)

### Annotated Bibliography
- [General introductory reference on OpenGL](http://www.glprogramming.com/red/chapter01.html) This tutorial describes OpenGL’s capabilities, gives a high-level overview of its rendering pipeline, points to common libraries, and explains double-buffered animation.
- [Tutorial for rotation in a plane](http://www.lighthouse3d.com/tutorials/glut-tutorial/mouse-putting-it-all-together/) This tutorial provides an example of triggering events upon mouse click / mouse motion in OpenGL and describes how to set up ground plane rotation upon mouse drag.
- [C++ tutorials point](https://www.tutorialspoint.com/cplusplus/) This website has a lot of examples and documentation for many C++ functions. Anytime we need to look up a C++-specific function or syntax, this is our go-to resource.

### Product Backlog
https://trello.com/b/3ElQkPlR/softsysviolentviolets
