#include <iostream>
#include <iomanip>// Required for fixed and setprecision
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>

#include "Classes.h"
#include "Functions.h"
#include "Windows.h"
#include "Globals.h"
#include "Math.h"

std::vector<Vector3> cube = {
  {-1, -0.5,  1},
  { 1, -0.5,  1},
  { 1,  1.5,  1},
  {-1,  1.5,  1},
  {-1, -0.5,  3},
  { 1, -0.5,  3},
  { 1,  1.5,  3},
  {-1,  1.5,  3},
};

std::vector<std::pair<int, int>> edges = {
    {0,1},{1,2},{2,3},{3,0},  // bottom face
    {4,5},{5,6},{6,7},{7,4},  // top face
    {0,4},{1,5},{2,6},{3,7}   // vertical edges connecting top & bottom
};

double throttle = 0.0;


wchar_t* screen = new wchar_t[nSCREEN_WIDTH * nSCREEN_HEIGHT];//wide char type
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
DWORD dwBytesWritten = 0;


void Draw3D() {
    std::vector<Pixel> yBuffer(nSCREEN_HEIGHT, Pixel(1000.0, Color3(0, 0, 0)));
    std::vector<std::vector<Pixel>> xBuffer(nSCREEN_WIDTH, yBuffer);

    SetConsoleActiveScreenBuffer(hConsole);

    for (int i = 0; i < nSCREEN_WIDTH * nSCREEN_HEIGHT; i++) {
        screen[i] = L' '; // fill with spaces
    }
    
    for (int i = 0; i < edges.size(); i++) {
       
        Vector3 vI = cube[edges[i].first];
        Vector3 vF = cube[edges[i].second];
        
        std::vector<Vector3> points = SampleEdge(vI, vF, 100);//points in world space
        //we need to take depth at each point before projecting it because projection loses depth

        for (int i = 0; i<points.size(); i++) {
            Pixel p(points[i].z, Color3(255, 255, 255));

            Vector2 vNds = Project(points[i]);
            
            if (vNds.x > 1 || vNds.y > 1 || vNds.x < -1 || vNds.y < -1) {
                //std::cout << std::to_string(vNds.x) << " " << std::to_string(vNds.y) << std::endl;
                continue; 
                
            }
            else {

                std::pair<int, int> screenSpace = ToScreen(vNds);
                int x = screenSpace.first;
                int y = screenSpace.second;

                xBuffer[x][y] = p;
                
                
            }
        }
    }
    
    for (int x = 0; x < xBuffer.size(); x++) {//Loops through columns
        for (int y = 0; y < yBuffer.size(); y++) {//Loops through rows

            Pixel p = xBuffer[x][y];

            int nScreenIndex = static_cast<int>(y * static_cast<float>(nSCREEN_WIDTH) + x);

            if (x >= 0 && x < nSCREEN_WIDTH &&
                y >= 0 && y < nSCREEN_HEIGHT &&
                p.depth<900.0)
            {
                int nScreenIndex = y * nSCREEN_WIDTH + x;
                screen[nScreenIndex] = 0x2022;
            }
        }
    }

    screen[nSCREEN_WIDTH * nSCREEN_HEIGHT - 1] = '\0';
    WriteConsoleOutputCharacter(hConsole, screen, nSCREEN_WIDTH * nSCREEN_HEIGHT, { 0,0 }, &dwBytesWritten);
}

void HandleInput() {
    if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
        gCamera.rotation = gCamera.rotation-Vector3(0.0,0.1,0.0);
    }

    if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
        gCamera.rotation = gCamera.rotation + Vector3(0.0, 0.1, 0.0);
    }

    if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
        gCamera.rotation = gCamera.rotation - Vector3(0.1, 0.0, 0.0);
    }

    if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
        gCamera.rotation = gCamera.rotation + Vector3(0.1, 0.0, 0.0);
    }

    if (GetAsyncKeyState((unsigned short)'Q') & 0x8000) {
        gCamera.fov -= 5.0;
    }

    if (GetAsyncKeyState((unsigned short)'E') & 0x8000) {
        gCamera.fov += 5.0;
    }

    if (GetAsyncKeyState((unsigned short)'H') & 0x8000) {
        throttle = 0;
    }

    if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
        throttle += 0.05;
    }

    if (GetAsyncKeyState(VK_LCONTROL) & 0x8000) {
        throttle -= 0.05;
    }

    double camRight = cos(gCamera.rotation.x) * sin(gCamera.rotation.y);
    double camUp = sin(gCamera.rotation.x);
    double camForward = cos(gCamera.rotation.x) * cos(gCamera.rotation.y);

    Vector3 moveVector = (Vector3(throttle*camRight,-throttle*camUp,throttle*camForward));

    gCamera.position = gCamera.position + moveVector;
}

int main()
{
    while (true)
    {   
        HandleInput();
        Draw3D();
        for (int i = 0; i < cube.size(); i++) {
            Vector3 v = cube[i];
            cube[i] = RotateV3(v, 'x', 0.1, Vector3(0, 0.5, 2));
            v = cube[i];
            cube[i] = RotateV3(v, 'z', -0.05, Vector3(0, 0.5, 2));
        }
        std::chrono::milliseconds delay = std::chrono::milliseconds(100);
        std::this_thread::sleep_for(delay);
    }

	return 0;
}