#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <string>
#include <fstream>

struct Student
{
	std::string name;
	std::string surname;
	std::string patronymic;
	int32_t group{};
	int32_t id{};
	int32_t mark_ma{};
	int32_t mark_geo{};
	int32_t mark_proga{};
	double average{ 0.0 };
};


struct Underachiever {
	std::string surname;
	int32_t group{};
	int32_t id{};
};


int32_t CountPeople(std::ifstream&);
void InputPeople(std::ifstream& fin, std::string* a, int32_t size);
void FillBinary(std::fstream& bin, std::string* a, int32_t size);
void FillStructuresFromStudents(std::ifstream& fin, Student* a, int32_t size);
void FillStructuresFromMarks(std::ifstream& fin, Student* a, int32_t size);
void ConnectStudentsAndMarks(Student* a, int32_t size_a, Student* b, int32_t size_b);
void MakeMainBin(std::fstream& bin, Student* a, int32_t size);

////////////////////////
double CountAverage(Student a);
void FillAverageMark(Student* a, int32_t size);
void MakeAverageBin(std::fstream& bin, Student* a, int32_t size);
//////////////////////////////

int32_t CountUnderachievers(Student*, int32_t);
void InputUnderachievers(Student*, int32_t, Underachiever*);
void SortUnderachieversByGroupAndSurname(Underachiever*, int32_t);

#endif