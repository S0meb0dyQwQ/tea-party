#include "Base.h"
void CheckFile(std::fstream& f)
{

	if (!f.good())
	{
		throw  std::ios_base::failure("file doesn't exist\n");
	}
	if (!f)
	{
		throw  std::ios_base::failure("output file error\n");
	}

}
void CheckOutputFile(std::ofstream& fout) 
{
	if (!fout.good())
	{
		throw  std::ios_base::failure("file doesn't exist\n");
	}
	if (!fout)
	{
		throw  std::ios_base::failure("output file error\n");
	}
}
void CheckInputFile(std::ifstream& fin)
{

	if (!fin.good())
	{
		throw std::ios_base::failure("file doesn't exist\n");
	}
	if (!fin)
	{
		throw  std::ios_base::failure("input file error\n");
	}
	if (fin.peek() == EOF)
	{
		throw  std::ios_base::failure("file is empty!\n");
	}
}
void CheckPeople(int32_t a)
{
	if (a == 0)
	{
		throw std::invalid_argument( "there's no such people\n");
	}
}
void CheckGroup(int32_t a) 
{
	if (a <= 0)
	{
		throw std::invalid_argument("there cant't be group with this number\n");
	}
}
void CheckSize(int32_t a)
{
	if (a <= 0)
	{
		throw std::invalid_argument("there no people in this group\n");
	}
}
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
	for (int32_t i = 0; i < size; ++i)
	{
		getline(fin, a[i]);
	}
}
void FillBinary(std::fstream& bin, std::string* a, int32_t size)
{
	for (int32_t i{}; i < size; ++i)
	{
		const char* cstr = a[i].c_str();
		bin.write(cstr, sizeof cstr);
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
			a[i].group = b[k].group;
		}
	}
}

void MakeMainBin(std::fstream& bin, Student* a, int32_t size) { 
	for (int32_t i{}; i < size; ++i) {

		std::string str = a[i].name + ';';
		bin.write(str.c_str(), str.size());

		str = a[i].surname + ';';
		bin.write(str.c_str(), str.size());

		str = a[i].patronymic + ';';
		bin.write(str.c_str(), str.size());

		str = std::to_string(a[i].group) + ';';
		bin.write(str.c_str(), str.size());

		str = std::to_string(a[i].id) + ';';
		bin.write(str.c_str(), str.size());

		str = std::to_string(a[i].mark_ma) + ';';
		bin.write(str.c_str(), str.size());

		str = std::to_string(a[i].mark_geo) + ';';
		bin.write(str.c_str(), str.size());

		str = std::to_string(a[i].mark_proga) + '\n';
		bin.write(str.c_str(), str.size());
	}
	/*std::string str = { '\0'};
	bin.write(str.c_str(), str.size());*/
}

double CountAverage(Student a)
{
	return(static_cast<double>(a.mark_geo + a.mark_ma + a.mark_proga)) / 3;
}
void FillAverageMark(Student* a, int32_t size)
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
		bin.write((char*)(&a[i].average), sizeof a[i].average);

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
//
void InputUnderachievers(Student* array, int32_t arraySize, StudentByPerformance* UnderachieversArray) {
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
void MakeStudentsByPerformanceBin(std::fstream& bin, StudentByPerformance* a, int32_t size) 
{

	for (int32_t i{}; i < size; ++i) 
	{
		std::string str = a[i].surname + ';';
		bin.write(str.c_str(), str.size());

		str = std::to_string(a[i].group) + ';';
		bin.write(str.c_str(), str.size());

		str = std::to_string(a[i].id) + '\n';
		bin.write(str.c_str(), str.size());
	}
}
void SortUnderachieversByGroupAndSurname(StudentByPerformance* UnderachieversArray, int32_t arraySize) {
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
//функция сортировки 

void PrintBinary(std::fstream& bin) {
	bin.seekg(0, std::ios::end);
	size_t arraySize = static_cast<size_t>(bin.tellg());
	bin.seekg(0, std::ios::beg);
	char* cText = new char[arraySize];
	bin.read(cText, arraySize);
	std::string binText{ cText, arraySize };
	delete[] cText;
	std::cout << binText;
}
void FillTxtWithList(StudentByPerformance* list, int32_t listSize, std::ofstream& oFile) {
	for (int32_t i{}; i < listSize; ++i) {
		oFile << list[i].surname << ';' << list[i].group << ';' << list[i].id << '\n';
	}
}

void PrintList(StudentByPerformance* list, int32_t listSize) {
	for (int32_t i{}; i < listSize; ++i) {
		std::cout << list[i].surname << ';' << list[i].group << ';' << list[i].id << '\n';
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
	CheckGroup(group_number);
	int32_t size{ CountPeopleInGroup(peoples, size_stud, group_number) };
	CheckSize(size);
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
	CheckGroup(group_number);
	int32_t size{ CountPeopleInGroup(peoples, size_stud, group_number) };
	CheckSize(size);
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
void InputHighAchievers(StudentByPerformance* array, Student* peoples, size_t size_stud)
{
	size_t t{};
	for (size_t i{}; i < size_stud; ++i)
	{
		if (peoples[i].average >= 8) {
			array[t].surname = peoples[i].surname;
			array[t].group = peoples[i].group;
			array[t++].id = peoples[i].id;
		}
	}
}
//функция вывода содержимого
//бинарного файла на консоль