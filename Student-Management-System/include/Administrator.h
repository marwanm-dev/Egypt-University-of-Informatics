#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

class Student;
#include "../include/Course.h"
#include "../include/Instructor.h"
#include "../include/User.h"
#include <iostream>
using namespace std;

class Administrator : public User {
  Student *students;
  Instructor *instructors;
  Course *courses;
  int studentCapacity;
  int instructorCapacity;
  int courseCapacity;
  int numInstructors;
  int numStudents;
  int numCourses;

public:
  Administrator(const string &, const string &);
  ~Administrator();
  void addStudent(const Student &);
  void removeStudent(const int &);
  void addInstructor(const Instructor &);
  void removeInstructor(const int &);
  void addCourse(const Course &);
  void removeCourse(const string &);
  void resizeStudents();
  void resizeInstructors();
  void resizeCourses();
  int getNumInstructors() const { return numInstructors; };
  Instructor *getInstructors() const { return instructors; };
  int getNumStudents() const { return numStudents; };
  Student *getStudents() const { return students; };
  Course *getCourse(const string &code) const;
  string *getCourseCodes() const;
  void display() const;
  void handleMenu();
};

#endif