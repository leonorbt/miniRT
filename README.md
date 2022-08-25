# miniRT
Doing miniRT with António.

If you are unsure between doing miniRT and cub3d, [this was the video](https://www.khanacademy.org/computing/pixar/rendering/rendering1/v/overview-rendering) that excited me about miniRT because it gave me a real world application of the project.

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

- There can't be more than 1 ambient light as they don't even have positioning, right?

### Camera (C)
```C  -50.0,0,20  0,0,1  70```

Identifier C

View point coordinates (x,y,z) --> should we transform this into (0,0,0)? It seems like a valid approach

3d normalized orientation vector for each x,y,z axis, ranging between -1 and 1

fov (horizontal field of view) in degrees, ranging from 0 to 180

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
- https://www.notion.so/miniRT-5f6fcdf6d05e4742b6c38f0588f12436
- [Raul's Notion](https://wary-neem-854.notion.site/MiniRT-71995aae3aac48d58aaf75be4c3e9193)
- [Physically Based Rendering](https://pbr-book.org/3ed-2018/contents)
- [Pixar - Rendering 101](https://www.khanacademy.org/computing/pixar/rendering)

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
