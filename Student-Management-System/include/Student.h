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
  Student(string, string);
  void registerCourse(Course);
  void dropCourses(string);
  double getGrade(string);
  double getAvgGrades();
  void display();
  // add the overloaded "=" operator
};

#endif
