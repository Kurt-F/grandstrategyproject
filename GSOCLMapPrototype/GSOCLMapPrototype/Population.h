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

#define NUM_POP_ATTRIBUTES 6
struct Population
{
	// ATTRIBUTES 
	int size; // Number of people in this population
	unsigned char flags; // Reserved for later
	unsigned char culture; // See above constants
	unsigned char profession;
	unsigned char religion;
	unsigned char ideology;
	float birth_rate; // Average number of children born per woman per period 
	// END ATTRIBUTES
	// Population needs
	float* needs; // The index of each value corresponds to its type, see above constants
	// Change "queue"
	int num_changes;
	float* changes; // array with same number of elements as pop has attributes. 
};

