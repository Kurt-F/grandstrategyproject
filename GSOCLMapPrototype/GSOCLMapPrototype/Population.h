#pragma once
// Culture constants
#define CUL_ENGLISH 0
#define CUL_FRENCH 1
// Religious constants
#define REL_CATHOLIC 0
#define REL_PROTESTANT 1
// Economic constants (this should be moved elsewhere in the future probably)
#define ECON_GRAIN 0
#define ECON_FRUIT 1
#define ECON_MEAT 2
#define ECON_IRON 3
#define ECON_COAL 4
// Job constants
#define LABORER 0
#define TECHNICIAN 1
// Political constants
#define POL_CONSERVATIVE 0
#define POL_LIBERAL 1
class Population
{
private:
	int size; // Number of people in this population
	unsigned char flags; // Reserved for later
	unsigned char culture; // See above constants
	unsigned char profession;
	unsigned char religion;
	unsigned char ideology;
	float* needs; // The index of each value corresponds to its type, see above constants
	float birth_rate; // Average number of children born per woman per period 
public:
	Population(
		int s,
		unsigned char f,
		unsigned char c,
		unsigned char p,
		unsigned char r,
		unsigned char i,
		float* ns,
		float b
	);
	~Population();
};

