#pragma once
#include <vector>

#include "Classes.h"

Vector3 ToCameraSpace(const Vector3& vWorld);

std::vector<Vector3> SampleEdge(const Vector3& vI, const Vector3& vF, const int& samples);

Vector2 Project(const Vector3& v);

std::vector<Vector3> DrawLine(const Vector3& vI, const Vector3& vF);

std::pair<int, int> ToScreen(const Vector2& vNds);