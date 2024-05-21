#include "../include/Student.h"
#include "../include/CONSTANTS.h"
#include "../include/Course.h"
#include "swapIndices.cpp"
#include <iomanip>

Student::Student() : numCourses(0), MAX_COURSES(STUDENT_MAX_COURSES) {}

Student::Student(const string &username, const string &password)
    : User(username, password), numCourses(0),
      MAX_COURSES(STUDENT_MAX_COURSES) {
  courses = new Course[MAX_COURSES];
  grades = new double[MAX_COURSES];
  if (username == "") // invalid credentials validated by the User constructor
    cout << "Student can not be created due to invalid credentials." << endl;
}

Student::~Student() {
  delete[] courses;
  delete[] grades;
}

void Student::registerCourse(Course course) { courses[numCourses++] = course; }

void Student::dropCourse(string code) {
  for (int i = 0; i < numCourses; ++i) {
    if (courses[i].getCode() == code) {
      swapIndices(courses[i], courses[numCourses - 1]);
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
  return -1;
}
double Student::getAvgGrades() {
  double sum = 0;
  for (int i = 0; i < numCourses; ++i)
    sum += courses[i].getAvgGrade(getId());

  return sum / numCourses;
}
void Student::display() const {
  User::display();

  // Display header for Courses and Grades
  cout << "Students' Courses/Grades" << endl;
  cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << "Code"
       << setw(COURSE_NAME_MAX_LENGTH + SPACE) << "Name"
       << setw(COURSE_CREDITS_MAX_LENGTH + 2 * SPACE) << "Credits"
       << setw(GRADE_MAX_LENGTH + SPACE) << "Grade" << endl;
  cout << DIVIDER;
  for (int i = 0; i < numCourses; ++i)
    cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << courses[i].getCode()
         << setw(COURSE_NAME_MAX_LENGTH + SPACE) << courses[i].getName()
         << setw(COURSE_CREDITS_MAX_LENGTH + SPACE) << courses[i].getCredits()
         << setw(GRADE_MAX_LENGTH + SPACE) << grades[i] << endl;
  cout << endl;
}
void Student::operator=(const Student &student) {
  User::operator=(student);
  numCourses = student.numCourses;
  delete[] courses;
  delete[] grades;
  courses = new Course[numCourses];
  grades = new double[numCourses];
  for (int i = 0; i < numCourses; ++i) {
    courses[i] = student.courses[i];
    grades[i] = student.grades[i];
  }
}
void Student::handleMenu() {
  int choice;
  do {
    cout << "1. Enroll in a new Course\n2. Drop a Course\n3. View Grade in a "
            "Specific Course\n"
         << "4. Display All Information\n5. Logout\n";
    cin >> choice;

    switch (choice) {
    case 1:
      // Enroll in a new course logic
      cout << "Enroll in a new Course logic here.\n";
      break;
    case 2:
      // Drop a course logic
      cout << "Drop a Course logic here.\n";
      break;
    case 3:
      // View grade in a specific course logic
      cout << "View Grade in a Specific Course logic here.\n";
      break;
    case 4:
      // Display all information logic
      cout << "Display All Information logic here.\n";
      break;
    case 5:
      // Logout
      return;
    default:
      cout << "Invalid choice!\n";
    }
  } while (choice != 5);
}
