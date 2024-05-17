#include "../include/Administrator.h"
#include "../include/Instructor.h"
#include "../include/User.h"
#include "swapIndices.cpp"

Administrator::Administrator(const string &username, const string &password)
    : User(username, password), numInstructors(0), numStudents(0),
      numCourses(0), instructors(new Instructor[0]), students(new Student[0]),
      courses(new Course[0]) {}
void Administrator::addStudent(const Student &student) {
  // students[numStudents++] = student;
}
void Administrator::removeStudent(const int &id) {
  for (int i = 0; i < numStudents; ++i) {
    if (students[i].getId() == id) {
      // swapIndices(students[i], students[numStudents - 1]);
      numStudents--;
    }
  }
}
void Administrator::addInstuctor(const Instructor &instructor) {
  // instructors[numInstructors++] = instructor;
}
void Administrator::removeInstructor(const int &id) {
  for (int i = 0; i < numInstructors; i++) {
    if (instructors[i].getId() == id) {
      // swapIndices(instructors[i], instructors[numInstructors - 1]);
      numInstructors--;
    }
  }
}
void Administrator::addCourse(const Course &course) {
  // courses[numCourses++] = course;
}
void Administrator::removeCourse(const string &code) {
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      // swapIndices(courses[i], courses[numCourses - 1]);
      numCourses--;
    }
  }
}
