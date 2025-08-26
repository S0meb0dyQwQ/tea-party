#include "Base.h"
int main()
{
	std::ifstream fin_stud("Students.txt");
	std::ifstream fin_mark("Marks.txt");
	std::fstream bin_stud("Parent.bin", std::ios::in | std::ios::out | std::ios::binary);
	std::fstream bin_mark("Mother.bin", std::ios::in | std::ios::out | std::ios::binary);//я не знаю почему такие названия. просто так

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
	ConnectSurnamesAndMarks(peoples, size_stud, marks, size_mark);
	delete[]marks;
	std::fstream stud_bin("InfoStud.bin", std::ios::in | std::ios::out | std::ios::binary);
	MakeMainBin(stud_bin, peoples, size_stud);
	PrintStruct(peoples, size_stud);


	int32_t countOfUnderachievers{ CountUnderachievers(peoples, size_stud) };
	Underachiever* underachievePeoples = new Underachiever[countOfUnderachievers];
	InputUnderachievers(peoples, size_stud, underachievePeoples);
	SortUnderachieversByGroupAndSurname(underachievePeoples, countOfUnderachievers);




	return 0;
}