// CPP2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "nest.h"
#include <iostream>
#include <windows.h>


int main()
{
	starting_numbers st = starting_numbers{
		50000,
		40000, 
		12, 5, 12, 5
	};
	nest *n = new nest(st);

	while(n->pass_day())
	{
		Sleep(100);
	}
	std::cout << "Long live the Queen!" << std::endl;
	delete n;
	char x;
	std::cout << "Press Enter to continue";
	std::cin >> x;
	return 0;
}

