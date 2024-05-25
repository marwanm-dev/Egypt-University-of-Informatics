#include "../include/Course.h"
#include "../include/CONSTANTS.h"
#include "./inputValidation.cpp"
#include "./swapIndices.cpp"
#include <iomanip>

Course::Course()
    : name(""), code(""), credits(0), numStudents(0), numInstructors(0),
      studentCapacity(INITIAL_CAPACITY),
      MAX_INSTRUCTORS(COURSE_MAX_INSTRUCTORS) {}
Course::Course(const string &name, const string &code, const int &credits)
    : numStudents(0), numInstructors(0), studentCapacity(1),
      MAX_INSTRUCTORS(COURSE_MAX_INSTRUCTORS) {
  instructorIds = new int[MAX_INSTRUCTORS];
  studentIds = new int[studentCapacity];
  studentGrades = new double[studentCapacity];
  if (isValidCourseCode(code) && isValidCourseName(name) &&
      isValidCourseCredits(credits)) {
    this->name = name;
    this->code = code;
    this->credits = credits;
  } else {
    this->name = "";
    if (!isValidCourseCode(code))
      cout << INVALID_CODE;
    else if (!isValidCourseName(name))
      cout << INVALID_COURSE_NAME;
    else
      cout << INVALID_COURSE_CREDITS;

    cout << "Course can not be created due to invalid information." << endl;
  }
}

Course::~Course() {
  delete[] instructorIds;
  delete[] studentIds;
  delete[] studentGrades;
}

void Course::addInstructorId(const int &id) {
  if (numInstructors < MAX_INSTRUCTORS) {
    instructorIds[numInstructors++] = id;
  } else
    cout << "Failed to add an instructor exceeding the maximum number of "
            "instructors per course."
         << endl;
}
void Course::removeInstructorId(const int &id) {
  for (int i = 0; i < numInstructors; ++i) {
    if (instructorIds[i] == id) {
      swapIndices(instructorIds[i], instructorIds[numInstructors - 1]);
      --numInstructors;
    }
  }
}
void Course::removeStudentId(const int &id) {
  for (int i = 0; i < numStudents; ++i) {
    if (studentIds[i] == id) {
      swapIndices(studentIds[i], studentIds[numStudents - 1]);
      swapIndices(studentGrades[i], studentGrades[numStudents - 1]);
      --numStudents;
    }
  }
}

void Course::addStudentId(const int &id, const double &grade) {
  bool found = false;
  for (int i = 0; i < numStudents; ++i) {
    if (studentIds[i] == id) {
      studentGrades[i] = grade;
      found = true;
      break;
    }
  }
  if (!found) {
    if (numStudents == studentCapacity)
      resizeStudents();

    studentIds[numStudents] = id;
    studentGrades[numStudents++] = grade;
  }
}

void Course::resizeStudents() {
  studentCapacity *= 2;
  int *newStudentIds = new int[studentCapacity];
  double *newStudentGrades = new double[studentCapacity];

  for (int i = 0; i < numStudents; ++i) {
    newStudentIds[i] = studentIds[i];
    newStudentGrades[i] = studentGrades[i];
  }

  delete[] studentIds;
  delete[] studentGrades;
  studentIds = newStudentIds;
  studentGrades = newStudentGrades;
}

double Course::getGrade(const int &id) {
  for (int i = 0; i < numStudents; ++i) {
    if (studentIds[i] == id)
      return studentGrades[i];
  }
  return -1;
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
    if (studentGrades[i] < min)
      min = studentGrades[i];
  }
  return min;
}
double Course::getAvgGrade() {
  double sum = 0;
  for (int i = 0; i < numStudents; i++) {
    sum += studentGrades[i];
  }
  return sum / numStudents;
}
void Course::incrementNumStudents() { ++numStudents; }

void Course::operator=(const Course &course) {
  delete[] instructorIds;
  delete[] studentIds;
  delete[] studentGrades;

  name = course.name;
  code = course.code;
  credits = course.credits;
  numStudents = course.numStudents;
  numInstructors = course.numInstructors;
  studentCapacity = course.studentCapacity;

  instructorIds = new int[MAX_INSTRUCTORS];
  studentIds = new int[studentCapacity];
  studentGrades = new double[studentCapacity];

  for (int i = 0; i < numStudents; ++i) {
    studentIds[i] = course.studentIds[i];
    studentGrades[i] = course.studentGrades[i];
  }

  for (int i = 0; i < numInstructors; ++i) {
    instructorIds[i] = course.instructorIds[i];
  }
}
void Course::display() const {
  cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << "Code"
       << setw(COURSE_NAME_MAX_LENGTH + SPACE) << "Name"
       << setw(COURSE_CREDITS_MAX_LENGTH + SPACE) << "Credits" << endl;
  cout << DIVIDER;
  cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << getCode()
       << setw(COURSE_NAME_MAX_LENGTH + SPACE) << getName()
       << setw(COURSE_CREDITS_MAX_LENGTH + SPACE) << getCredits() << endl;
  cout << endl;
  // Display header for Instructor Ids
  cout << "Instructor Ids:" << endl;
  cout << DIVIDER;
  for (int i = 0; i < numInstructors; ++i)
    cout << left << instructorIds[i] << endl;
  cout << endl;
  // Display header for Student Ids/Grades
  cout << "Student Ids and Grades" << endl;
  cout << left << setw(ID_MAX_LENGTH + SPACE) << "Id"
       << setw(GRADE_MAX_LENGTH + SPACE) << "Grade" << endl;
  cout << DIVIDER;
  for (int i = 0; i < numStudents; ++i)
    cout << left << setw(ID_MAX_LENGTH + SPACE) << studentIds[i]
         << setw(GRADE_MAX_LENGTH + SPACE) << studentGrades[i] << endl;

  cout << endl;
}
