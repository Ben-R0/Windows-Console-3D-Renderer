#include "Globals.h"

//Vector3
Vector3::Vector3(double newX, double newY, double newZ):x(newX), y(newY), z(newZ){}//Constructor

Vector3 Vector3::operator+(const Vector3& rhs) const{//Addition
	return { x + rhs.x, y + rhs.y, z + rhs.z };
}

Vector3 Vector3::operator-(const Vector3& rhs) const {//Subtraction
	return { x - rhs.x, y - rhs.y, z - rhs.z };
}

Vector3 Vector3::operator*(const double& s) const {//Scalar Multiplication
	return { x * s,y * s,z * s };
}


//Vector2
Vector2::Vector2(double newX, double newY):x(newX), y(newY){}//Constructor

Vector2 Vector2::operator+(const Vector2& rhs) const {//Addition
			return { x + rhs.x, y + rhs.y };
		}

Vector2 Vector2::operator*(const double& s) const {//Scalar Multiplication
	return { x * s, y * s };
}


//We don't store positions for pixels in the struct because pixels are stored in a buffer where buffer[x][y]=pixel at that location
//We store depth in order to determine which pixel should be infront
//If the pixel infront is transparent, we blend the colors of visible pixels in the screen position
Pixel::Pixel(double newDepth, Color3 newColor):depth(newDepth), color(newColor) {};

