#include <iostream>
#include "Classes.h"
#include "Math.h"

Vector3 RotateV3(Vector3 v, char axis, double angle, Vector3 p) {//p=pivot point
	Vector3 offsetV = v - p;

	Vec4 v4;
	v4(0, 0) = offsetV.x;
	v4(1, 0) = offsetV.y;
	v4(2, 0) = offsetV.z;
	v4(3, 0) = 1.0;

	Vec4 r4;

	if (axis == 'x') {
		r4 = xRotation(angle) * v4;
	}
	else if (axis == 'y') {
		r4 = yRotation(angle) * v4;
	}
	else {//hopefully (axis == 'z')
		r4 = zRotation(angle) * v4;
	}
	Vector3 offsetR3(r4(0, 0), r4(1, 0), r4(2, 0));

	Vector3 r3 = offsetR3 + p;

	return r3;
};