# 3D Windows Console Renderer

A 3D renderer using Windows handles to draw a wide character on the console screen and visualize objects. 

## 📦 Technologies

* C++
<br>

## 🌌 Features

* 3D rendering of an object's wireframe depicting its edges and verticies.
* 3 different object types with customizable parameters.
* Full support for object and camera rotation.
* Camera manipulation using keyboard shortcuts.

  
<br>

## 🎹 Keyboard Shortcuts

* W: Throttle Up
* S: Throttle Down
* A: Rotate Camera Left
* D: Rotate Camera Right
* Q: Zoom In (FOV Down)
* E: Zoom Out (FOV Up)
* H: Full Stop (Throttle = 0)
<br>

## 👨‍🍳 The Process

I started by studying existing projects on console rendering, and found a 3D console game engine which used a Windows handle to write a wide character type across the whole screen for visualization of a scene.
Working from this, I applied what I remember from multivariable calculus to create a basic rendering pipeline to depict a single scene of a fixed object given a fixed camera.
I started with just visualizing its verticies using a vector of position data, and then created a new vector storing pairs of these vertices to visualize edges.

Here's one of the early renders right after I nailed down edge visualization:

<br>

<img width="467" height="240" alt="image" src="https://github.com/user-attachments/assets/6709b23e-6040-4022-8647-e0d5160b5246" />

*Early Edge Visualization*

<br>

I then did some research into linear algebra concepts to develop a matrix struct with a variety of operator overloads to create an easier pipeline leading into rotation.
After applying these principles and creating static factories for the rotation matrices, I was able to produce a rotation system for both the object and the camera. Here's a demonstration of the rotation system for a cube:

<br>

![Rotating Cube](https://github.com/user-attachments/assets/d61c7deb-397e-4876-80cc-9d9582c11215)

*Matrix Rotation Early Application*

<br>

Next, I implemented a shape selection menu for a cube, pyramid, and sphere shape. I gave all shapes the ability to be scaled based on user input before drawing, moved model coordinates to local space before drawing, and added radial samples and rings customization options for the sphere type.

<br>

<img width="639" height="289" alt="image" src="https://github.com/user-attachments/assets/7574b655-9f15-4212-89ed-a7869992faa2" />

*Customization Menu*

<br>

<img width="475" height="470" alt="image" src="https://github.com/user-attachments/assets/6a00fad5-5708-4612-954f-4ed7541cedc3" />

*Example Sphere Render: 7 Radial Samples, 7 Rings, Scaled by 4x* 

<br>

## 🎯 Future Goals

At the project's onset, I used the the parametretic equation for a 3D line to quickly develop an intuitive line drawing method, but the Bresenham algorithm would be a more efficient replacement. I opted to currently disclude some features like faces due to the nature of the rendering environment (these don't always look great in the console), but it could be worth implementing these features to experience the associated technical challenged.

In the longer term, reading image files to shade 3D faces or direct reading from .obj files would definitely strengthen the project's scope. Right now, the project can visualize any object defined in the Main.cpp vertices and edges vectors, but this can be fairly difficult to modify. I was considering a .json file loading system as well that would give me more control over the file format.

Currently, I'm focusing on learning OpenGL to create a more robust and complete renderer using CMake. I'm hoping to create some interesting projects with this in the near future.
