#include "Unit.h"

	Unit::Unit(float* a, int s) {
		this->attributes = a;
		this->num_attr = s;
	}
	Unit::~Unit() {
		delete(attributes);
	}
	float* Unit::GetAttributes() {
		return attributes;
	}
	void Unit::SetAttributes(float* a) {
		this->attributes = a;
	}

	int Unit::GetSize()
	{
		return num_attr;
	}