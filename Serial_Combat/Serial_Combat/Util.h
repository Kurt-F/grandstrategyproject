#pragma once
// Unit attribute constants
#define STRENGTH 0 
#define MORALE 1 
#define SPEED 2 // Measured in mph
#define ARMOUR 3
#define AP 4
#define TACTICS 5 // 0-1
#define EXPERIENCE 6
#define INITIATIVE 7 // Affects how many attacks are made per tick. Unimplemented. Must be < 0.5.
#define ATTACK 8
#define DEFENSE 9
#define MAX_STR 10
#define COUNTERMSRS 11 // Countermeasures like anti-air missiles, active camoflage etc. Unimplemented.
#define UNIT_ATTR_COUNT 12 // Should always be 1 + highest attribute int used. 
// Army constants
#define MAX_NUM_ARMIES 20000
#define MAX_UNITS_IN_ARMY 25
// Unit flags
// To check if a SINGLE bit flag is set, use bitwise AND and check if > 0
// For example: (flags & UNIT_FLAG_MASK) > 0
// To set a flag, OR the flag variable with the desired flag
// For example: flags = flags | UNIT_FLAG_MASK;
// Flags are implemented as unsigned chars(byte) so always >= 0
#define UNIT_DEAD 0x01 // Assigned to first bit
#define UNIT_RETREAT 0x02 // Assigned to second bit
#define UNIT_HALTED 0x04 // Assigned to third bit
