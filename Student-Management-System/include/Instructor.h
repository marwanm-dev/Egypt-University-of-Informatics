#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "Course.h"
#include "User.h"
#include <iostream>
using namespace std;

class Instructor : public User {
  Course *courses;
  int numCourses;
  const int MAX_COURSES;

public:
  Instructor();
  ~Instructor();
  Instructor(const string &, const string &);
  void addCourse(Course);
  void removeCourse(string);
  void setGrade(string, int, double);
  double performStats(string, string);
  void operator=(const Instructor &);
  void display() const;
  void handleMenu();
};

#endif
