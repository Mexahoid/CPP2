// CPP2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "nest.h"
#include <iostream>
#include <windows.h>
#include "world.h"


int main()
{

	starting_numbers st = starting_numbers{
		50000,
		40000, 
		12, 5, 12, 5
	};

	starting_numbers st2 = starting_numbers{
		50000,
		4000,
		14, 8, 2, 5
	};
	//nest *n = new nest(st);

	world *n = new world(st);

	while(n->pass_day())
	{
		Sleep(1000);
	}
	std::cout << "Long live the Queen!" << std::endl;
	delete n;
	char x;
	std::cout << "Press any key to continue";
	std::cin >> x;
	return 0;
}

