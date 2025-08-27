#include "Base.h"
int main()
{
	std::ifstream fin_stud("Students.txt");
	std::ifstream fin_mark("Marks.txt");
	std::fstream bin_stud("Parent.bin", std::ios::in | std::ios::out | std::ios::binary);
	std::fstream bin_mark("Mother.bin", std::ios::in | std::ios::out | std::ios::binary);

	int32_t size_stud{ CountPeople(fin_stud) };
	std::string* lines = new std::string[size_stud];
	InputPeople(fin_stud, lines, size_stud);
	FillBinary(bin_stud, lines, size_stud);
	int32_t size_mark = CountPeople(fin_mark);
	InputPeople(fin_mark, lines, size_mark);
	FillBinary(bin_mark, lines, size_mark);
	delete[]lines;

	Student* peoples = new Student[size_stud];
	FillStructuresFromStudents(fin_stud, peoples, size_stud);
	Student* marks = new Student[size_mark];
	FillStructuresFromMarks(fin_mark, marks, size_mark);
	ConnectStudentsAndMarks(peoples, size_stud, marks, size_mark);
	//моё
	FillAverageMark(peoples, size_stud);
	for (size_t i{}; i < size_stud; ++i) {
		std::cout << peoples[i].surname << '\t' << peoples[i].id << '\n';
	}
	CreateStatemantByAlphabet(peoples, size_stud);
	CreateStatementByAverageMark(peoples, size_stud);
	int32_t size_high_achiev{ CountHighAchievers(peoples, size_stud) };
	StudentByPerformance* HighAchievers = new StudentByPerformance[size_high_achiev];
	InputHighAchievers(HighAchievers, peoples, size_stud);
	for (size_t i{}; i < size_high_achiev; ++i) {
		std::cout << HighAchievers[i].surname << '\t' << HighAchievers[i].id << '\n';
	}
	//моё кончилось
	delete[]marks;
	std::fstream stud_bin("InfoStud.bin", std::ios::in | std::ios::out | std::ios::binary);
	MakeMainBin(stud_bin, peoples, size_stud);

	std::fstream average_bin("Average.bin", std::ios::in | std::ios::out | std::ios::binary);
	FillAverageMark(peoples, size_stud);
	return 0;
}