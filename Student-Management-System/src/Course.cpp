#include "../include/Course.h"
#include "../include/CONSTANTS.h"
#include "./inputValidation.cpp"
#include "./swapIndices.cpp"
#include <iomanip>

Course::Course()
    : name(""), code(""), credits(0), numStudents(0), numInstructors(0),
      numPrerequisites(0), MAX_INSTRUCTORS(COURSE_MAX_INSTRUCTORS) {}
Course::Course(const string &name, const string &code, const int &credits)
    : numStudents(0), numInstructors(0), numPrerequisites(0),
      MAX_INSTRUCTORS(COURSE_MAX_INSTRUCTORS) {
  instructorIds = new int[MAX_INSTRUCTORS];
  studentIds = new int[0];
  studentGrades = new double[0];
  prerequisites = new Course[0];
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
  instructorIds[numInstructors++] = id;
}
void Course::addPrerequisite(const Course &course) {
  prerequisites[numPrerequisites++] = course;
}
void Course::removePrerequisite(const string &code) {
  if (numPrerequisites == 0)
    cout << "No Prerequisites to remove." << endl;
  int initialNumPrerequisites = numPrerequisites;
  for (int i = 0; i < numPrerequisites; ++i) {
    if (prerequisites[i].code == code) {
      swapIndices(prerequisites[i], prerequisites[numPrerequisites - 1]);
      --numPrerequisites;
    }
  }
  if (initialNumPrerequisites == numPrerequisites) {
    cout << INVALID_CODE;
  } // if number of instructors did not decrease by 1
}

void Course::addStudentId(const int &id) {
  bool eligible = false;
  for (int i = 0; i < numPrerequisites; ++i) {
    for (int j = 0; j < numStudents; ++j) {
      if (prerequisites[i].studentIds[j] == id)
        eligible = true;
    }
  }
  if (eligible) {
    studentIds[numStudents] = id;
    studentGrades[numStudents++] = id;

  } else {
    cout << "Ineligible due to missing preqrequisite courses:" << endl;
    for (int i = 0; i < numPrerequisites; ++i)
      cout << i + 1 << ": " << prerequisites[i].code << endl;
  }
}
double Course::getGrade(const int &id) {
  for (int i = 0; i < numStudents; ++i) {
    if (studentIds[i] == id)
      return studentGrades[i];
  }
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
  instructorIds = new int[course.numInstructors];
  studentIds = new int[course.numStudents];
  studentGrades = new double[course.numStudents];
  name = course.name;
  code = course.code;
  credits = course.credits;
  numStudents = course.numStudents;
  numInstructors = course.numInstructors;
  for (int i = 0; i < numStudents; i++) {
    studentIds[i] = course.studentIds[i];
    studentGrades[i] = course.studentGrades[i];
  }
  for (int i = 0; i < numInstructors; i++)
    instructorIds[i] = course.instructorIds[i];
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
