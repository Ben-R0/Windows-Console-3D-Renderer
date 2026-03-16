#pragma once
#include "Classes.h"
#include "Math.h"


struct Camera {
	Vector3 position;
	Vector3 rotation; // pitch, yaw, roll
	double fov;
	double nearPlane;
	double farPlane;
};

extern Camera gCamera;

extern const double SCREEN_WIDTH;
extern const double SCREEN_HEIGHT;
extern const int nSCREEN_WIDTH;
extern const int nSCREEN_HEIGHT;


extern const double SCREEN_ASPECT;