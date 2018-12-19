#include <list>
#include "Army.cpp"
#ifdef APPLE
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif
#define ARMY_MAX_SIZE 25;
#define MAX_NUM_ARMIES 20000;

class ArmyManagerSingleton {
private:
	ArmyManagerSingleton() {
		int limit = MAX_NUM_ARMIES;
		for (int i = 0; i < limit; i++) {
			free_indices.push_back(i);
		}
	}
	std::list<int> used_indices;
	std::list<int> free_indices;
	static ArmyManagerSingleton* instance;
public:
	ArmyManagerSingleton* get_instance() {
		if (instance == nullptr) {
			instance = new ArmyManagerSingleton();
		}
		return instance;
	}
	Army* get_army(int index) {
		return nullptr;
	}
};