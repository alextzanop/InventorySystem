#include "myMath.h"
#include <iostream>
#include <cmath>

//euler distance
double myMath::myEucDist(int x0, int y0, int x1, int y1) {
	return mySqrt(myPower(x0 - x1, 2) + myPower(y0 - y1, 2));
}

//power(base^exp)
double myMath::myPower(int base, int exp) {
	int p = 1;
	for (int i = 0; i < exp; i++) {
		p *= base;
	}
	return p;
}

//square root
double myMath::mySqrt(int base) {
	return std::sqrt(base);
}
