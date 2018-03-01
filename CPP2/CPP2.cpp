// CPP2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "nest.h"


typedef struct {
	int FoodCreated;
	int FoodConsumed;
	int FoodCurrent;

	int EnemiesCurrent;

	int SoldierCount;
	int OverseerCount;
	int SlaveCount;
	int LarvaCount;

} DataForDay;


int main()
{
	nest *n = new nest(5000);

	delete n;
	return 0;
}

