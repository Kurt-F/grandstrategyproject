#ifndef  ARMY
#define ARMY


#define ATTR_HP 0;
#define ATTR_STR 1;
#define ATTR_OFF 2;
#define ATTR_DEF 3;
#include "Unit.h"

class Army {
private:
	Unit* units;
	int size;
	int max_size;
public:
	Army(Unit* u, int s, int m);
	~Army();
	Unit* GetUnits();
	void SetUnits(Unit* u);
	int GetMaxSize();
};
#endif // ! ARMY