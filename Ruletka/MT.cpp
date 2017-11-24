//Generator liczb pseudolosowych Mersenne Twister

#include "MT.h"

using namespace std;

// Inicjuje MT[]
//--------------
void InicjujMT(unsigned int x0)
{
	ulong x;

	MT[0] = x0;
	for (int i = 1; i < 623; i++)
	{
		x = MT[i - 1];
		x = (23023 * x) & 0xffffffffull;
		x = (3 * x) & 0xffffffffull;
		MT[i] = (unsigned int)x;
	}
}

// Generator Mersenne Twister
//--------------------------
unsigned int MersenneTwister()
{
	const unsigned int MA[] = { 0,0x9908b0df };
	long int y;
	int i1, i397;

	i1 = mti + 1; if (i1 > 623) i1 = 0;
	i397 = mti + 397; if (i397 > 623) i397 -= 624;
	y = (MT[mti] & 0x80000000) | (MT[i1] & 0x7fffffff);
	MT[mti] = MT[i397] ^ (y >> 1) ^ MA[y & 1];
	y = MT[mti];
	y ^= y >> 11;
	y ^= (y << 7) & 0x9d2c5680;
	y ^= (y << 15) & 0xefc60000;
	y ^= y >> 18;
	mti = i1;
	return y;
}
