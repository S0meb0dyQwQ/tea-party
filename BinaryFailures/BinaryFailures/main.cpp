#include "Base.h"
int main()
{
	std::ifstream fin_stud("Students.txt");
	std::ifstream fin_mark("Marks.txt");
	std::fstream bin_stud("Parent.bin", std::ios::in | std::ios::out | std::ios::binary);
	std::fstream bin_mark("Mother.bin", std::ios::in | std::ios::out | std::ios::binary);
	int32_t size{ CountPeople(fin_stud) };
	std::string* peoples = new std::string[size];
	InputPeople(fin_stud, peoples, size);
	FillBinary(bin_stud, peoples, size);
	InputPeople(fin_mark, peoples, size);
	FillBinary(bin_mark, peoples, size);

	return 0;
}