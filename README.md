# 3D Windows Console Renderer

A 3D renderer using Windows handles to draw a wide character on the console screen and visualize objects. 

___________________________________________________________________________________________________


## 📦 Technologies

* C++


___________________________________________________________________________________________________


## 🌌 Features

* 3D rendering of an object depicting its edges and verticies.
* Full support for object and camera rotation.
* Camera manipulation using keyboard shortcuts.


___________________________________________________________________________________________________


## 🎹 Keyboard Shortcuts

* W: Throttle Up
* S: Throttle Down
* A: Rotate Camera Left
* D: Rotate Camera Right
* Q: Zoom In (FOV Down)
* E: Zoom Out (FOV Up)
* H: Full Stop (Throttle = 0)


___________________________________________________________________________________________________


## 👨‍🍳 The Process

I started by studying existing projects on console rendering, and found a 3D console game engine which used a Windows handle to write a wide character type across the whole screen for visualization of a scene.
Working from this, I applied what I remember from multivariable calculus to create a basic rendering pipeline to depict a single scene of a fixed object given a fixed camera.
I started with just visualizing its verticies using a vector of position data, and then created a new vector storing pairs of these vertices to visualize edges.

Here's one of the early renders right after I nailed down edge visualization:

<img width="467" height="240" alt="image" src="https://github.com/user-attachments/assets/6709b23e-6040-4022-8647-e0d5160b5246" />


I then did some research into linear algebra concepts to develop a matrix struct with a variety of operator overloads to create an easier pipeline leading into rotation.
After applying these principles and creating static factories for the rotation matrices, I was able to produce a rotation system for both the object and the camera.

![Rotating Cube](https://github.com/user-attachments/assets/d61c7deb-397e-4876-80cc-9d9582c11215)


___________________________________________________________________________________________________



## 🎯 Future Goals

At the project's onset, I used the the parametretic equation for a 3D line to quickly develop an intuitive line drawing method, but the Bresenham algorithm would be a more efficient replacement.

In the longer term, shading of 3D faces or direct reading from .obj files would strengthen the project's scope.
