#include <vector>
#include <numbers>
#include <cmath>

#include "Functions.h"
#include "Classes.h"
#include "Globals.h"


//Convert a Vector3 from world space to camera space
Vector3 ToCameraSpace(const Vector3& vWorld) {
	Vector3 vCam(vWorld.x, vWorld.y, vWorld.z);
	vCam = RotateV3(vCam, 'z', -gCamera.rotation.z, gCamera.position);
	vCam = RotateV3(vCam, 'y', -gCamera.rotation.y, gCamera.position);
	vCam = RotateV3(vCam,'x', -gCamera.rotation.x, gCamera.position);
	
	return vCam - gCamera.position;
}




//Compute a vector list representing samples number of points between the two points defining an edge
std::vector<Vector3> SampleEdge(const Vector3& vI, const Vector3& vF, const int& samples) {
	std::vector<Vector3> points;
	points.reserve(samples + 1);//samples+1th point is vF

	Vector3 delta = vF - vI;

	for (int i = 0; i <= samples; i++) {
		float a = static_cast<float>(i) / samples;
		Vector3 vWorld = vI + delta * a;
		Vector3 vCam = ToCameraSpace(vWorld);
		if (vCam.z <= gCamera.nearPlane) {//Point behind camera
			continue;
		}
		points.push_back(vCam);
	}

	return points;//camera space points
}


//Projection
Vector2 Project(const Vector3& vCam) {
	/*
	double fovRad = gCamera.fov * 0.5 * (std::numbers::pi / 180.0);
	double scale = 1.0 / std::tan(fovRad);

	Vector2 vNds(
		(vCam.x / vCam.z)*scale*SCREEN_ASPECT,
		(vCam.y / vCam.z)*scale
	);
	*/
	double fovY = gCamera.fov * std::numbers::pi / 180.0;  // vertical FOV in radians
	double fovX = 2.0 * std::atan(std::tan(fovY / 2.0) * SCREEN_ASPECT);

	Vector2 vNds(
		vCam.x / (vCam.z * std::tan(fovX / 2.0)), // horizontal
		vCam.y / (vCam.z * std::tan(fovY / 2.0))  // vertical
	);
	return vNds;
}
/*
returns a point in normalized device space(nds)
nds is like udim2
these values must be clipped to [1,1]
*/


//ToScreen
std::pair<int,int> ToScreen(const Vector2& vNds) {//takes v in normalized device space
	double xScreen = (vNds.x + 1) / 2;
	double yScreen = 1 - (vNds.y + 1) / 2;

	xScreen *= SCREEN_WIDTH;
	yScreen *= SCREEN_HEIGHT;

	int nXScreen = static_cast<int>(xScreen);
	int nYScreen = static_cast<int>(yScreen);

	return std::pair<int,int>(nXScreen, nYScreen);

	/*
	return {
		(p.x + 1.0) * 0.5 * SCREEN_WIDTH,
		(1.0 - (p.y + 1.0) * 0.5) * SCREEN_HEIGHT
	};
	*/
}




//Compute a line between two Vector3 points, returning a list of points at which to create pixels
std::vector<Vector3> DrawLine(const Vector3& vI, const Vector3& vF) {
	std::vector<Vector3> line = {};

	Vector3 dirVector = vF - vI;

	


	return line;
}

//returns a pair of verts (lhs) and edges (rhs)... this implementation could be better id assume
std::pair<std::vector<Vector3>, std::vector<std::pair<int, int>>> buildSphere(int radialSamples, int rings) {//actually makes rings+1
	std::vector<Vector3> verts;
	std::vector<std::pair<int, int>> edges;

	//height of sphere will range from -1 to 1
	for (int i = 0; i <= rings; i++) {
		double y = -1.0 + 2.0 * (static_cast<double>(i) / rings);
		double radius = sqrt(1.0 - y * y);
		
		for (int j = 0; j <= radialSamples; j++) {
			double theta = (static_cast<double>(j) / radialSamples) * (2 * pi);//% times 2pi
			double x = radius * cos(theta);
			double z = radius * sin(theta);
			
			verts.push_back({x,y,z});

			int currentIndex = i * (radialSamples + 1) + j;

			//horizontal edges
			if (j > 0) {
				std::pair<int, int> edge = { currentIndex - 1, currentIndex };
				edges.push_back(edge);
			}
			else {
				std::pair<int, int> edge = { currentIndex, currentIndex + 1 };
				edges.push_back(edge);
			}

			//vertical edges
			if (i > 0) {
				int prev = (i - 1) * (radialSamples + 1) + j;
				std::pair<int, int> edge = { prev, currentIndex};
				edges.push_back(edge);
			}
		}
	}

	return std::pair<std::vector<Vector3>, std::vector<std::pair<int, int>>> {verts, edges};
}