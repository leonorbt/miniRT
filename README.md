# miniRT
Doing miniRT with António.

If you are unsure between doing miniRT and cub3d, [this was the video](https://www.khanacademy.org/computing/pixar/rendering/rendering1/v/overview-rendering) that excited me about miniRT because it gave me a real world application of the project.

## Tutorial
Not sure how to tackle this? Well, neither am I, but this is what we have done so far:
- Parsing - after Minishell no need for an explanation here
- See pixar movies on ray tracing, which requires you to revise some concepts:
	- Weighted average (this is what you did in school to compute your grade when projects, exams and behvaiour were worth different ammounts)
	- Line equation (this is just the normal y = ax + b but putting everything to the side)
	- Equation systems (that big { with as many lines as unknown variables)
	- Equation of a plane
- [Law of cosines](https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces/dot-cross-products/v/defining-the-angle-between-vectors?modal=1)
- Dot product of orthogonal vectors = 0. Maybe I can get the "extreme" vector, that is, the one on the most left and right and the plane will be the difference between those 2 vectors 
- Try to build the matrix where the objects will be project. What is this matrix? We have a set of coordinates that tell us where the camera is, we then have a vector that tells us there the camera is directed and the FOV says how wide the lense is. Knowing where we are and where we are looking, we can draw a matrix that will have as many elements as pixels, adjusting the width with the FOV.
	- I think there are infinite planes and the rays will cross them all, but for now I will imagine the plane to be 1 unit away from the camera as this helps me visualize
	- Important note: the rays come from the light and then are reflected/refracted into the camera, but in the drawing phase it seems to be the opposite
- I was having a hard time understanding how to transform 3D coordinates in 2D image plane and [this link helped me a lot](https://www.scratchapixel.com/lessons/3d-basic-rendering/computing-pixel-coordinates-of-3d-point/mathematics-computing-2d-coordinates-of-3d-points)
	- World space to camera space: [word-to-local matrix](https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function), which converts any point from the world coordinate system into a local coordinate system
	- Camera space to canvas (or image plane): perspective projection, that is, dividing the x and y coordinates by the -z coordinate (must be negative, as the z-axis is going into the camera). We can now discard the z coordinate
	- Canvas (or image plane) to NDC (Normalized Device Coordinate): the goal is to normalize the coordinates into [0,1] by summing to the x coordinate half the canvas width (moving the origin from the center to the left) and then dividing by the total width (so the max is 1) and to the y coordinate half the canvas height (moving the origin from the middle to the bottom) and then dividing by the total height (so the max is 1)
	- NDC to raster (pixel space): multiply the normalized x and 1-y coordinates by width and height in pixels and round to integer (it's 1-y because y pixel moves in opposite direction of y axis)

## Window stuff (aka minilibX stuff)
- Close the window with ESC
- Quit cleanly in the red cross
- Use images of minilibX (?)
- Test covering the window and moving it
- Minimize

## Parsing
The first argument of the program should be a scene description file (.rt)
- Each type of element can be separated by one or more line breaks
- Each piece of information from an element can be separated by one or more spaces
- Each type of element can be set in any order in the file
- Elements which are defined by a capital letter can only be declared once in the scene
- The element first's information is the type identifier (one or two chars), followed by specific information for each object

In case of error or misconfiguration, exit properly + return "Error\n" followed by an explicit error message of your choice

## Elements
### Ambient lightning (A)
```A  0.2  255,255,255```

Identifier A

Ratio from 0.0 to 1.0

R,G,B colors, ranging from 0 to 255

### Camera (C)
```C  -50.0,0,20  0,0,1  70```

Identifier C

View point coordinates (x,y,z) --> should we transform this into (0,0,0)? It seems like a valid approach

3d normalized orientation vector for each x,y,z axis, ranging between -1 and 1 --> this gives us the direction where the camera is looking at

fov (horizontal field of view) in degrees, ranging from 0 to 180 --> this gives us the angle of the camera (like fish-eye). If the angle is smaller (closer to 0), we are zooming in. If the angle is bigger (closer to 180), we are zooming out.

- There can be more than one camera, the same image can be viewed from multiple points of view

### Light (L)
```L  -40.0,50.0,0.0  0.6  10,0,255```

Identifier L

Coordinates of the light point (x,y,z)

Brightness ratio from 0.0 to 1.0

Bonus: R,G,B colors, ranging from 0 to 255

- There can be more than one light

### Plane (pl)
```pl  0.0,0.0,-10.0  0.0,1.0,0.0  0,0,225```

Identifier pl

Coordinates (x,y,z)

3d normalized orientation vector for each x,y,z axis, ranging between -1 and 1

R,G,B colors, ranging from 0 to 255

Add the formula and relevant notes


### Sphere (sp)
```sp  0.0,0.0,20.6  12.6  10,0,255```

Identifier sp

Coordinates of the sphere center (x,y,z)

Sphere diameter

R,G,B colors, ranging from 0 to 255

Formula + notes


### Cylinder (cy)
```cy  50.0,0.0,20.6  0.0,0.0,1.0  14.2 21.42  10,0,255```

Identifier cy

Coordinates (x,y,z)

3d normalized orientation vector for each x,y,z axis, ranging between -1 and 1

Cylinder diameter

Cylinder height

R,G,B colors, ranging from 0 to 255

I think the formula is going to make it infinite, we need to truncate it on both sides at a certain height and then add the circles as top and bottom


### Triangle (tr)
Characters are a bunch of 4 sided polygons, which can be split into triangles by drawing an edge that connects diagonal points.


## Resources:
- The holy grail is [Scratch a pixel](https://www.scratchapixel.com/index.php). It is the best documentation for this project, explaining everything behind in several ways and with source code in C++. I'm not sure if it is even possible to do this project without that.
- https://www.notion.so/miniRT-5f6fcdf6d05e4742b6c38f0588f12436
- [Raul's Notion](https://wary-neem-854.notion.site/MiniRT-71995aae3aac48d58aaf75be4c3e9193)
- [Physically Based Rendering](https://pbr-book.org/3ed-2018/contents)
- [Pixar - Rendering 101](https://www.khanacademy.org/computing/pixar/rendering)
- [What is the difference between ray tracing and ray casting?](https://stackoverflow.com/a/67354199)

## Repos
- https://github.com/Knulpinette/42_04_minirt
- https://www.gitdetail.com/repositories/appinha/42cursus-02-miniRT/617200
- https://github.com/appinha/42cursus-02-miniRT
- https://github.com/eljommys/miniRT-for-Linux
- https://github.com/nesvoboda/minirt
- https://github.com/solaldunckel/miniRT
- https://github.com/eljommys/miniRT-for-Linux
- https://github.com/jpceia/42-miniRT
- https://github.com/m4r11/02.miniRT 

### Ray tracing
- [How Ray tracking work?](https://polaron3d.com/Hub/ray-tracing)
- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [Ray Tracing in One Weekend - GitHub Repo](https://github.com/eastriverlee/raytracing)
