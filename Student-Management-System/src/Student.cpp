#include "../include/Student.h"
#include "../include/Course.h"
#include "swapIndices.cpp"

Student::Student() : numCourses(0), MAX_COURSES(6) {}
Student::Student(string username, string password)
    : User(username, password), numCourses(0), MAX_COURSES(6) {
  courses = new Course[MAX_COURSES];
  grades = new double[MAX_COURSES];
}

void Student::registerCourse(Course course) {
  // courses[numCourses++] = course;
}

void Student::dropCourses(string code) {
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == code) {
      // swapIndices(courses[i], courses[numCourses - 1]);
      numCourses--;
    }
  }
}
double Student::getGrade(string code) {
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == code) {
      int numStudents = courses[i].getNumStudents();
      for (int j = 0; j < numStudents; ++j) {
        if (courses[i].getStudentIds()[j] == getId()) {
          return courses[i].getStudentIds()[j];
        }
      }
    }
  }
}
