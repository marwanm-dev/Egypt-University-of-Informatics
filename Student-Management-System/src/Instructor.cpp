#include "../include/Instructor.h"
#include "../include/CONSTANTS.h"
#include "../include/Course.h"
#include "../include/User.h"
#include "swapIndices.cpp"
#include <iomanip>
#include <string>

Instructor::Instructor() : numCourses(0), MAX_COURSES(INSTRUCTOR_MAX_COURSES) {}

Instructor::Instructor(const string &username, const string &password)
    : User(username, password), numCourses(0),
      MAX_COURSES(INSTRUCTOR_MAX_COURSES) {
  courses = new Course[MAX_COURSES];
  if (username == "") // invalid credentials validated by the User constructor
    cout << "Instructor can not be created due to invalid credentials." << endl;
}

Instructor::~Instructor() { delete[] courses; }

void Instructor::addCourse(Course course) { courses[numCourses++] = course; }

void Instructor::removeCourse(string code) {
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      swapIndices(courses[i], courses[numCourses - 1]);
      numCourses--;
    }
  }
}

void Instructor::setGrade(string code, int id, double grade) {
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

double Instructor::performStats(string code, string type) {
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].getCode() == code) {
      if (type == "max") {
        return courses[i].getMaxGrade();
      }
      if (type == "min") {
        return courses[i].getMinGrade();
      }
      if (type == "avg") {
        return courses[i].getAvgGrade(-1);
      }
    }
  }
  return -1;
};

void Instructor::operator=(const Instructor &instructor) {
  User::operator=(instructor);
  numCourses = instructor.numCourses;
  delete[] courses;
  courses = new Course[numCourses];
  for (int i = 0; i < numCourses; ++i)
    courses[i] = instructor.courses[i];
}

void Instructor::display() const {
  User::display();

  // Display header for Courses
  cout << "Instructor Courses:" << endl;
  cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << "Code"
       << setw(COURSE_NAME_MAX_LENGTH + SPACE) << "Name"
       << setw(COURSE_CREDITS_MAX_LENGTH + SPACE) << "Credits" << endl;
  cout << DIVIDER;
  for (int i = 0; i < numCourses; i++)
    cout << left << setw(COURSE_CODE_MAX_LENGTH + SPACE) << courses[i].getCode()
         << setw(COURSE_NAME_MAX_LENGTH + SPACE) << courses[i].getName()
         << setw(COURSE_CREDITS_MAX_LENGTH + SPACE) << courses[i].getCredits();
  cout << endl;
}

void Instructor::handleMenu() {
  int choice;
  do {
    cout << "1. Add Course\n2. Remove Course\n3. Add/Update Student Grade\n"
         << "4. Perform Course Statistics\n5. Display All Information\n6. "
            "Logout\n";
    cin >> choice;

    switch (choice) {
    case 1:
      // Add course logic
      cout << "Add Course logic here.\n";
      break;
    case 2:
      // Remove course logic
      cout << "Remove Course logic here.\n";
      break;
    case 3:
      // Add/Update student grade logic
      cout << "Add/Update Student Grade logic here.\n";
      break;
    case 4:
      // Perform course statistics logic
      cout << "Perform Course Statistics logic here.\n";
      break;
    case 5:
      // Display all information logic
      cout << "Display All Information logic here.\n";
      break;
    case 6:
      // Logout
      return;
    default:
      cout << "Invalid choice!\n";
    }
  } while (choice != 6);
}
