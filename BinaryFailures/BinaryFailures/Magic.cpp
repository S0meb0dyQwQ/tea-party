#include "Base.h"

int32_t CountPeople(std::ifstream& fin)
{
	fin.clear();
	fin.seekg(0, std::ios::beg);
	std::string tmp;
	int32_t counter{};
	while (getline(fin, tmp))
	{
		++counter;
	}
	return counter;
}
void InputPeople(std::ifstream& fin, std::string* a, int32_t size)
{
	fin.clear();
	fin.seekg(0, std::ios::beg);
	for (int32_t i{}; i < size; ++i)
	{
		getline(fin, a[i]);
	}
	fin.close();
}
void FillBinary(std::fstream& bin, std::string* a, int32_t size)
{
	for (int32_t i{}; i < size; ++i)
	{
		bin.write(reinterpret_cast<char*>(&a[i]), sizeof a[i]);
	}
}