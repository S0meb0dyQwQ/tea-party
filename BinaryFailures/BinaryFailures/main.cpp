#include "Functions.h"
int main()
{
	std::ifstream fin_stud("Students.txt");
	std::ifstream fin_mark("Marks.txt");
	std::fstream bin_stud("Parent.bin", std::ios::out | std::ios::in | std::ios::binary);
	std::fstream bin_mark("Mother.bin", std::ios::out | std::ios::in | std::ios::binary);



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
	delete[]marks;
	std::fstream stud_bin("InfoStud.bin", std::ios::out | std::ios::in | std::ios::binary);
	/*MakeMainBin(stud_bin, peoples, size_stud);*/



	/////////////
	std::fstream average_bin("Average.bin", std::ios::out | std::ios::in | std::ios::binary);
	FillAverageMark(peoples, size_stud);
	//////////////


	int32_t countOfUnderachievers{ CountUnderachievers(peoples, size_stud) };
	StudentByPerformance* underachievePeoples = new StudentByPerformance[countOfUnderachievers];
	InputUnderachievers(peoples, size_stud, underachievePeoples);
	/*std::fstream unachivers("Underachievers_list.bin", std::ios::out | std::ios::in | std::ios::binary);
	MakeStudentsByPerformanceBin(unachivers, underachievePeoples, countOfUnderachievers);*/


	SortUnderachieversByGroupAndSurname(underachievePeoples, countOfUnderachievers);
	/*std::fstream sortedUnachiversOut("Underachievers_sortedList.bin", std::ios::out | std::ios::in | std::ios::binary);
	MakeStudentsByPerformanceBin(sortedUnachiversOut, underachievePeoples, countOfUnderachievers);
	std::fstream sortedUnachiversIn("Underachievers_sortedList.bin", std::ios::out | std::ios::in | std::ios::binary);
	PrintBinary(sortedUnachiversIn);*/


	std::ofstream outBad("bad_marks.txt");


	FillTxtWithList(underachievePeoples, countOfUnderachievers, outBad);
	PrintList(underachievePeoples, countOfUnderachievers);




	stud_bin.close();
	bin_stud.close();
	bin_mark.close();
	/*unachivers.close();*/
	/*sortedUnachiversOut.close();*/
	/*sortedUnachiversIn.close();*/
	average_bin.close();
	fin_mark.close();
	fin_stud.close();
	outBad.close();
	delete[]peoples;
	delete[]underachievePeoples;
	return 0;
}