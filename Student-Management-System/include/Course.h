#ifndef COURSE_H
#define COURSE_H

#include <iostream>
using namespace std;

class Course {
  string name;
  string code;
  int credits;
  int *instructorIds;
  int *studentIds;
  double *studentGrades;
  int numInstructors;
  int numStudents;
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
  string getCode() const { return code; }
  string getName() const { return name; }
  int getCredits() const { return credits; }
  int getNumStudents() { return numStudents; };
  int *getStudentIds() { return studentIds; };
  double *getStudentGrades() { return studentGrades; };
  void incrementNumStudents();
  void operator=(const Course &);
  void display() const;
};

#endif
