#include "Army.h"

	Army::Army(Unit* u, int s, int m) {
		this->units = u;
		this->size = s;
		this->max_size = m;
	}
	Army::~Army() {
		for (int i = 0; i < this->size; i++) {
			delete(&this->units[i]);
		}
		delete(this->units);
	}
	Unit* Army::GetUnits() {
		return this->units;
	}
	void Army::SetUnits(Unit* u) {
		this->units = u;
	}

	int Army::GetMaxSize()
	{
		return max_size;
	}
