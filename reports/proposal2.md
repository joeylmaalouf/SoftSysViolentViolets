# Project 2 Proposal

### Software Systems

##### Joe, Joey, Jordan, Sarah

#### Proposal

The goal of our project is to create a three-dimensional version of Microsoft Paint. We’d like to learn about 3D graphics and C++. We plan to utilize OpenGL to render our graphics, which will be voxel-based (as MS Paint is pixel-based). OpenGL abstracts away the lowest-level graphics primitives and provides wrapper functions which make it easier to model, render, and manipulate three-dimensional objects. We’re choosing to use OpenGL because we would rather focus on the project-specific details than a low-level implementation. We’re choosing to use C++ because it’s more commonly used with OpenGL.

At minimum, we’d like to be able to create and delete three-dimensional shapes with specified colors. We have several ideas for stretch goals, primarily based on making more user-friendly features: we could make it possible to save and load drawings, we could allow texturing of shapes, or we could provide several specialized brush shapes.

We’re most concerned about translating two-dimensional screen space into three-dimensional world space -- if the user clicks on the screen to fill in a voxel, we know the horizontal & vertical position of the voxel but not the “depth” of the voxel. We are considering the following potential solutions (we’re leaning towards the “cursor” solution because it’s mathematically simpler and gives the user more control):

- Putting a “cursor” of sorts into the world which can be manipulated using the mouse or keys. The cursor looks like a shadow of a voxel, and there are commands which place a block at the current cursor position, modify the block at the current cursor position, etc.

- Essentially raycasting: drawing a line from the clicked coordinate into the world until it hits something, and putting a voxel there. This would require a “start object” in the scene and would prevent us from placing voxels anywhere that no others exist already. It would also make placing larger groups of voxels at once more difficult to measure; it would be easy to paint continuously towards yourself, but hard to paint continuously in any other direction.

#### Annotated Bibliography

- [General introductory reference on OpenGL](http://www.glprogramming.com/red/chapter01.html)
  - This tutorial describes OpenGL’s capabilities, gives a high-level overview of its rendering pipeline, points to common libraries, and explains double-buffered animation.

- [Tutorial for rotation in a plane](http://www.lighthouse3d.com/tutorials/glut-tutorial/mouse-putting-it-all-together/)
  - This tutorial provides an example of triggering events upon mouse click / mouse motion in OpenGL and describes how to set up ground plane rotation upon mouse drag.

#### Product Backlog

https://trello.com/b/3ElQkPlR/softsysviolentviolets
