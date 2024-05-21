#ifndef STUDENT_H
#define STUDENT_H

#include "../include/Course.h"
#include "../include/User.h"
#include <iostream>
using namespace std;

class Student : public User {
  Course *courses;
  double *grades;
  int numCourses;
  const int MAX_COURSES;

public:
  Student();
  ~Student();
  Student(const string &, const string &);
  void registerCourse(Course);
  void dropCourse(string);
  double getGrade(string);
  double getAvgGrades();
  void operator=(const Student &);
  void display() const;
  void handleMenu();
};

#endif
