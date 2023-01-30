#include "smath.h"

smath::random::random(debug* msg)
{
	srand(time(0));
	this->msg = msg;
}

int smath::random::randomInt(int radius)
{
	return (rand() % radius) + 1; 
}