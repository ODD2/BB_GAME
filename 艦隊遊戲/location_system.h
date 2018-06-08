#pragma once
#include <stdlib.h>
#include <math.h>
#include "GLOBALSETTINGS.h"
using namespace std;

struct s_2D{
	double x;
	double y;
};

struct s_3D {
	double x=0;
	double y=0;
	double z=0;
};

typedef struct s_2D _2D;
typedef struct s_3D _3D;

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