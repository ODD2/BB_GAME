#pragma once
#include <stdlib.h>
#include <math.h>
#include "GLOBALSETTINGS.h"
using namespace std;

struct _2D{
	double x;
	double y;
};

struct _3D {

	_3D() {};
	_3D(const _2D& rhs) {
		x = rhs.x;
		y = rhs.y;
	}

	double x;
	double y;
	double z;
};


inline bool operator==(_2D const &  rhs, _2D const & lhs) {
	if (fabs(rhs.x - lhs.x) < EPSILON
		&&
		fabs(lhs.y - rhs.y) < EPSILON
		)
		return true;
	else
		return false;
}

inline bool operator==(_3D const & lhs, _3D const & rhs) {
	if (
		fabs(lhs.x - rhs.x) < EPSILON
		&&
		fabs(lhs.y - rhs.y) < EPSILON
		&&
		fabs(lhs.z - rhs.z) < EPSILON
		)
		return true;
	else
		return false;
}

inline bool OutOfRange_2D(_2D const & rhs) {
	if (rhs.x < 0 ||rhs.x > MAP_INTERVALS || rhs.y < 0 || rhs.y > MAP_INTERVALS) {
		return true;
	}
	return false;
}

inline double Distance_2D(_2D const & lhs, _2D const & rhs) {
	double x = fabs(lhs.x - rhs.x);
	double y = fabs(lhs.y - rhs.x);
	return pow(x*x + y*y, 0.5);
}

inline bool OutOfRange_3D(_3D const & rhs) {
	if (rhs.x < 0 || rhs.x > MAP_INTERVALS || rhs.y < 0 || rhs.y > MAP_INTERVALS || rhs.z < 0 || rhs.z > MAP_INTERVALS) {
		return true;
	}
	return false;
}

inline double Distance_3D(_3D const & lhs, _3D const & rhs) {
	double x = fabs(lhs.x - rhs.x);
	double y = fabs(lhs.y - rhs.x);
	double z = fabs(lhs.z - rhs.z);
	return pow(x*x + y*y + z*z, 0.5);
}