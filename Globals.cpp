#include "Globals.h"
#include "Math.h"

Camera gCamera = { Vector3(0,0,-5.0), Vector3(0.0,0.0,0.0), 90.0, 0.0, 1000.0 };

const double SCREEN_WIDTH = 120.0;//120.0;
const double SCREEN_HEIGHT = 40.0;//40.0;
const int nSCREEN_WIDTH = static_cast<int>(SCREEN_WIDTH);
const int nSCREEN_HEIGHT = static_cast<int>(SCREEN_HEIGHT);


const double SCREEN_ASPECT = SCREEN_WIDTH / SCREEN_HEIGHT;