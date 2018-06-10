#pragma once
#include <stdlib.h>
#include <math.h>
#include "GLOBALSETTINGS.h"
using namespace std;

struct _2D{
	_2D(double x,double y) :x(x), y(y) {};
	double x;
	double y;
};

struct _3D {

	_3D():x(0),y(0),z(0) {};
	_3D(double x, double y, double z) :x(x), y(y), z(z) {}
	_3D(const _2D& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = 0;
	}

	double x;
	double y;
	double z;

	inline _2D to_2D() {
		return _2D(x,y);
	}
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
	if (rhs.x < -EPSILON ||rhs.x > MAP_INTERVALS + EPSILON ||
		rhs.y < -EPSILON || rhs.y > MAP_INTERVALS + EPSILON) {
		return true;
	}
	return false;
}

inline double Distance_2D(_2D const & lhs, _2D const & rhs) {
	double x = fabs(lhs.x - rhs.x);
	double y = fabs(lhs.y - rhs.y);
	return pow(x*x + y*y, 0.5);
}

inline bool OutOfRange_3D(_3D const & rhs) {
	if (
		rhs.x < -EPSILON || rhs.x > MAP_INTERVALS+EPSILON ||
		rhs.y < -EPSILON || rhs.y > MAP_INTERVALS+EPSILON || 
		rhs.z < -MAP_INTERVALS-EPSILON || rhs.z > MAP_INTERVALS+EPSILON
		) {
		return true;
	}
	return false;
}

inline double Distance_3D(_3D const & lhs, _3D const & rhs) {
	double x = fabs(lhs.x - rhs.x);
	double y = fabs(lhs.y - rhs.y);
	double z = fabs(lhs.z - rhs.z);
	return pow(x*x + y*y + z*z, 0.5);
}