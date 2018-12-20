#ifndef  ARMY
#define ARMY


#define ATTR_HP 0;
#define ATTR_STR 1;
#define ATTR_OFF 2;
#define ATTR_DEF 3;
#include "Unit.cpp"

class Army {
private:
	Unit* units;
	int size;
	int max_size;
public:

	Army(Unit* u, int s, int m) {
		this->units = u;
		this->size = s;
		this->max_size = m;
	}
	~Army() {
		for (int i = 0; i < this->size; i++) {
			delete(&this->units[i]);
		}
		delete(this->units);
	}
	Unit* GetUnits() {
		return this->units;
	}
	void SetUnits(Unit* u) {
		this->units = u;
	}

	int GetMaxSize()
	{
		return max_size;
	}
};
#endif // ! ARMY