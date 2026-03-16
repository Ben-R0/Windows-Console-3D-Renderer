#pragma once


struct Vector3 {
	double x;
	double y;
	double z;

	Vector3(double newX, double newY, double newZ);

	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator-(const Vector3& rhs) const;

	Vector3 operator*(const double& s) const;
};

struct Vector2 {
	double x;
	double y;


	Vector2(double newX, double newY);

	Vector2 operator+(const Vector2& rhs) const;

	Vector2 operator*(const double& s) const;	
};

struct Color3 {
	int R;
	int G;
	int B;
};

struct Pixel {
	double depth;
	Color3 color;

	Pixel(double newDepth, Color3 newColor);
};