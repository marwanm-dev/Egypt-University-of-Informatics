#ifndef COURSE_H
#define COURSE_H

#include <iostream>
using namespace std;

class Course {
  string name;
  string code;
  int *instructorIds;
  int credits;
  int *studentIds;
  double *studentGrades;
  int numStudents;
  int numInstructors;
  const int MAX_INSTRUCTORS;

public:
  Course();
  Course(string, string, int);
  ~Course();
  void addInstructorId(int);
  void addStudentId(int);
  double getMaxGrade();
  double getMinGrade();
  double getAvgGrade(int);
  string getCode() { return code; }
  int getNumStudents() { return numStudents; };
  int *getStudentIds() { return studentIds; };
  double *getStudentGrades() { return studentGrades; };
  void incrementNumStudents();
  // Add overloaded "=" operator
};

#endif
