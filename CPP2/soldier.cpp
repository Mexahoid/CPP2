#include "stdafx.h"
#include "soldier.h"
#include <cstdlib>
#include <ctime>

soldier::soldier(nest *const nest) : ant(nest, nest->get_info(1))
{
	// ������� �� ���� ��� ��� ������� ������
	entity::untap();
}

void soldier::act()
{
	// Zoldaten ����� ����� ������������, ������ �� ��������������� ��� ���
	ant::act();
	if (_health < 1)
		return;
	if (_health <= _max_health - _heal_amount)
		ant::act();
}

int soldier::get_revealing_chance()
{
	srand(time(nullptr));
	return rand() % 101;
}

void soldier::hit_enemy(enemy* enemy) const
{
	enemy->hit(_power);
}

