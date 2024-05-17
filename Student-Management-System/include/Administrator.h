#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "../include/Course.h"
#include "../include/Instructor.h"
#include "../include/Student.h"
#include "../include/User.h"
#include <iostream>
using namespace std;

class Administrator : public User {
  Instructor *instructors;
  Student *students;
  Course *courses;
  int numInstructors;
  int numStudents;
  int numCourses;

public:
  Administrator(const string &, const string &);
  void addStudent(const Student &);
  void removeStudent(const int &);
  void addInstuctor(const Instructor &);
  void removeInstructor(const int &);
  void addCourse(const Course &);
  void removeCourse(const string &);
};

#endif
