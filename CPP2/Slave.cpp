#include "stdafx.h"
#include "slave.h"
#include <string>

slave::slave(nest *const nest) : ant(nest, nest->get_info(3))
{

}

void slave::act()
{
	if (!_tapped)
	{
		ant::act();
		_nest->add_resources(_power);
		if (SLAVE_ADDING_INFO)
		{
			_messenger("---------------------", true);
			_messenger("Slave added ", false);
			_messenger(std::to_string(_power).c_str(), false);
			_messenger(" food.", true);
			_messenger("---------------------", true);
		}
		tap();
		if (STARVATION_DEATH_INFO)
			if (_health < 1)
			{
				_messenger("---------------------", true);
				_messenger("Slave died due to starvation.", true);
				_messenger("---------------------", true);
			}
	}
}