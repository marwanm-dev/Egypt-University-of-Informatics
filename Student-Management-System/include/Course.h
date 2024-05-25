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
  int numStudents;
  int numInstructors;
  int studentCapacity;
  const int MAX_INSTRUCTORS;

public:
  Course();
  Course(const Course &);
  Course(const string &, const string &, const int &);
  ~Course();
  void addInstructorId(const int &);
  void removeInstructorId(const int &);
  void addStudent(const int &, const double &);
  void removeStudent(const int &);
  double getGrade(const int &);
  double getAvgGrade();
  double getMaxGrade();
  double getMinGrade();
  void resizeStudents();
  void operator=(const Course &);
  void display() const;
  string getCode() const { return code; }
  string getName() const { return name; }
  int getCredits() const { return credits; }
  int getNumStudents() { return numStudents; };
  int *getStudentIds() { return studentIds; };
  double *getStudentGrades() { return studentGrades; };
};

#endif