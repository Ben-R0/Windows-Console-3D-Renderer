#pragma once
#include <cmath>
constexpr double pi = 3.14159265358979323846;

template <int R, int C>
struct Matrix {
	double m[R][C];

	Matrix() {
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				m[r][c] = 0.0;
			}
		}
	};

	Matrix operator+(const Matrix& rhs) {
		Matrix sum(R,C);
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				sum(r, c) = m[r][c] + rhs[r][c];
			}
		}
		return sum;
	}

	template <int K>
	Matrix<R,K> operator*(const Matrix<C, K>& rhs) {
		Matrix<R, K> product;
		for (int r = 0; r < R; r++) {
			for (int k = 0; k < K; k++) {
				product(r, k) = 0.0;
				for (int c = 0; c < C; c++) {
					product(r, k) += m[r][c] * rhs(c,k);
				}
			}
		}

		return product;
	}

	Matrix operator*(const double& rhs) {
		Matrix product(R,C);
		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				product(r, c) = m[r][c] * rhs;
			}
		}

		return product;
	}

	// operator() for getting values at r,c
	double& operator()(int r, int c) {
		return m[r][c];
	}

	//somehow splitting this from the other 1 above fixes the * operator
	const double& operator()(int r, int c) const{
		return m[r][c];
	}
};



//type aliases for simple matrices of given dimensions
using Mat4 = Matrix<4, 4>;
using Vec4 = Matrix<4, 1>;
using Vec3 = Matrix<3, 1>;

static Matrix<4, 4> xRotation(double theta) {
	Mat4 rX;
	double c = cos(theta);
	double s = sin(theta);

	rX(0, 0) = 1.0;
	rX(1, 1) = c;
	rX(1, 2) = -s;
	rX(2, 1) = s;
	rX(2, 2) = c;
	rX(3, 3) = 1.0;

	return rX;
};

static Matrix<4, 4> yRotation(double theta) {
	Mat4 rX;
	double c = cos(theta);
	double s = sin(theta);

	rX(0, 0) = c;
	rX(0, 2) = s;
	rX(1, 1) = 1.0;
	rX(2, 0) = -s;
	rX(2, 2) = c;
	rX(3, 3) = 1.0;

	return rX;
};

static Matrix<4, 4> zRotation(double theta) {
	Mat4 rX;
	double c = cos(theta);
	double s = sin(theta);

	rX(0, 0) = c;
	rX(0, 1) = -s;
	rX(1, 0) = s;
	rX(1, 1) = c;
	rX(2, 2) = 1.0;
	rX(3, 3) = 1.0;

	return rX;
};

//has to be defined in math.cpp for some reason
Vector3 RotateV3(Vector3 v, char axis, double angle, Vector3 p = Vector3(0.0,0.0,0.0));