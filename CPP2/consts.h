#pragma once

const int QUEEN_HEALTH = 1000;
const int QUEEN_HUNGER = QUEEN_HEALTH / 5 * 2;
const int QUEEN_POWER = QUEEN_HEALTH / 100;
const int QUEEN_HEAL = QUEEN_HEALTH / 10;
const int QUEEN_DAMAGE = 4;

const int SOLDIER_HEALTH = 500;
const int SOLDIER_HUNGER = SOLDIER_HEALTH / 5;
const int SOLDIER_DAMAGE = SOLDIER_HEALTH / 100 * 5;
const int SOLDIER_HEAL = SOLDIER_HEALTH / 5;

const int OVERSEER_HEALTH = 100;
const int OVERSEER_HUNGER = OVERSEER_HEALTH / 2;
const int OVERSEER_POWER = OVERSEER_HEALTH / 100 * 4;
const int OVERSEER_HEAL = OVERSEER_HEALTH / 4;
const int OVERSEER_DAMAGE = OVERSEER_HEALTH / 10;

const int SLAVE_HEALTH = 50;
const int SLAVE_HUNGER = SLAVE_HEALTH / 5 * 2;
const int SLAVE_POWER = SLAVE_HEALTH * 2;
const int SLAVE_HEAL = SLAVE_HEALTH / 10;
const int SLAVE_DAMAGE = SLAVE_HEALTH / 10;

const int LARVA_HEALTH = 5;
const int LARVA_HUNGER = LARVA_HEALTH * 2;
const int LARVA_TIME = LARVA_HEALTH * 2;
const int LARVA_HEAL = LARVA_HEALTH / 5;
const int LARVA_DAMAGE = 1;

const int ENEMIES_INCOME_COUNT_MAX = 20;
const int ENEMIES_HEALTH_MAX = 20;
const int ENEMIES_POWER_MAX = 35;
const int ENEMIES_HUNGER = 20;

const int SOLDIER_MULT = 10;
const int OVERSEER_MULT = 30;
const int SLAVE_MULT = 3;




const bool SLAVE_ADDING_INFO = false;
const bool ENEMY_STEALING_INFO = false;
const bool QUEEN_SPAWNING_INFO = false;
const bool STARVATION_DEATH_INFO = true;
const bool LARVA_ASK_TO_QUEEN_INFO = false;

const bool FIGHT_INFO = true;

const bool SLAVE_FIGHT_INFO = true;
const bool SOLDIER_HIT_INFO = true;
const bool OVERSEER_HIT_INFO = true;
const bool QUEEN_HIT_INFO = true;
const bool LARVA_HIT_INFO = true;
const bool ENEMY_HIT_INFO = true;
const bool TWOHEADED_FIGHT_INFO = true;