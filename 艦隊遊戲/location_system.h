#pragma once
#include <math.h>
#include "GLOBALSETTINGS.h"

typedef struct {
	double x;
	double y;

	bool operator==(const _2D& location) {
		if (
			fabs(x - location.x) < EPSILON
			&&
			fabs(y - location.y) < EPSILON
			)
			return true;
		else
			return false;
	}
}_2D;

typedef struct {
	double x=0;
	double y=0;
	double z=0;

	bool operator==(const _3D& location) {
		if (
			fabs(x - location.x) < EPSILON
			&&
			fabs(y - location.y) < EPSILON
			&&
			fabs(z - location.z) < EPSILON
			)
			return true;
		else
			return false;
	}
}_3D;