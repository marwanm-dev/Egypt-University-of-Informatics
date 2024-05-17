#include "../include/Student.h"
#include "../include/Course.h"

Student::Student() : numCourses(0), MAX_COURSES(6) {}
Student::Student(string username, string password)
    : User(username, password), numCourses(0), MAX_COURSES(6) {
  courses = new Course[MAX_COURSES];
  grades = new double[MAX_COURSES];
}

void Student::registerCourse(Course course) {
  courses[numCourses++] = course;
  if (numCourses >= MAX_COURSES)
    cout << "can't register more";
}

void Student::dropCourses(string code) {
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == code) {
      Course temp = courses[i];
      courses[i] = courses[numCourses - 1];
      courses[numCourses - 1] = temp;
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
void Student::display() {
  User::display();
  cout << "Role: student" << endl;
  cout << courses[0].getCode();
}
