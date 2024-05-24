#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

class Administrator;

#include "Administrator.h"
#include "Course.h"
#include "User.h"
#include <iostream>
using namespace std;

class Instructor : public User {
  Course *courses;
  int numCourses;
  const int MAX_COURSES;
  const Administrator *ADMIN;

public:
  Instructor();
  ~Instructor();
  Instructor(const string &, const string &, const Administrator &);
  void addCourse(const string &);
  void removeCourse(const string &);
  void setGrade(const string &, const int &, const double &);
  double performStats(const string &, const string &);
  void operator=(const Instructor &);
  void display() const;
  void handleMenu();
};

#endif
