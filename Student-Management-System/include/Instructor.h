#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "Course.h"
#include "User.h"
#include <iostream>
using namespace std;

class Instructor : public User {
private:
  Course *courses;
  int numCourses;
  const int MAX_COURSES;

public:
  Instructor();
  Instructor(string, string);
  void addCourse(Course);
  void removeCourse(string);
  void setGrade(string, int, double);
  double performStats(string, string);
  // add the overloaded "=" operator
};

#endif
