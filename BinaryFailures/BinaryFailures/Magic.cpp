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
}
void FillBinary(std::fstream& bin, std::string* a, int32_t size)
{
	for (int32_t i{}; i < size; ++i)
	{
		bin.write(reinterpret_cast<char*>(&a[i]), sizeof a[i]);
	}
}
void FillStructuresFromStudents(std::ifstream& fin, Student* a, int32_t size)
{
	fin.clear();
	fin.seekg(0, std::ios::beg);
	for (int32_t i{}; i < size; ++i)
	{
		fin >> a[i].id;
		fin.ignore();
		getline(fin, a[i].surname, ';');
		getline(fin, a[i].name, ';');
		getline(fin, a[i].patronymic);
	}
}
void FillStructuresFromMarks(std::ifstream& fin, Student* a, int32_t size)
{
	fin.clear();
	fin.seekg(0, std::ios::beg);
	std::string line;
	for (int32_t i{}; i < size; ++i)
	{
		fin >> a[i].group;
		fin.ignore();
		fin >> a[i].id;
		fin.ignore();
		getline(fin,line, ';');
		fin >> a[i].mark_ma;
		fin.ignore();
		getline(fin, line, ';');
		fin >> a[i].mark_geo;
		fin.ignore();
		getline(fin, line, ';');
		fin >> a[i].mark_proga;
	}
}
void ConnectStudentsAndMarks(Student* a, int32_t size_a, Student* b, int32_t size_b)
{
	for (int32_t i{}; i < size_a; ++i)
	{
		for(int32_t k{}; k < size_b; ++k)
		if (a[i].id == b[k].id)
		{
			a[i].mark_ma = b[k].mark_ma;
			a[i].mark_geo = b[k].mark_geo;
			a[i].mark_proga = b[k].mark_proga;
		}
	}
}
void MakeMainBin(std::fstream& bin, Student* a, int32_t size) 
{
	for (int32_t i{}; i < size; ++i)
	{
		bin.write(reinterpret_cast<char*>(&a[i]), sizeof a[i]);
	}
}
double CountAverage(Student a)
{
	return(static_cast<double>(a.mark_geo + a.mark_ma + a.mark_proga)) / 3;
}
void FillAverageMark(Student* a, int32_t size)//well i dont know another ways
{
	for (int32_t i{}; i < size; ++i)
	{
		a[i].average = CountAverage(a[i]);
	}
}
void MakeAverageBin(std::fstream& bin, Student* a, int32_t size)
{
	for (int32_t i{}; i < size; ++i) 
	{
		bin.write(reinterpret_cast<char*>(&a[i].average), sizeof a[i].average);
	}

}