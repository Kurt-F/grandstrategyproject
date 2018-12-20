#include "ArmyManagerSingleton.cpp"

int main()
{
	ArmyManagerSingleton *arm = ArmyManagerSingleton::get_army();
	return 0;
}