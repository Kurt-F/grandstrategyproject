#include "pch.h"
#include "Population.h"

Population::Population(int s, unsigned char f, unsigned char c, unsigned char p, unsigned char r, unsigned char i, float * ns, float b)
{
	size = s;
	flags = f;
	culture = c;
	profession = p;
	religion = r;
	ideology = i;
	needs = ns; // TODO: Clone array
	birth_rate = b;
}

Population::~Population()
{
}

