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
		getline(fin, line, ';');
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
		for (int32_t k{}; k < size_b; ++k)
			if (a[i].id == b[k].id)
			{
				a[i].mark_ma = b[k].mark_ma;
				a[i].mark_geo = b[k].mark_geo;
				a[i].mark_proga = b[k].mark_proga;
				a[i].group = b[k].group;//нада
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




bool CompareSurnamesByAlphabet(std::string a, std::string b) {
	const char* A = a.c_str();
	const char* B = b.c_str();
	if (strcmp(A, B) > 0) {
		return 1;
	}
	return 0;
}
void SortByAlphabet(Student* a, size_t size) {
	while (size) {
		for (size_t i{}; i < size - 1; ++i) {
			if (CompareSurnamesByAlphabet(a[i].surname, a[i + 1].surname)) {
				std::swap(a[i], a[i + 1]);
			}
		}
		--size;
	}
}
int32_t CountPeopleInGroup(Student* a, size_t size, int32_t group_number) {
	int32_t res{};
	for (size_t i{}; i < size; ++i) {
		if (a[i].group == group_number) {
			++res;
		}
	}
	return res;
}
void FillArrayByGroup(Student* peoples, size_t size_stud, Student* array, int32_t group_number) {
	size_t t{};
	for (size_t i{}; i < size_stud; ++i) {
		if (peoples[i].group == group_number) {
			array[t++] = peoples[i];
		}
	}
}
void CreateStatemantByAlphabet(Student* peoples, size_t size_stud) {
	std::cout << "Choose a group\n";
	int32_t group_number{};
	std::cin >> group_number;
	int32_t size{ CountPeopleInGroup(peoples, size_stud, group_number) };
	Student* group_by_alphabet = new Student[size];
	FillArrayByGroup(peoples, size_stud, group_by_alphabet, group_number);
	SortByAlphabet(group_by_alphabet, size);
	for (size_t i{}; i < size; ++i) {
		std::cout << group_by_alphabet[i].group << '\t' << group_by_alphabet[i].name << '\t' << group_by_alphabet[i].surname << '\t' << group_by_alphabet[i].patronymic << '\t' << CountAverage(group_by_alphabet[i]) << '\n';
	}
}
void BubbleSort(Student* array, size_t size) {
	while (size) {
		for (size_t i{}; i < size - 1; ++i) {
			if (array[i].average < array[i + 1].average) {
				std::swap(array[i], array[i + 1]);
			}
		}
		--size;
	}
}
void CreateStatementByAverageMark(Student* peoples, size_t size_stud) {
	std::cout << "Choose a group\n";
	int32_t group_number{};
	std::cin >> group_number;
	int32_t size{ CountPeopleInGroup(peoples, size_stud, group_number) };
	Student* group_by_alphabet = new Student[size];
	FillArrayByGroup(peoples, size_stud, group_by_alphabet, group_number);
	FillAverageMark(group_by_alphabet, size);
	BubbleSort(group_by_alphabet, size);
	for (size_t i{}; i < size; ++i) {
		std::cout << group_by_alphabet[i].group << '\t' << group_by_alphabet[i].name << '\t' << group_by_alphabet[i].surname << '\t' << group_by_alphabet[i].patronymic << '\t' << CountAverage(group_by_alphabet[i]) << '\n';
	}
}
int32_t CountHighAchievers(Student* array, size_t size) {
	int32_t res{};
	for (size_t i{}; i < size; ++i) {
		if (array[i].average >= 8) {
			++res;
		}
	}
	return res;
}
void InputHighAchievers(StudentByPerformance* array, Student* peoples, size_t size_stud) {
	size_t t{};
	for (size_t i{}; i < size_stud; ++i) {
		if (peoples[i].average >= 8) {
			array[t].surname = peoples[i].surname;
			array[t].group = peoples[i].group;
			array[t++].id = peoples[i].id;
		}
	}
}