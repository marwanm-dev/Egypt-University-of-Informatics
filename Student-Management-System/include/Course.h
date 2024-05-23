#ifndef COURSE_H
#define COURSE_H

#include <iostream>
using namespace std;

class Course {
  string name;
  string code;
  int credits;
  Course *prerequisites;
  int *instructorIds;
  int *studentIds;
  double *studentGrades;
  int numInstructors;
  int numStudents;
  int numPrerequisites;
  const int MAX_INSTRUCTORS;

public:
  Course();
  Course(const string &, const string &, const int &);
  ~Course();
  void addInstructorId(const int &);
  void removeInstructorId(const int &);
  void addStudentId(const int &);
  void removeStudentId(const int &);
  void addPrerequisite(const Course &);
  void removePrerequisite(const string &);
  double getGrade(const int &);
  double getMaxGrade();
  double getMinGrade();
  double getAvgGrade();
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