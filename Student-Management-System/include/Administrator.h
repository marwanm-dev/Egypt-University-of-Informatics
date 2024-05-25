#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

class Student;
class Instructor;
#include "../include/Course.h"
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
  int numStudents;
  int numInstructors;
  int numCourses;

public:
  Administrator();
  Administrator(const string &, const string &);
  ~Administrator();
  void addStudent(const Student &);
  void removeStudent(const int &);
  void addInstructor(const Instructor &);
  void removeInstructor(const int &);
  void addCourse(const Course &);
  void removeCourse(const string &);
  Course *getCourse(const string &) const;
  string *getCourseCodes() const;
  void resizeStudents();
  void resizeInstructors();
  void resizeCourses();
  void display() const;
  void handleMenu();
  int getNumStudents() const { return numStudents; };
  Student *getStudents() const { return students; };
  int getNumInstructors() const { return numInstructors; };
  Instructor *getInstructors() const { return instructors; };
  int getNumCourses() const { return numCourses; };
};

#endif