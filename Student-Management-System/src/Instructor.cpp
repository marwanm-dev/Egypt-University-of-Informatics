#include "../include/Instructor.h"
#include "../include/Course.h"
#include "../include/User.h"
#include "swapIndices.cpp"
#include <string>

Instructor::Instructor() : MAX_COURSES(5) {}
Instructor ::Instructor(string username, string password)
    : User(username, password), MAX_COURSES(5) {
  numCourses = 0;
  courses = new Course[MAX_COURSES];
}
void Instructor ::addCourse(Course course) {
  // courses[numCourses++] = course;
}
void Instructor ::removeCourse(string code) {
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      // swapIndices(courses[i], courses[numCourses - 1]);
      numCourses--;
    }
  }
}
void Instructor ::setGrade(string code, int id, double grade) {
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      int numStudents = courses[i].getNumStudents();
      for (int j = 0; j < numStudents; j++) {
        if (courses[i].getStudentIds()[j] == id) {
          courses[i].getStudentGrades()[j] = grade;
        } else {
          courses[i].getStudentIds()[numStudents] = id;
          courses[i].getStudentGrades()[numStudents] = grade;
          courses[i].incrementNumStudents();
        }
      }
    }
  }
}
double Instructor ::performStats(string code, string type) {
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      if (type == "max") {
        courses[i].getMaxGrade();
      }
      if (type == "min") {
        courses[i].getMinGrade();
      }
      if (type == "avg") {
        courses[i].getAvgGrade(-1);
      }
    }
  }
};
