#include "Base.h"

#include <vector>
#include <optional>

int main()
{
	try 
	{
		std::ifstream fin_stud("Students.txt");
		CheckInputFile(fin_stud);
		int32_t size_stud{ CountPeople(fin_stud) };
		std::string* lines{ new std::string[size_stud] };
		InputPeople(fin_stud, lines, size_stud);

		std::fstream bin_stud("Parent.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckFile(bin_stud);
		FillBinary(bin_stud, lines, size_stud);
		bin_stud.close();

		std::ifstream fin_mark("Marks.txt");
		CheckInputFile(fin_mark);
		int32_t size_mark = CountPeople(fin_mark);
		InputPeople(fin_mark, lines, size_mark);

		std::fstream bin_mark("Mother.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckFile(bin_mark);
		FillBinary(bin_mark, lines, size_mark);
		bin_mark.close();

		delete[] lines;

		Student* peoples = new Student[size_stud];
		FillStructuresFromStudents(fin_stud, peoples, size_stud);
		fin_stud.close();

		Student* marks = new Student[size_mark];
		FillStructuresFromMarks(fin_mark, marks, size_mark);
		fin_mark.close();

		ConnectStudentsAndMarks(peoples, size_stud, marks, size_mark);
		delete[] marks;
		std::fstream average_bin("Average.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckFile(average_bin);
		FillAverageMark(peoples, size_stud);
		MakeAverageBin(average_bin, peoples, size_stud);
		average_bin.close();
		std::fstream stud_bin("InfoStud.bin", std::ios::in | std::ios::out | std::ios::binary);
		CheckFile(stud_bin);
		MakeMainBin(stud_bin, peoples, size_stud);
		stud_bin.close();

		
		int32_t countOfUnderachievers{ CountUnderachievers(peoples, size_stud) };
		try {
			CheckPeople(countOfUnderachievers);
			StudentByPerformance* underachievePeoples = new StudentByPerformance[countOfUnderachievers];
			InputUnderachievers(peoples, size_stud, underachievePeoples);
			std::fstream unachivers("Underachievers.bin", std::ios::in | std::ios::out | std::ios::binary);
			CheckFile(unachivers);
			MakeStudentsByPerformanceBin(unachivers, underachievePeoples, countOfUnderachievers);
			std::cout << "array before sort: \n";
			PrintBinary(unachivers);
			unachivers.close();

			SortUnderachieversByGroupAndSurname(underachievePeoples, countOfUnderachievers);

			std::fstream unachivers_sorted("Underachievers_sorted.bin", std::ios::in | std::ios::out | std::ios::binary);
			CheckFile(unachivers_sorted);
			MakeStudentsByPerformanceBin(unachivers_sorted, underachievePeoples, countOfUnderachievers);
			std::cout << "array after sort: \n";
			PrintBinary(unachivers_sorted);
			unachivers_sorted.close();
			std::ofstream outBad("bad_marks.txt");
			CheckOutputFile(outBad);

			FillTxtWithList(underachievePeoples, countOfUnderachievers, outBad);
			outBad.close();
			std::cout << "here is your underachievers\n";
			PrintList(underachievePeoples, countOfUnderachievers);
			delete[]underachievePeoples;
		}
		catch (std::ios_base::failure& e)
		{
			std::cout << e.what();
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what();
		}

		try 
		{
			CreateStatemantByAlphabet(peoples, size_stud);
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what();
		}
		try
		{
			CreateStatementByAverageMark(peoples, size_stud);
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what();
		}
		try {
			int32_t size_high_achiev{ CountHighAchievers(peoples, size_stud) };
			CheckPeople(size_high_achiev);
			StudentByPerformance* HighAchievers = new StudentByPerformance[size_high_achiev];
			InputHighAchievers(HighAchievers, peoples, size_stud);
			delete[] peoples;
			SortUnderachieversByGroupAndSurname(HighAchievers, size_high_achiev);
			std::ofstream outGood("good_marks.txt");
			CheckOutputFile(outGood);


			FillTxtWithList(HighAchievers, size_high_achiev, outGood);
			outGood.close();
			std::cout << "here is your highachievers\n";
			PrintList(HighAchievers, size_high_achiev);
			delete[]HighAchievers;
		}
		catch (std::ios_base::failure& e)
		{
			std::cout << e.what();
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what();
		}
	}
	catch (std::ios_base::failure& e)
	{
		std::cout << e.what();
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what();
	}
	return 0;
}