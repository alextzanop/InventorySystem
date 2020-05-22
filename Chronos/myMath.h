#pragma once

//some math functions used in the rest of the project
class myMath
{

public:
	//euler distance
	static double myEucDist(int x0, int y0, int x1, int y1);

	//power function (base^exp)
	static double myPower(int base, int exp);

	//square root
	static double mySqrt(int base);

};

