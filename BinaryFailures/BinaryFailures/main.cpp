#include "Base.h"
int main()
{
	//1)CheckOutputFile and CheckInputFile 
	std::ifstream fin_stud("Students.txt");//1)
	std::ifstream fin_mark("Marks.txt");//1)
	std::fstream bin_stud("Parent.bin", std::ios::in | std::ios::out | std::ios::binary);//1)
	std::fstream bin_mark("Mother.bin", std::ios::in | std::ios::out | std::ios::binary);//1)

	//if there is no people
	int32_t size_stud{ CountPeople(fin_stud) };
	std::string* lines = new std::string[size_stud];
	InputPeople(fin_stud, lines, size_stud);
	FillBinary(bin_stud, lines, size_stud);
	bin_stud.close();
	int32_t size_mark = CountPeople(fin_mark);
	InputPeople(fin_mark, lines, size_mark);
	FillBinary(bin_mark, lines, size_mark);
	bin_mark.close();
	delete[]lines;

	Student* peoples = new Student[size_stud];
	FillStructuresFromStudents(fin_stud, peoples, size_stud);
	fin_stud.close();

	Student* marks = new Student[size_mark];
	//2) if marks>10 or <0
	FillStructuresFromMarks(fin_mark, marks, size_mark);//2)
	fin_mark.close();

	ConnectStudentsAndMarks(peoples, size_stud, marks, size_mark);
	delete[]marks;
	std::fstream average_bin("Average.bin", std::ios::in | std::ios::out | std::ios::binary);//1)
	FillAverageMark(peoples, size_stud);
	MakeAverageBin(average_bin, peoples, size_stud);
	average_bin.close();
	std::fstream stud_bin("InfoStud.bin", std::ios::in | std::ios::out | std::ios::binary);//1)
	MakeMainBin(stud_bin, peoples, size_stud);
	stud_bin.close();
	//try
	//if there is no underachievers but programm can fork after this
	int32_t countOfUnderachievers{ CountUnderachievers(peoples, size_stud) };
	StudentByPerformance* underachievePeoples = new StudentByPerformance[countOfUnderachievers];
	InputUnderachievers(peoples, size_stud, underachievePeoples);
	std::fstream unachivers("Underachievers.bin", std::ios::in | std::ios::out | std::ios::binary);//1)
	MakeStudentsByPerformanceBin(unachivers, underachievePeoples, countOfUnderachievers);
	PrintBinary(unachivers);
	unachivers.close();

	SortUnderachieversByGroupAndSurname(underachievePeoples, countOfUnderachievers);

	std::fstream unachivers_sorted("Underachievers_sorted.bin", std::ios::in | std::ios::out | std::ios::binary);//1)
	MakeStudentsByPerformanceBin(unachivers_sorted, underachievePeoples, countOfUnderachievers);
	PrintBinary(unachivers_sorted);
	unachivers_sorted.close();
	//catch
	
	//3)if u input wrong number (<0) and if there is no group
	//try
	CreateStatemantByAlphabet(peoples, size_stud);//3)

	CreateStatementByAverageMark(peoples, size_stud);//3)
	//catch
	int32_t size_high_achiev{ CountHighAchievers(peoples, size_stud) };// also like underachievers
	StudentByPerformance* HighAchievers = new StudentByPerformance[size_high_achiev];
	InputHighAchievers(HighAchievers, peoples, size_stud);
	delete[]peoples;
	SortUnderachieversByGroupAndSurname(HighAchievers, size_high_achiev);

	std::ofstream outBad("bad_marks.txt");//1)


	FillTxtWithList(underachievePeoples, countOfUnderachievers, outBad);
	outBad.close();
	PrintList(underachievePeoples, countOfUnderachievers);
	delete[]underachievePeoples;

	std::ofstream outGood("good_marks.txt");//1)


	FillTxtWithList(HighAchievers, size_high_achiev, outGood);
	outGood.close();
	PrintList(HighAchievers, size_high_achiev);
	delete[]HighAchievers;

	return 0;
}