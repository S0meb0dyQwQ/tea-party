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

////////////////////////////////
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
//////////////////////////////////////

bool CompareSurnamesByAlphabet(Student a, Student b) {
	const char* A = a.surname.c_str();
	const char* B = b.surname.c_str();
	if (strcmp(A, B) > 0) {
		return 1;
	}
	return 0;
}

int32_t CountUnderachievers(Student* array, int32_t arraySize) {
	int32_t counter{};
	for (int32_t i{}; i < arraySize; ++i) {
		if (CountAverage(array[i]) < 4) {
			++counter;
		}
	}
	return counter;
}


void InputUnderachievers(Student* array, int32_t arraySize, Underachiever* UnderachieversArray) {
	int32_t counter{};
	for (int32_t i{}; i < arraySize; ++i) {
		if (CountAverage(array[i]) < 4) {
			UnderachieversArray[counter].surname = array[i].surname;
			UnderachieversArray[counter].group = array[i].group;
			UnderachieversArray[counter].id = array[i].id;
			++counter;
		}
	}
}


void SortUnderachieversByGroupAndSurname(Underachiever* UnderachieversArray, int32_t arraySize) {
	while (arraySize) {
		for (int32_t i{}; i < arraySize - 1; ++i) {
			if (UnderachieversArray[i].group > UnderachieversArray[i + 1].group) {
				std::swap(UnderachieversArray[i], UnderachieversArray[i + 1]);
			}
			if (UnderachieversArray[i].group == UnderachieversArray[i + 1].group) {
				if (CompareSurnamesByAlphabet(UnderachieversArray[i].surname, UnderachieversArray[i + 1].surname)) {
					std::swap(UnderachieversArray[i], UnderachieversArray[i + 1]);
				}
			}

		}
		--arraySize;
	}
}