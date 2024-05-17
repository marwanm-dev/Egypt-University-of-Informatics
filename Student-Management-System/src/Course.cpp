#include "../include/Course.h"

Course::Course()
    : name(""), code(0), numInstructors(0), credits(0), studentIds(0),
      studentGrades(0), numStudents(0), instructorIds(0), MAX_INSTRUCTORS(3) {}
Course::Course(string name, string code, int credits)
    : numStudents(0), numInstructors(0), MAX_INSTRUCTORS(3) {
  this->name = name;
  this->code = code;
  this->credits = credits;
  instructorIds = new int[MAX_INSTRUCTORS];
  studentIds = new int[0];
  studentGrades = new double[0];
}
Course::~Course() {
  delete[] instructorIds;
  delete[] studentIds;
  delete[] studentGrades;
}

void Course::addInstructorId(int id) { instructorIds[numInstructors++] = id; }
void Course::addStudentId(int id) {
  studentIds[numStudents] = id;
  studentGrades[numStudents++] = id;
}
double Course::getMaxGrade() {
  int max = studentGrades[0];
  for (int i = 1; i < numStudents; i++) {
    if (studentGrades[i] > max) {
      max = studentGrades[i];
    }
  }
  return max;
}
double Course::getMinGrade() {
  int min = studentGrades[0];
  for (int i = 0; i < numStudents; i++) {
    if (studentGrades[i] < min) {
      min = studentGrades[i];
    }
  }
  return min;
}
double Course::getAvgGrade(int id = -1) {
  double sum = 0;
  if (id == -1) {
    for (int i = 0; i < numStudents; i++) {
      sum += studentGrades[i];
    }
    return sum / numStudents;
  } else {
    for (int i = 0; i < numStudents; i++) {
      if (studentIds[i] == id) {
        return studentGrades[i];
      }
    }
  }
}
