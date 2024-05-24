#ifndef STUDENT_H
#define STUDENT_H

class Administrator;

#include "Administrator.h"
#include "Course.h"
#include "User.h"
#include <iostream>
using namespace std;

class Student : public User {
  Course *courses;
  double *grades;
  int numCourses;
  const int MAX_COURSES;
  const Administrator *ADMIN;

public:
  Student();
  ~Student();
  Student(const string &, const string &, const Administrator &);
  void registerCourse(const string &);
  void dropCourse(const string &);
  double getGrade(const string &);
  double getStats(const string &);
  void operator=(const Student &);
  void display() const;
  void handleMenu();
};

#endif
