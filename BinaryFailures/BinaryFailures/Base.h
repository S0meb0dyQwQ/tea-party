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

struct StudentByPerformance {
	std::string surname;
	int32_t group{};
	int32_t id{};
};

void CheckFile(std::fstream&);
void CheckInputFile(std::ifstream&);
void CheckOutputFile(std::ofstream&);
void CheckPeople(int32_t);
void CheckGroup(int32_t);
void CheckSize(int32_t);
int32_t CountPeople(std::ifstream&);
void InputPeople(std::ifstream& fin, std::string* a, int32_t size);
void FillBinary(std::fstream& bin, std::string* a, int32_t size);
void FillStructuresFromStudents(std::ifstream& fin, Student* a, int32_t size);
void FillStructuresFromMarks(std::ifstream& fin, Student* a, int32_t size);
void ConnectStudentsAndMarks(Student* a, int32_t size_a, Student* b, int32_t size_b);
void MakeMainBin(std::fstream& bin, Student* a, int32_t size);

double CountAverage(Student a);
void FillAverageMark(Student* a, int32_t size);
void MakeAverageBin(std::fstream& bin, Student* a, int32_t size);

bool CompareSurnamesByAlphabet(std::string, std::string);
void SortByAlphabet(Student*, size_t);
int32_t CountPeopleInGroup(Student*, size_t, int32_t);
void FillArrayByGroup(Student*, size_t, Student*, int32_t);
void CreateStatemantByAlphabet(Student*, size_t);
void BubbleSort(Student*, size_t);
void CreateStatementByAverageMark(Student*, size_t);
int32_t CountHighAchievers(Student*, size_t);
void InputHighAchievers(StudentByPerformance*, Student*, size_t);

int32_t CountUnderachievers(Student*, int32_t);
void SortUnderachieversByGroupAndSurname(StudentByPerformance*, int32_t);
void InputUnderachievers(Student* array, int32_t arraySize, StudentByPerformance* UnderachieversArray);

void InputUnderachievers(Student*, int32_t, StudentByPerformance*);
void MakeStudentsByPerformanceBin(std::fstream&, StudentByPerformance*, int32_t);

void SortUnderachieversByGroupAndSurname(StudentByPerformance*, int32_t);

void PrintBinary(std::fstream&);

void FillTxtWithList(StudentByPerformance*, int32_t, std::ofstream&);
void PrintList(StudentByPerformance*, int32_t);
#endif