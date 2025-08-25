#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string>

struct Students
{
	std::string name;
	std::string surname;
	std::string patronymic;
	int32_t group{};
	int32_t id{};
	int32_t mark_ma{};
	int32_t mark_geo{};
	int32_t mark_proga{};
};
#endif